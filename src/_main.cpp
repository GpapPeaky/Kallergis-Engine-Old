#include "includes.aux"

int main(int argv, char* args[]){


    map_width = 5760;
    map_height = 3240;

    Uint64 start, end, seconds;
    SDL_FRect FPS_pos;
    FPS_pos.x = 0.0f;
    FPS_pos.y = 25.0f;

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

        #ifdef CALC_COUNT

            start = SDL_GetPerformanceCounter(); /* CALC_COUNT */

        #endif /* CALC_COUNT */

        events_handling(quit);

        SDL_RenderClear(renderer); /* Canvas clearing */
        
        // generate_countries_surfaces(); /* Creates a new Surface and Texture, to render the country colours */ 

        render_map(map_scale, x_off, y_off); /* Renders the .png */

        render_on_mouse_hover(); /* Special Event */

        #ifdef CALC_COUNT

            end = SDL_GetPerformanceCounter(); /* CALC_COUNT */

            seconds = (end - start);
            std::string FPS = "cpc: " + std::to_string(seconds);

            render_text(FPS, &FPS_pos);

        #endif /* CALC_COUNT */

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
