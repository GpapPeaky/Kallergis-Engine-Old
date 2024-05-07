#include "includes.aux"

int main(int argv, char* args[]){

    win_init("win");
    init_map();
    prov_to_reg("src/regions/provinces.mdf"); /* Relative to the executable location */   
    reg_names("src/regions/region_names.ndf");
    init_countries("src/country/cou.ndf", "src/country/tags.cdf");
    reg_to_country("src/regions/ownership.cdf"); 

    print_regions();
    print_countries();

    bool quit = false;
    
    while(!quit){
        events_handling(quit);

        SDL_RenderClear(renderer); /* Canvas clearing */
        render_map(); /* Renders the .png */
        SDL_RenderPresent(renderer); /* Present copies */
    }

    /* Cleanup */

    SDL_DestroyTexture(map_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    std::printf("terminates correctly\n");

    return EXIT_SUCCESS;
}
