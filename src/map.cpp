#include "map.h"

float map_scale = 1.0f;
int map_width;
int map_height;

render_capable render_map(void){

    SDL_QueryTexture(map_texture, NULL, NULL, &map_width, &map_height); /* Take the width and height of the map */

    int zoom_scale_w = static_cast<int>(map_width * map_scale);
    int zoom_scale_h = static_cast<int>(map_height * map_scale);

    SDL_Rect rect = { 0, 0, zoom_scale_w, zoom_scale_h };
    SDL_RenderCopy(renderer, map_texture, NULL, &rect);
}
