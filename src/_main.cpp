#include "includes.aux"

int main(int argv, char* args[]){

    map_width = 5760;
    map_height = 3240;

    /* Initialise */
    win_init("project candia");
    init_font();
    init_map();
    initialise_viewport(DEV_SCREEN_W, DEV_SCREEN_H);

    /* Parsers */
    prov_to_reg("src/regions/provinces.mdf"); /* Relative to the executable location */   
    reg_names("src/regions/region_names.ndf");
    init_countries("src/country/cou.ndf", "src/country/tags.cdf");
    reg_to_country("src/regions/ownership.cdf"); 

    /* Prints */
    print_regions();
    print_countries();

    bool quit = false;

    while(!quit){
        events_handling(quit);

        SDL_RenderClear(renderer); /* Canvas clearing */
        render_map(map_scale, x_off, y_off); /* Renders the .png */
        render_on_mouse_hover(); /* Special Event */
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
