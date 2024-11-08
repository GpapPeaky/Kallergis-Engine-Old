/**
 * @author GpapPeaky Giorgos Papamatthaiakis
 *          https://github.com/GpapPeaky
 * 
 * @version 0.1 Hepanastase (release.patch Name)
 */

#include "auxf/includes.aux"

/* TODO: Refactor all the code, variable names for something more elegant and understandable */
/* TODO: Make it so that components that are not inside the camera's rectangle, don't render */

int main(int argv, char** args){
    /* Viewport initialisation */
    camera cam = SDL2_CreateCamera();
    /* Initialise the window and renderer */
    SDL2_CreateWindowAndRenderer("keng");
    /* Initialise the map data to be used */
    KENG_CreateMapTextures();
    /* Initialise the unit graphic assets */
    KENG_CreateUnitAssets();
    /* Initialise goods graphic assets */
    KENG_CreateGoods();
    /* Initialise the font */
    SDL2_CreateFont();
    /* Initialise the clock */
    KENG_CreateClock();

    #ifdef MAIN_DBG
        DEBUG_Print("init called");
    #endif

    /* Parse provinces, (RGB values, names, ids ect.) and add them to the respective region (regions are initialised here as well...) */
    KENG_ProvinceToRegion("history/provinces/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        DEBUG_Print("prov to regions called");
    #endif

    /* Parse region names, to assign them to the previously initialised regions */
    KENG_CreateRegionNames("history/regions/region_names.ndf");
    #ifdef MAIN_DBG
        DEBUG_Print("region names called");
    #endif
    
    /* Parse country data (RGB values, names) and their unique tags */
    KENG_CreateCountries("history/country/cou.ndf", "history/country/tags.cdf");
    #ifdef MAIN_DBG
        DEBUG_Print("init countries called");
    #endif

    /* Parse ownership data, to assign the regions to the correct country */
    KENG_RegionsToCountry("history/country/ownership.cdf"); 
    #ifdef MAIN_DBG
        DEBUG_Print("regions to countries called");
    #endif

    /* Paints the given province map with the correct country colour */
    KENG_MarkCountries(click_surface, map); /* We use the click map as per usual */
    #ifdef MAIN_DBG
        DEBUG_Print("marking countries called");
    #endif

    /* Paints the borders inbetween countries and provinces */
    KENG_MarkInnerBorders(click_surface, inner_border_map); /* FIXME: Marks coastlines and rivers as well, when it shouldn't */
    #ifdef MAIN_DBG
        DEBUG_Print("border generation called");
    #endif

    /* Prints */
    #ifdef MAIN_PRINTS
        KENG_PrintRegions();
        KENG_PrintCountries();
        KENG_PrintCountryColours();
        KENG_PrintProvinces();
        #ifdef MAIN_DBG
            DEBUG_Print("Prints Completed\n");
        #endif
    #endif

    /* Initialise PeakyGUI province box */
    PGUI_CreateProvinceInspector(renderer);
    #ifdef PGUI_PRINT
        DEBUG_Print("Province Inspector initialised\n");
    #endif
    PGUI_CreateCountryBar(&countries[0], renderer); /* It will take the player country data */
    #ifdef PGUI_PRINT
        DEBUG_Print("Country Top Bar initialised\n");
    #endif

    /* IT APPEARS THAT THE (CLEAR -> RENDERCOPY -> PRESENT) METHOD IS GPU ACCELERATED... */

    /* Game */
    bool quit = false;
    int cycles = 0;
    while(!quit){
        /* TODO: Refactor Renditions, into one function, and their names */
        SDL2_RenderMap(renderer, textures, cam);
        SDL2_DrawUnits(cam);
        SDL2_RenderGoodsBar();

        SDL2_HandleEvents(quit, cam);

        PGUI_DrawItems(renderer);

        /* Text has to be in front of the GUI items */
        /* We first render, then we update */
        SDL2_RenderCountryStats(&countries[0]);

        SDL2_RenderProvinceInfo(clicked_province);
        PGUI_UpdateProvinceInspector(clicked_province, renderer);
        
        SDL_RenderPresent(renderer);

        cycles++;
        if(KENG_gamePause == 0){
            if(cycles % (*KENG_gameSpeed) == 0){ /* We can manipulate this to simulate game speed, we dont update if we want
            to pause the game */
                /* Update the timer, to simulate change after 12 cycles */
                KENG_UpdateClock();
                KENG_UpdateProvincePopulations(&countries[0]);
                KENG_UpdateCountryStats(&countries[0]);
            }
        }
    }

    /* Cleanup */
    SDL2_Cleanup(win, renderer);

    return EXIT_SUCCESS;
}
