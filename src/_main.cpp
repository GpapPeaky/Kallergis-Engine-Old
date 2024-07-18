/**
 * @author GpapPeaky Giorgos Papamatthaiakis
 *          https://github.com/GpapPeaky
 * 
 * @version 0.1 Hepanastase (release.patch Name)
 */

#include "../auxf/includes.aux"

int main(int argv, char* args[]){

    /* Initialise */
    camera cam = init_camera(); /* Initialising Viewport / Camera */
    init_menu("assets/gfx/menu/menu_bg.bmp");
    prime_array_generation(300);
    init_hash();
    win_init("kallergis engine");
    init_font();
    init_map();

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
        std::printf("Countries Painting Completed\n");
    #endif

    mark_borders(map, click_map, win, 1);
    #ifdef MAIN_DBG
        std::printf("Borders Created\n\n");
    #endif

    /* Prints */
    print_regions();
    print_countries();
    print_country_colours();
    print_provinces();

    #ifdef MAIN_MENU
        /* Menu */
        bool menu_box = false;
        while(!menu_box){
            SDL_Event e;

            SDL_UpperBlitScaled(menu, NULL, screen, NULL);
            draw_buttons();
            while(SDL_PollEvent(&e)){
            if(e.type == SDL_MOUSEBUTTONDOWN){
                button* pressed = check_for_button_interaction();
                if(strcmp(pressed->text, "play") == 0){
                    std::printf("Entering game\n");
                    menu_box = true;
                }
                if(strcmp(pressed->text, "quit") == 0){
                    std::printf("Quitting game\n");
                    cleanup(win, renderer);
                    return EXIT_SUCCESS;
                }
            }
            SDL_UpdateWindowSurface(win);
            }
        }
    #endif

    /* Game */
    bool quit = false;
    while(!quit){
        events_handling(quit, cam);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); /* Clean Canvas */
        render_to_screen(map, screen, cam);
        // render_to_screen(click_map, screen, cam);
        // SDL_UpperBlitScaled(click_map, &cam.rect, screen, NULL);
        // render_to_screen(map, screen, cam); /* Renders the .bmp by blitting it onto the screen */
        // render_on_mouse_hover(); /* Special Event */

        #ifdef WIN_UPDATE /* Only updates when the TAB key is pressed, if called in main it will update and stay there always */
            SDL_UpdateWindowSurface(win);
        /* If any change is done to the window surface (all the surfaces mashed together), it is changed and updated so that it is shown */
        /* It clatters due to the {CLEAR -> RENDERCOPY -> PRESENT} method */
        #endif
    }

    EXIT:
        cleanup(win, renderer);

    return EXIT_SUCCESS;
}
