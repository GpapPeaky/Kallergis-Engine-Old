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
    camera KENG_SDL2camera = SDL2_CreateCamera();
    /* Initialise the window and renderer */
    SDL2_CreateWindowAndRenderer("Keng");
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
        KENG_DebugPrint("init called");
    #endif

    /* Parse provinces, (RGB values, names, ids ect.) and add them to the respective region (regions are initialised here as well...) */
    KENG_ProvinceToRegion("history/provinces/provinces.mdf"); /* Relative to the executable location */ 
    #ifdef MAIN_DBG
        KENG_DebugPrint("prov to regions called");
    #endif

    /* Parse region names, to assign them to the previously initialised regions */
    KENG_CreateRegionNames("history/regions/region_names.ndf");
    #ifdef MAIN_DBG
        KENG_DebugPrint("region names called");
    #endif
    
    /* Parse country data (RGB values, names) and their unique tags */
    KENG_CreateCountries("history/country/cou.ndf", "history/country/tags.cdf", "history/country/leaders.cdf");
    #ifdef MAIN_DBG
        KENG_DebugPrint("init countries called");
    #endif

    /* Parse ownership data, to assign the regions to the correct country */
    KENG_RegionsToCountry("history/country/ownership.cdf"); 
    #ifdef MAIN_DBG
        KENG_DebugPrint("regions to countries called");
    #endif

    /* Paints the given province map with the correct country colour */
    KENG_MarkCountries(KENG_clickSurface, map); /* We use the click map as per usual */
    #ifdef MAIN_DBG
        KENG_DebugPrint("marking countries called");
    #endif

    /* Generate the unit coords */
    KENG_GenerateUnitCoords(KENG_clickSurface);
    #ifdef MAIN_DBG
        KENG_DebugPrint("generating unit coords called");
    #endif

    /* Paints the borders inbetween countries and provinces */
    KENG_MarkInnerBorders(KENG_clickSurface, inner_border_map); /* FIXME: Marks coastlines and rivers as well, when it shouldn't */
    #ifdef MAIN_DBG
        KENG_DebugPrint("border generation called");
    #endif

    /* Player Initialisation */
    KENG_CreateMainPlayer(KENG_GetCountry("HER"), "Peaky", 1);
    #ifdef MAIN_DBG
        KENG_PrintPlayerAttributes();
        KENG_DebugPrint("Player initialised\n");
    #endif

    /* Cities */
    KENG_CreateCitiesFromFile("history/cities/cities.mdf", renderer);
    #ifdef MAIN_DBG
        KENG_DebugPrint("cities created");
    #endif

    /* Prints */
    #ifdef MAIN_PRINTS
        KENG_PrintRegions();
        KENG_PrintCountries();
        KENG_PrintCountryColours();
        KENG_PrintProvinces();
        #ifdef MAIN_DBG
            KENG_DebugPrint("Prints Completed\n");
        #endif
    #endif

    /* Overload the PGUI path */
    PGUI_AssetPath = "ThirdParty/PeakyGUI/assets/";
    PGUI_CreateCountryBar(KENG_mainPlayer->playerCountry, renderer); /* It will take the player country data */
    #ifdef PGUI_PRINT
        KENG_DebugPrint("Country Top Bar initialised\n");
    #endif
    PGUI_CreateProvinceInspector(renderer);
    #ifdef PGUI_PRINT
        KENG_DebugPrint("Province Inspector initialised\n");
    #endif
    PGUI_CreateCountryLeaderOverview(renderer);
    #ifdef PGUI_PRINT
        KENG_DebugPrint("Leader Overview initialised\n");
    #endif

    // PGUI_CreateCalendar(renderer);

    /* TODO: Initial units, parse from file */
    KENG_CreateUnit(ARMOR, *KENG_GetCountry("HER"), 1, KENG_clickSurface, KENG_SDL2camera);
    KENG_CreateUnit(INFANTRY, *KENG_GetCountry("HER"), 2, KENG_clickSurface, KENG_SDL2camera);
    KENG_CreateUnit(MOTORISED, *KENG_GetCountry("HER"), 3, KENG_clickSurface, KENG_SDL2camera);
    KENG_CreateUnit(ARTILLERY, *KENG_GetCountry("HER"), 4, KENG_clickSurface, KENG_SDL2camera);

    srand(time(NULL));

    /* CITIES THREAD */
    /* TODO: Initialise the city thread parameters */

    /* Game */
    bool SDL2_quit = false;
    Uint KENG_gameCycles = 0;
    while(!SDL2_quit){
        // std::lock_guard<std::mutex> lock(KENG_CityRenderMutex);
        /* TODO: Refactor Renditions, into one function, and their names */
        SDL2_RenderMap(renderer, textures, KENG_SDL2camera);
        SDL2_RenderCities(renderer, KENG_SDL2camera); /* Render behind PGUI, and the units, THREADED */
        SDL2_DrawUnits(KENG_SDL2camera);

        SDL2_HandleEvents(SDL2_quit, KENG_SDL2camera);

        PGUI_DrawItems(renderer);
        SDL2_RenderGoodsBar();

        /* Text has to be in front of the GUI items */
        /* We first render, then we update */
        SDL2_RenderCountryStats(KENG_mainPlayer->playerCountry); /* For the player */

        SDL2_RenderProvinceInfo(clicked_province);
        PGUI_UpdateProvinceInspector(clicked_province, renderer);

        SDL2_RenderLeaderName(KENG_mainPlayer->playerCountry, renderer); /* For the player */
        
        SDL_RenderPresent(renderer);

        KENG_gameCycles++;
        if(KENG_gamePause == NOT_PAUSED){
            if(KENG_gameCycles % KENG_gameSpeed == 0){ /* We can manipulate this to simulate game speed, we dont update if we want
            to pause the game */
                /* Update the timer, to simulate change after 12 cycles */
                KENG_UpdateClock();
                KENG_UpdateProvincePopulations();
                KENG_UpdateCountryStats();
            }
        }
    }

    /* Cleanup */
    SDL2_Cleanup(win, renderer);

    return EXIT_SUCCESS;
}
