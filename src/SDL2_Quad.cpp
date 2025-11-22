#include "SDL2_Quad.hpp"

SDL2_Quad SDL2_Quads[SDL2_MAX_QUADS];

int SDL2_QuadCount;

bool SDL2_QuadOutlines = false;

bool SDL2_SameColor(SDL_Color c1, SDL_Color c2, int tolerance){
    return abs(c1.r - c2.r) <= tolerance &&
           abs(c1.g - c2.g) <= tolerance &&
           abs(c1.b - c2.b) <= tolerance;
}

SDL_Color SDL2_GetPixel(SDL_Surface* src, int x, int y){
    Uint8 *p = (Uint8 *)src->pixels + y * src->pitch + x * src->format->BytesPerPixel;
    Uint32 pixel;
    switch(src->format->BytesPerPixel){
        case 1:
            pixel = *p;
            break;
        case 2:
            pixel = *(Uint16 *)p;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixel = p[0] << 16 | p[1] << 8 | p[2];
            else
                pixel = p[0] | p[1] << 8 | p[2] << 16;
            break;
        default:
            pixel = *(Uint32 *)p;
            break;
    }

    SDL_Color c;
    SDL_GetRGB(pixel, src->format, &c.r, &c.g, &c.b);

    return c;
}

bool SDL2_IsRegionUniform(SDL_Surface* src, int x, int y, int w, int h, SDL_Color* outColor){
    SDL_Color first = SDL2_GetPixel(src, x, y);
    for(int j = y ; j < y + h ; j++){ 
        for(int i = x ; i < x + w ; i++){
            SDL_Color c = SDL2_GetPixel(src, i, j);
            if(!SDL2_SameColor(first, c, 25)){
                return false;
            }
        }
    }
    
    *outColor = first;
    
    return true;
}

SDL2_Quad* SDL2_Quadtree(SDL_Surface* src, int x, int y, int w, int h){
    if(SDL2_QuadCount >= SDL2_MAX_QUADS) return nullptr;

    SDL2_Quad* q = &SDL2_Quads[SDL2_QuadCount++];
    q->pos = {x, y, w, h};
    q->children[0] = q->children[1] = q->children[2] = q->children[3] = nullptr;

    SDL_Color c;
    if (SDL2_IsRegionUniform(src, x, y, w, h, &c) || w <= SDL2_MIN_QUAD_SIZE || h <= SDL2_MIN_QUAD_SIZE) {
        q->color = c;
        q->isLeaf = true;
        return q;
    }

    q->isLeaf = false;
    int hw = w / 2;
    int hh = h / 2;

    q->children[0] = SDL2_Quadtree(src, x,       y,       hw, hh);
    q->children[1] = SDL2_Quadtree(src, x + hw,  y,       w - hw, hh);
    q->children[2] = SDL2_Quadtree(src, x,       y + hh,  hw, h - hh);
    q->children[3] = SDL2_Quadtree(src, x + hw,  y + hh,  w - hw, h - hh);

    return q;
}

void SDL2_RenderQuadNode(SDL2_Quad* q){
    if(!q) return;

    /* Transformed rects */
    float tx1 = (q->pos.x - (SDL2_Cam->offsetFromCamera.x - SDL2_WinWidth / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
    float ty1 = (q->pos.y - (SDL2_Cam->offsetFromCamera.y - SDL2_WinHeight / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
    float tx2 = ((q->pos.x + q->pos.w) - (SDL2_Cam->offsetFromCamera.x - SDL2_WinWidth / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
    float ty2 = ((q->pos.y + q->pos.h) - (SDL2_Cam->offsetFromCamera.y - SDL2_WinHeight / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;

    SDL_FRect transformed = {
        roundf(tx1),
        roundf(ty1),
        roundf(tx2) - roundf(tx1),
        roundf(ty2) - roundf(ty1)
    };

    SDL_FRect cameraRect = {
        (float)SDL2_Cam->cameraRect.x,
        (float)SDL2_Cam->cameraRect.y,
        (float)SDL2_Cam->cameraRect.w,
        (float)SDL2_Cam->cameraRect.h
    };

    SDL_FRect r;
    if(!SDL_IntersectFRect(&transformed, &cameraRect, &r)){
        return;
    }

    float minScreenSize = 2.0f; /* Pixels, adjust */

    bool tooSmallToSubdivide = (transformed.w < minScreenSize || transformed.h < minScreenSize);

    if(q->isLeaf || tooSmallToSubdivide){
        SDL_SetRenderDrawColor(SDL2_Rnd, q->color.r, q->color.g, q->color.b, 255);

        if(SDL2_QuadOutlines){
            SDL_RenderDrawRectF(SDL2_Rnd, &transformed);
        }else{
            SDL_RenderFillRectF(SDL2_Rnd, &transformed);
        }
        return;

    }

    /* Recurse into children for higher detail */
    for(Uint8 i = 0 ; i < 4 ; i++){
        SDL2_RenderQuadNode(q->children[i]);
    }
}

bool SDL2_AllChildrenLeavesSameColor(SDL2_Quad* node, SDL_Color* outColor){
    if (!node) return false;
    SDL2_Quad* a = node->children[0];
    SDL2_Quad* b = node->children[1];
    SDL2_Quad* c = node->children[2];
    SDL2_Quad* d = node->children[3];

    if(!a || !b || !c || !d) return false;
    if(!a->isLeaf || !b->isLeaf || !c->isLeaf || !d->isLeaf) return false;

    if(SDL2_SameColor(a->color, b->color, 0) &&
        SDL2_SameColor(a->color, c->color, 0) &&
        SDL2_SameColor(a->color, d->color, 0)){
            *outColor = a->color;
            return true;
    }

    return false;
}

void SDL2_MergeTree(SDL2_Quad* node){
    if(!node) return;

    for(int i = 0; i < 4; ++i){
        if(node->children[i]) SDL2_MergeTree(node->children[i]);
    }

    if(node->isLeaf) return;

    SDL_Color unified;
    if(SDL2_AllChildrenLeavesSameColor(node, &unified)){
        node->isLeaf = true;
        node->color  = unified;
        node->children[0] = node->children[1] = node->children[2] = node->children[3] = nullptr;
        SDL2_QuadCount--;
    }
}
