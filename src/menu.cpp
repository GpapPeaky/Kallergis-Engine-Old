#include "menu.hpp"
#include "init_map.hpp"

SDL_Surface* menu;
std::vector<button> buttons;

void init_menu(std::string filename){

    button play;
    button quit;

    SDL_Surface* native_menu = SDL_LoadBMP(filename.c_str());
    if(!native_menu){
        std::printf("Failed to load native menu surface\n");
    }

    menu = resize_bitmap(native_menu, 1920, 1080);
    if(!menu){
        std::printf("Failed to load menu surface\n");
    }

    /* TODO: Make a create_button() function */
    play.text = "play";
    play.img = SDL_LoadBMP("assets/gfx/menu/play_button.bmp");
    play.rect.w = play.img->w;
    play.rect.h = play.img->h;
    play.rect.x = (menu->w / 2) - (play.rect.w / 2);
    play.rect.y = (menu->h / 2) - (play.rect.h / 2) - 200;

    quit.text = "quit";
    quit.img = SDL_LoadBMP("assets/gfx/menu/quit_button.bmp");
    quit.rect.w = quit.img->w;
    quit.rect.h = quit.img->h;
    quit.rect.x = (menu->w / 2) - (quit.rect.w / 2);
    quit.rect.y = (menu->h / 2) - (quit.rect.h / 2) + 200;

    buttons.push_back(play);
    buttons.push_back(quit);

    return;
}

render_capable draw_buttons(void){
    for(auto& butt : buttons){
        SDL_UpperBlitScaled(butt.img, NULL, screen, &butt.rect);
    }

    return;
}

button* check_for_button_interaction(void){
    int x, y;
    SDL_GetMouseState(&x, &y);
    for(auto& butt : buttons){
        if(x > butt.rect.x && x < butt.rect.w + butt.rect.x && y > butt.rect.y && y < butt.rect.h + butt.rect.y){
            printf("Button %s clicked\n", butt.text);
            return &butt;
        }
    }

    /* FIXME: Not pressing a button still makes the game quit */
}
