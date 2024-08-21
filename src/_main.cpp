/**
 * @author GpapPeaky Giorgos Papamatthaiakis
 *          https://github.com/GpapPeaky
 * 
 * @version 0.1 Hepanastase (release.patch Name)
 */

#include "../auxf/includes.aux"

int main(int argv, char** args){
    /* Viewport initialisation */
    camera cam = init_camera();
    /* UI initialisation */
    init_menu("assets/gfx/ui/menu/menu_bg.bmp");
    /* Provinces hastable initialisation */
    prime_array_generation(300);
    init_hash();
    /* Initialise the window and renderer */
    win_init("keng");
    /* Initialise the map data to be used */
    init_map_textures();
    /* Initialise the unit graphic assets */
    init_unit_assets();

    #ifdef MAIN_DBG
        std::printf("\nInit Functions Completed l:%d\n", __LINE__);
    #endif

    /* Parse provinces, (RGB values, names, ids ect.) and add them to the respective region (regions are initialised here as well...) */
    prov_to_reg("history/provinces/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        std::printf("Provinces To Regions Parse Completed l:%d\n", __LINE__);
    #endif

    /* Parse region names, to assign them to the previously initialised regions */
    reg_names("history/regions/region_names.ndf");
    #ifdef MAIN_DBG
        std::printf("Region Names Parse Completed l:%d\n", __LINE__);
    #endif
    
    /* Parse country data (RGB values, names) and their unique tags */
    init_countries("history/country/cou.ndf", "history/country/tags.cdf");
    #ifdef MAIN_DBG
        std::printf("Countries Parse Completed l:%d\n", __LINE__);
    #endif

    /* Parse ownership data, to assign the regions to the correct country */
    reg_to_country("history/country/ownership.cdf"); 
    #ifdef MAIN_DBG
        std::printf("Region To Countries Complete l:%d\n", __LINE__);
    #endif

    /* Paints the given province map with the correct country colour */
    mark_countries(click_surface, map); /* We use the click map as per usual */
    #ifdef MAIN_DBG
        std::printf("Countries Painting Completed l:%d\n", __LINE__);
    #endif

    /* Paints the borders inbetween countries and provinces */
    // mark_borders(map, outter_border_map, win, OUTTER_BORDER_COLOUR_GS);
    mark_inner_borders(click_surface, inner_border_map); /* FIXME: Marks coastlines and rivers as well, when it shouldn't */
    #ifdef MAIN_DBG
        std::printf("Border Generation Completed l:%d\n\n", __LINE__);
    #endif

    /* Prints */
    print_regions();
    print_countries();
    print_country_colours();
    print_provinces();
    #ifdef MAIN_DBG
        std::printf("\nPrints Completed l:%d\n\n", __LINE__);
    #endif

    /* IDEA: Might keep this like that... */
    #ifdef MAIN_MENU
        /* TODO: refactor to a function ,not raw code in main! */
        bool menu_box = false;
        while(!menu_box){
            SDL_Event e;

            SDL_UpperBlitScaled(menu, NULL, screen, NULL);
            draw_buttons();
            while(SDL_PollEvent(&e)){
            if(e.type == SDL_MOUSEBUTTONDOWN){
                button* pressed = check_for_button_interaction();
                if(pressed != NULL){
                    if(strcmp(pressed->text, "play") == 0){
                        std::printf("Entering game...\n");
                        buttons_cleanup();
                        menu_box = true;
                    }
                    if(strcmp(pressed->text, "quit") == 0){
                        std::printf("Quitting game...\n");
                        buttons_cleanup();
                        cleanup(win, renderer);
                        return EXIT_SUCCESS;
                    }
                }
            }
            SDL_UpdateWindowSurface(win);
            }
        }
    #endif

    create_unit(INFANTRY, get_country("TST"), 2, click_surface);
    create_unit(ARMOR, get_country("TST"), 4, click_surface);
    create_unit(ARTILLERY, get_country("TST"), 3, click_surface);
    create_unit(MOTORISED, get_country("TST"), 5, click_surface);
    // /* Wrong prov_id given */
    // create_unit(INFANTRY, get_country("TST"), 36, click_surface); 

    /* IT APPEARS THAT THE (CLEAR -> RENDERCOPY -> PRESENT) METHOD IS GPU ACCELERATED... */

    /* Game */
    bool quit = false;
    while(!quit){
        /* TODO: Refactor Renditions, into one function */
        render_map(renderer, textures, cam);
        draw_units(cam);
        events_handling(quit, cam);
        
        SDL_RenderPresent(renderer);

        // generate_countries_surfaces(map, win); /* Lags the engine ,call it if a province is annexed */
        // SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); /* Clean Canvas */
        // render_to_screen(map, screen, cam);
        // if(cam.zoom > 1.7){
        //     render_to_screen(inner_border_map, screen, cam);
        // }
        // render_to_screen(outter_border_map, screen, cam);
        // if(cam.zoom > 1.0){
        //     draw_units(screen, cam);
        // }
        // render_to_screen(highlight_map, screen, cam); /* FIXME: Highlight map not showing */
        // render_to_screen(click_map, screen, cam);
        // SDL_UpperBlitScaled(click_map, &cam.rect, screen, NULL);
        // render_to_screen(map, screen, cam); /* Renders the .bmp by blitting it onto the screen */
        // render_on_mouse_hover(); /* Special Event */

        // #ifdef WIN_UPDATE
        //     SDL_UpdateWindowSurface(win);
        //     /* If any change is done to the window surface (all the surfaces mashed together), it is changed and updated so that it is shown */
        //     /* It clatters due to the {CLEAR -> RENDERCOPY -> PRESENT} method */
        // #endif

        /* Frame rate cap at 60 fps (60 FPS means 16 microseconds per frame (or per loop, since one counts as one frame)) */
    }

    /* Cleanup */
    cleanup(win, renderer);

    return EXIT_SUCCESS;
}
