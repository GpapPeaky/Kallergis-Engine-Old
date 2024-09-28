#include "pgui_load.hpp"

const char* PGUI_AssetPath = "PeakyGUI/assets/";

SDL_Surface* PGUI_Load(const char* fname, int flags){

    /* For no background, if we want to create just a button */
    if(flags == PGUI_EMPTY_COMPONENT){
        SDL_Surface* emptyComponent= SDL_CreateRGBSurface(0, 1, 1,  32, 0, 0, 0, 0); /* Create an empty surface */

        return emptyComponent;
    }

    size_t pathLength = strlen(PGUI_AssetPath) + strlen(fname) + 1;
    char* fullPath = new char[pathLength];

    /* Construct the path */
    snprintf(fullPath, pathLength, "%s%s", PGUI_AssetPath, fname);

    SDL_Surface* surface = IMG_Load(fullPath);
    
    /* Check for errors */
    if(surface == nullptr){
        std::cerr << "Error loading image: " << IMG_GetError() << std::endl;
    }

    delete[] fullPath;
    return surface;
 }
 