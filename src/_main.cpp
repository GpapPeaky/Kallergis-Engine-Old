#include "includes.aux"

int main(int argv, char* args[]){

    win_init("win");
    prov_to_reg("src/regions/provinces.mdf"); /* Relative to the executable location */   
    reg_names("src/regions/region_names.ndf");
    init_countries("src/country/cou.ndf", "src/country/tags.cdf");
    reg_to_country("src/regions/ownership.cdf"); 

    print_regions();
    print_countries();

    while(1){
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_e){ /* Force termination key */
                break;
            }
        }

        SDL_RenderClear(renderer); /* Canvas clearing */

         /* Loading texture copies */

        /* render_map(); */

        SDL_RenderPresent(renderer); /* Present copies */
    }

    std::printf("terminates correctly\n");

    return EXIT_SUCCESS;
}
