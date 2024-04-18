#include "map.h"

render_capable render_map(void){
    SDL_Rect rect = { 0, 0, map_surface->w, map_surface->h };
    SDL_RenderCopy(renderer, map_texture, NULL, &rect);
}