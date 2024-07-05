#include "map.h"

SDL_Rect viewport; 
float map_scale = 1.0f;
int map_width;
int map_height;
int x_off = 0;
int y_off = 0;

render_capable render_map(float zoom, int x, int y){
    int texture_h, texture_w;
    SDL_QueryTexture(map_texture, NULL, NULL, &texture_w, &texture_h); /* Take the width and height of the map */

    int renderer_w, renderer_h;
    SDL_GetRendererOutputSize(renderer, &renderer_w, &renderer_h);

    /* Moves the colours as well for the font to be displayed on hover */

    float texture_center_x = texture_w / 2.0f;
    float texture_center_y = texture_h / 2.0f;

    float renderer_center_x = renderer_w / 2.0f;
    float rendere_center_y = renderer_h / 2.0f;

    viewport.w = static_cast<int>(texture_w * zoom);
    viewport.h = static_cast<int>(texture_h * zoom);
    viewport.x = static_cast<int>(renderer_center_x - (texture_center_x * zoom) + x);
    viewport.y = static_cast<int>(rendere_center_y - (texture_center_y * zoom) + y);

    // SDL_RenderCopy(renderer, map_bg_texture, NULL, &viewport); /* Render the texture on top of the map */
    SDL_RenderCopy(renderer, map_texture, NULL, &viewport);
    // screen = SDL_GetWindowSurface(win);
    // SDL_BlitSurface(map_surface, NULL, screen, &viewport);

    /* IDEA: For each textutre create a texture that has different data and render it instead */

    return;
}

void initialise_viewport(float screen_width, float screen_height){
    viewport.h = screen_height / 2;
    viewport.w = screen_width / 2;

    float scale_w = screen_width / map_width;
    float scale_h = screen_height / map_height;

    map_scale = std::min(scale_w, scale_h);

    viewport.x = (map_width * map_scale - screen_width) / 2;
    viewport.y = (map_height * map_scale - screen_height) / 2;

    std::printf("viewport initialised\n");

    return;
}

SDL_Surface* resize_province_bitmap(float w, float h){
    SDL_Surface* resized_map_surface = SDL_CreateRGBSurface(0, static_cast<int>(w), static_cast<int>(h), map_surface->format->BitsPerPixel, 
                                                    map_surface->format->Rmask, map_surface->format->Gmask, 
                                                    map_surface->format->Bmask, map_surface->format->Amask);

    SDL_Rect stretched_rect = {0, 0, static_cast<int>(w), static_cast<int>(h)};
    SDL_BlitScaled(map_surface, NULL, resized_map_surface, &stretched_rect);

    return resized_map_surface;
}
