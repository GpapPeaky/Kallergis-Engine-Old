#include "map.hpp"

render_capable render_to_screen(SDL_Surface* surface, SDL_Surface* screen, camera cam){
    // int texture_h, texture_w;
    // SDL_QueryTexture(map_texture, NULL, NULL, &texture_w, &texture_h); /* Take the width and height of the map */

    // int renderer_w, renderer_h;
    // SDL_GetRendererOutputSize(renderer, &renderer_w, &renderer_h); /* We can use this for the zoom-in/-out */

    // /* Moves the colours as well for the font to be displayed on hover */

    // float texture_center_x = texture_w / 2.0f;
    // float texture_center_y = texture_h / 2.0f;

    // float renderer_center_x = renderer_w / 2.0f;
    // float rendere_center_y = renderer_h / 2.0f;

    // viewport.w = static_cast<int>(texture_w * zoom);
    // viewport.h = static_cast<int>(texture_h * zoom);
    // viewport.x = static_cast<int>(renderer_center_x - (texture_center_x * zoom) + x);
    // viewport.y = static_cast<int>(rendere_center_y - (texture_center_y * zoom) + y);

    // SDL_RenderCopy(renderer, map_bg_texture, NULL, &viewport); /* Render the texture on top of the map */
    // SDL_RenderCopy(renderer, map_texture, NULL, &viewport);
    // screen = SDL_GetWindowSurface(win);
    SDL_UpperBlitScaled(surface, &cam.rect, screen, NULL);

    return;
}
