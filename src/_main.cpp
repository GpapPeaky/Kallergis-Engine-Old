/**
 * @author GpapPeaky Giorgos Papamatthaiakis
 *          https://github.com/GpapPeaky
 * 
 * @version 0.1 Hepanastase (release.patch Name)
 */

#include "auxf/includes.aux"

/* TODO: Make it so that components that are not inside the camera's rectangle, don't render */

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
    /* Initialise goods graphic assets */
    init_goods();

    #ifdef MAIN_DBG
        dprint("init called");
    #endif

    /* Parse provinces, (RGB values, names, ids ect.) and add them to the respective region (regions are initialised here as well...) */
    prov_to_reg("history/provinces/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        dprint("prov to regions called");
    #endif

    /* Parse region names, to assign them to the previously initialised regions */
    reg_names("history/regions/region_names.ndf");
    #ifdef MAIN_DBG
        dprint("region names called");
    #endif
    
    /* Parse country data (RGB values, names) and their unique tags */
    init_countries("history/country/cou.ndf", "history/country/tags.cdf");
    #ifdef MAIN_DBG
        dprint("init countries called");
    #endif

    /* Parse ownership data, to assign the regions to the correct country */
    reg_to_country("history/country/ownership.cdf"); 
    #ifdef MAIN_DBG
        dprint("regions to countries called");
    #endif

    /* Paints the given province map with the correct country colour */
    mark_countries(click_surface, map); /* We use the click map as per usual */
    #ifdef MAIN_DBG
        dprint("marking countries called");
    #endif

    /* Paints the borders inbetween countries and provinces */
    mark_inner_borders(click_surface, inner_border_map); /* FIXME: Marks coastlines and rivers as well, when it shouldn't */
    #ifdef MAIN_DBG
        dprint("border generation called");
    #endif

    /* Prints */
    #ifdef MAIN_PRINTS
        print_regions();
        print_countries();
        print_country_colours();
        print_provinces();
        #ifdef MAIN_DBG
            dprint("Prints Completed\n");
        #endif
    #endif

    /* TODO: Start Adding UI for unit creation, Add a units.udf file for the where the first units are created */

    create_unit(MOTORISED, get_country("TST"), 1, click_surface, cam);

    /* IT APPEARS THAT THE (CLEAR -> RENDERCOPY -> PRESENT) METHOD IS GPU ACCELERATED... */

    /* Game */
    bool quit = false;
    while(!quit){
        /* TODO: Refactor Renditions, into one function */
        render_map(renderer, textures, cam);
        draw_units(cam);
        render_goods_bar();
        events_handling(quit, cam);
        
        SDL_RenderPresent(renderer);

        // generate_countries_surfaces(map, win); /* Lags the engine ,call it if a region is annexed */

        /* Frame rate cap at 60 fps (60 FPS means 16 microseconds per frame (or per loop, since one counts as one frame)) */
    }

    /* Cleanup */
    cleanup(win, renderer);

    return EXIT_SUCCESS;
}
