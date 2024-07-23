#include "menu.hpp"
#include "init_map.hpp"

SDL_Surface* menu;
std::vector<button*> buttons;

button* create_button(SDL_Surface* screen_to_copy_to, const char* text, const char* file, int x, int y){
    button* new_button = new button;

    new_button->text = text;
    new_button->img = SDL_LoadBMP(file);
    if(!new_button->img){
        std::printf("Bitmap Not Found\n");
        return NULL;
    }
    new_button->rect.w = new_button->img->w;
    new_button->rect.h = new_button->img->h;
    new_button->rect.x = x;
    new_button->rect.y = y;

    if(x == CENTERED){
        new_button->rect.x = (screen_to_copy_to->w / 2) - (new_button->rect.w / 2);
    }

    if(y == CENTERED){
        new_button->rect.y = (screen_to_copy_to->h / 2) - (new_button->rect.h / 2);
    }

    return new_button;
}

void delete_button(button* but){
    if(but->img){
        SDL_FreeSurface(but->img);
    }

    delete but;

    return;
}

void buttons_cleanup(){
    for(button* but : buttons){
        delete_button(but);
    }

    buttons.clear();

    return;
}

void init_menu(std::string filename){
    SDL_Surface* native_menu = SDL_LoadBMP(filename.c_str());
    if(!native_menu){
        std::printf("Failed to load native menu surface\n");
    }

    menu = resize_bitmap(native_menu, 1920, 1080);
    if(!menu){
        std::printf("Failed to load menu surface\n");
    }

    button* quit = create_button(menu, "quit", "assets/gfx/menu/quit_button.bmp", CENTERED, CENTERED);
    buttons.push_back(quit);

    button* play = create_button(menu, "play", "assets/gfx/menu/play_button.bmp", CENTERED, 200);
    buttons.push_back(play);

    return;
}

render_capable draw_buttons(void){
    for(auto& butt : buttons){
        SDL_UpperBlitScaled(butt->img, NULL, screen, &butt->rect);
    }

    return;
}

button* check_for_button_interaction(void){
    int x, y;
    SDL_GetMouseState(&x, &y);
    for(auto& butt : buttons){
        if(x > butt->rect.x && x < butt->rect.w + butt->rect.x && y > butt->rect.y && y < butt->rect.h + butt->rect.y){
            return butt;
        }
    }

    return NULL;
}
