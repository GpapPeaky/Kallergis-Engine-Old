#include "includes.aux"

int main(int argv, char* args[]){

    win_init("win");
    read_mdf("src/regions/regions.mdf"); /* Relative to the executable location */

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
