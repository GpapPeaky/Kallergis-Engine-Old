#include "includes.aux"

int main(int argv, char* args[]){

    win_init("win");
    prov_to_reg("src/regions/regions.mdf"); /* Relative to the executable location */

    print_regions();

    while(1){
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                break;
            }
        }
    }

    std::printf("terminates correctly\n");

    return EXIT_SUCCESS;
}
