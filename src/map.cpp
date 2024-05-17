#include "map.h"

SDL_FRect viewport;
long double map_scale = 1.0f;
int map_width;
int map_height;

render_capable render_map(void){

    /* FIXME: zoom scaling */

    SDL_QueryTexture(map_texture, NULL, NULL, &map_width, &map_height); /* Take the width and height of the map */

    float zoom_scale_w = (map_width * map_scale);
    float zoom_scale_h = (map_height * map_scale);

    SDL_FRect rect = { static_cast<float>(viewport.x), static_cast<float>(viewport.y), zoom_scale_w, zoom_scale_h };
    SDL_RenderCopyF(renderer, map_texture, NULL, &rect);
}
