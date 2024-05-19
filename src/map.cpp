#include "map.h"

SDL_FRect viewport; 
float map_scale = 1.0f;
int map_width;
int map_height;

render_capable render_map(void){
    SDL_QueryTexture(map_texture, NULL, NULL, &map_width, &map_height); /* Take the width and height of the map */

    /* Moves the colours as well for the font to be displayed on hover */
    float zoom_scale_w = (map_width * map_scale);
    float zoom_scale_h = (map_height * map_scale);

    SDL_FRect rect = { 
        viewport.x,
        viewport.y,
        zoom_scale_w,
        zoom_scale_h
        };

    SDL_RenderCopyF(renderer, map_texture, NULL, &rect);
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
