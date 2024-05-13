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

render_capable render_text(const std::string msg, SDL_FRect* position){
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

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // for(auto& province : provinces){
    //     if(){
    //         render_text(("HP: " + std::to_string(enemy.sprite.HP)).c_str(), &enemy.sprite.pos);
    //     }
    // }
}
