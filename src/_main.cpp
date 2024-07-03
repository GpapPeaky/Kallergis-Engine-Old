#include "includes.aux"

int main(int argv, char* args[]){

    /* TODO: Move somewhere else, in an initialiser function maybe */
    map_width = 5760;
    map_height = 3240;
    Uint64 start, end, cpc_count;
    SDL_FRect CPC_pos;
    CPC_pos.x = 0.0f;
    CPC_pos.y = 25.0f;

    /* Initialise */
    prime_array_generation(300);
    init_hash();
    win_init("project candia");
    init_font();
    init_map();
    initialise_viewport(DEV_SCREEN_W, DEV_SCREEN_H);

    #ifdef MAIN_DBG
        std::printf("@INITIALISATION COMPLETED@\n");
    #endif

    /* Parsers */
    prov_to_reg("src/regions/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        std::printf("$PROV2REG COMPLETED\n");
    #endif

    reg_names("src/regions/region_names.ndf");
    #ifdef MAIN_DBG
        std::printf("$REGNAMES COMPLETED\n");
    #endif
    
    init_countries("src/country/cou.ndf", "src/country/tags.cdf");
    #ifdef MAIN_DBG
        std::printf("$COUNTRIESINIT COMPLETED\n");
    #endif

    reg_to_country("src/regions/ownership.cdf"); 
    #ifdef MAIN_DBG
        std::printf("$REG2COU COMPLETED\n");
    #endif

    generate_countries_surfaces();

    // flood_fill(map_surface, 2936, 1189, SDL_MapRGB(map_surface->format, 105, 200, 95), SDL_MapRGB(map_surface->format, 255, 255, 255)); /* TODO: Rewrite */
    SDL_UpdateTexture(map_texture, &viewport, map_surface->pixels, map_surface->pitch);

    /* We might just be close for that... check the bin */

    #ifdef PIXELS
        std::printf("$COUNTRY COLOURS COMPLETED\n");
    #endif
    
    /* Prints */
    print_regions();
    print_countries();
    print_country_colours();
    print_provinces();

    bool quit = false;

    while(!quit){

        #ifdef CPC

            start = SDL_GetPerformanceCounter(); /* CPC */

        #endif /* CPC */

        events_handling(quit);

        SDL_RenderClear(renderer); /* Canvas clearing */
        
        // generate_countries_surfaces(); /* Creates a new Surface and Texture, to render the country colours */ 

        render_map(map_scale, x_off, y_off); /* Renders the .png */

        render_on_mouse_hover(); /* Special Event */

        #ifdef CPC

            end = SDL_GetPerformanceCounter(); /* CPC */

            cpc_count = (end - start);
            std::string CPC = "cpc: " + std::to_string(cpc_count);

            render_text(CPC, &CPC_pos);
            if(cpc_count > CPC_BENCHMARK){
                std::printf("%d\n", cpc_count);
            }

        #endif /* CPC */

        SDL_UpdateWindowSurface(win); /* If any change is done to the window surface (all the surfaces mashed together), it is changed and updated so that it is shown */
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
