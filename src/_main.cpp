/**
 * @author GpapPeaky Giorgos Papamatthaiakis
 *          https://github.com/GpapPeaky
 * 
 * @version 0.1 Hepanastase (release.patch Name)
 */

#include "../auxf/includes.aux"

int main(int argv, char* args[]){

    /* Initialise */
    prime_array_generation(300);
    init_hash();
    win_init("kallergis engine");
    init_font();
    init_map();
    // initialise_viewport(DEV_SCREEN_W, DEV_SCREEN_H); /* FIXME */
    #ifdef MAIN_DBG
        std::printf("Init Functions Complete!\n");
    #endif

    /* Parsers */
    prov_to_reg("history/provinces/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        std::printf("\nProvinces To Regions Parse Complete\n");
    #endif

    reg_names("history/regions/region_names.ndf");
    #ifdef MAIN_DBG
        std::printf("Region Names Parse Complete\n");
    #endif
    
    init_countries("history/country/cou.ndf", "history/country/tags.cdf");
    #ifdef MAIN_DBG
        std::printf("Countries Parse Complete\n");
    #endif

    reg_to_country("history/country/ownership.cdf"); 
    #ifdef MAIN_DBG
        std::printf("Region To Countries Complete\n");
    #endif

    generate_countries_surfaces(map, win);
    #ifdef MAIN_DBG
        std::printf("Countries Painting Completed\n\n");
    #endif

    /* Prints */
    print_regions();
    print_countries();
    print_country_colours();
    print_provinces();

    bool quit = false;
    while(!quit){

        events_handling(quit);
        render_to_screen(map, screen, 0, 0, 0); /* Renders the .bmp by blitting it onto the screen */
        // render_on_mouse_hover(); /* Special Event */

        #ifdef WIN_UPDATE /* Only updates when the TAB key is pressed, if called in main it will update and stay there always */
            SDL_UpdateWindowSurface(win);
        /* If any change is done to the window surface (all the surfaces mashed together), it is changed and updated so that it is shown */
        /* It clatters due to the {CLEAR -> RENDERCOPY -> PRESENT} method */
        #endif
    }


    cleanup(win, renderer);

    return EXIT_SUCCESS;
}
