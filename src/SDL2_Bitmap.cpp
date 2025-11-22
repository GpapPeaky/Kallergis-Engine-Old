#include "SDL2_Bitmap.hpp"

SDL2_Bitmap* SDL2_NewBitmap(const char* fpath){
    SDL2_Bitmap* bp = new SDL2_Bitmap();

    bp->srfc = IMG_Load(fpath);
    if(!bp->srfc){ printf("ERROR: Couldn't load surface %s\n", fpath); }

    bp->txtr = SDL_CreateTextureFromSurface(SDL2_Rnd, bp->srfc);
    if(!bp->txtr){ printf("ERROR: Couldn't create texture %s\n", fpath); }

    bp->pos = { 0.0F, 0.0F, (float)bp->srfc->w, (float)bp->srfc->h };

    return bp;
}

void SDL2_RecalibrateBitmapTexture(SDL2_Bitmap* bp){
    if(!bp){ printf("ERROR: Invalid bitmap object in texture recalibration\n"); }

    if(bp->txtr){
        SDL_DestroyTexture(bp->txtr); /* Free the texture */
    }

    bp->txtr = SDL_CreateTextureFromSurface(SDL2_Rnd, bp->srfc);

    return;
}

void SDL2_RecalibrateBitmapSizeAspectRatioLocked(SDL2_Bitmap* bp, float size){
    float aspectRatio = (float)bp->srfc->w / (float)bp->srfc->h; /* Parse from the unchanged surface */

    bp->pos.w = size;
    bp->pos.h = size / aspectRatio;

    return;
}

void SDL2_RecalibrateBitmapSize(SDL2_Bitmap* bp, float w, float h){
    bp->pos.w = w;
    bp->pos.h = h;

    return;
}

void SDL2_FreeBitmap(SDL2_Bitmap* bp){
    if(bp->txtr){ SDL_DestroyTexture(bp->txtr); }
    if(bp->srfc){ SDL_FreeSurface(bp->srfc); }

    delete bp;

    return;
}

void SDL2_RenderBitmap(SDL2_Bitmap* bp, SDL_Rect* srcRect){
    /* Apply camera offsets */
    SDL_FRect transformedRect = bp->pos;
    transformedRect.x = (bp->pos.x - (SDL2_Cam->offsetFromCamera.x - SDL2_WinWidth / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
    transformedRect.y = (bp->pos.y - (SDL2_Cam->offsetFromCamera.y - SDL2_WinHeight / (2.0f * SDL2_Cam->zoom))) * SDL2_Cam->zoom;
    transformedRect.w = bp->pos.w * SDL2_Cam->zoom;
    transformedRect.h = bp->pos.h * SDL2_Cam->zoom;


    SDL_RenderCopyF(
        SDL2_Rnd, 
        bp->txtr,
        srcRect,
        &transformedRect);

    return;
}
