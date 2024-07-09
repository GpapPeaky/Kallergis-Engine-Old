#include "includes.aux"

int main(int argv, char* args[]){

    /* TODO: Move somewhere else, in an initialiser function maybe */
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
    // initialise_viewport(DEV_SCREEN_W, DEV_SCREEN_H); /* FIXME */
    #ifdef MAIN_DBG
        std::printf("Init Functions Complete!\n");
    #endif

    /* Parsers */
    prov_to_reg("src/regions/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        std::printf("\nProvinces To Regions Parse Complete\n");
    #endif

    reg_names("src/regions/region_names.ndf");
    #ifdef MAIN_DBG
        std::printf("Region Names Parse Complete\n");
    #endif
    
    init_countries("src/country/cou.ndf", "src/country/tags.cdf");
    #ifdef MAIN_DBG
        std::printf("Countries Parse Complete\n");
    #endif

    reg_to_country("src/regions/ownership.cdf"); 
    #ifdef MAIN_DBG
        std::printf("Region To Countries Complete\n");
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

        // SDL_RenderClear(renderer); /* Canvas clearing */

        events_handling(quit);
        render_to_screen(map, screen, 0, 0, 0); /* Renders the .bmp by blitting it onto the screen */
        // render_on_mouse_hover(); /* Special Event */

        #ifdef CPC
            end = SDL_GetPerformanceCounter(); /* CPC */
            cpc_count = (end - start);
            std::string str = "cpc: " + std::to_string(cpc_count);
            render_text(str, &CPC_pos);
            if(cpc_count > CPC_BENCHMARK){
                std::printf("%d\n", cpc_count);
            }
        #endif /* CPC */

        // SDL_UpdateWindowSurface(win); /* If any change is done to the window surface (all the surfaces mashed together), it is changed and updated so that it is shown */
        // SDL_RenderPresent(renderer); /* Present copies */

        #ifdef WIN_UPDATE /* Only updates when the TAB key is pressed, if called in main it will update and stay there always */
        /* It clatters due to the {CLEAR -> RENDERCOPY -> PRESENT} method */
            SDL_UpdateWindowSurface(win);
        #endif
    }

    /* Cleanup */

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    std::printf("terminates correctly\n");

    return EXIT_SUCCESS;
}
