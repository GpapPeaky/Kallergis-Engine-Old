#include "font.h"

SDL_Color text_colour = { 255, 255, 255};
SDL_Color text_colour_bg = {0, 0, 0};
SDL_Surface * text = NULL;
SDL_Texture * txt = NULL;
SDL_Texture * b_txt = NULL;
TTF_Font* font = NULL;
SDL_FRect rect;
SDL_FRect b_rect;
SDL_FRect c_rect;

err_capable init_font(void){

    TTF_Init(); /* Initialise */

    font = TTF_OpenFont("src/gfx/font/constanb.ttf", FONT_SIZE);
    if(!font){
        std:printf("FONT: %s\n ", SDL_GetError());
        return FAIL;
    }

    return SUCCESS;
}

render_capable render_text(std::string msg, SDL_FRect* position){
    text = TTF_RenderUTF8_Solid(font, msg.c_str(), text_colour);
    if(!text){
        std::printf("%s\n ", SDL_GetError());
    }
    txt = SDL_CreateTextureFromSurface(renderer, text);
    if(!txt){
        std::printf("%s\n ", SDL_GetError());
    }

    SDL_FreeSurface(text);

    text = TTF_RenderUTF8_Solid(font, msg.c_str(), text_colour_bg);
    if(!text){
        std::printf("%s\n ", SDL_GetError());
    }
    b_txt = SDL_CreateTextureFromSurface(renderer, text);
    if(!b_txt){
        std::printf("%s\n ", SDL_GetError());
    }

    SDL_FreeSurface(text);

    rect.x = position->x;
    rect.y = position->y -20;
    rect.h = text->h;
    rect.w = text->w;

    b_rect.x = rect.x + 2;
    b_rect.y = rect.y + 2;
    b_rect.h = text->h + 2;
    b_rect.w = text->w + 2;

    c_rect.x = rect.x - 2;
    c_rect.y = rect.y - 2;
    c_rect.h = text->h;
    c_rect.w = text->w;

    SDL_RenderCopyF(renderer, b_txt, NULL, &c_rect);
    SDL_RenderCopyF(renderer, b_txt, NULL, &b_rect);
    SDL_RenderCopyF(renderer, txt, NULL, &rect);

    SDL_DestroyTexture(b_txt);
    SDL_DestroyTexture(txt);
}

render_capable render_on_mouse_hover(void){

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    Uint8 r, g, b;

    int map_x = (mouse_x - viewport.x) / map_scale;
    int map_y = (mouse_y - viewport.y) / map_scale;

    int index = map_y * map_surface->pitch + map_x * 3;

    /* Parse pixels from the map_surface and not the actual screen */

    b = ((Uint8*)map_surface->pixels)[index];
    g = ((Uint8*)map_surface->pixels)[index + 1];
    r = ((Uint8*)map_surface->pixels)[index + 2];

    for(auto& province : provinces){
        if(province.prov_colour.r == r &&
        province.prov_colour.g ==  g &&
        province.prov_colour.b == b){

            std::string info = "Name: " + province.prov_name +  " Region: " + regions[province.region].reg_name + " (" + std::to_string(province.region) + ") ID: " + std::to_string(province.prov_id);

            SDL_FRect text_pos;

            text_pos.x = mouse_x;
            text_pos.y = mouse_y;

            render_text(info, &text_pos);
            return;
        }
    }

    return;
}
