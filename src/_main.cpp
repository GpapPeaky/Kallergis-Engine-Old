#include "init_win.h"

int main(int argv, char* args[]){

    win_init("win");

    while(1){
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                break;
            }
        }
    }

    std::printf("Works correctly\n");

    return EXIT_SUCCESS;
}
