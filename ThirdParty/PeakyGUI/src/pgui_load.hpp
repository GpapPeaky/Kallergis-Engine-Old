#include "pgui_primitives.hpp"
#include "pgui_button.hpp"
#include <cstring>
#include <iostream>

#ifndef __PGUI_LOAD_H__
#define __PGUI_LOAD_H__

extern const char* PGUI_AssetPath;

/**
 * @brief Loads a .png form them PGUI assets
 * 
 * @param fname asset to load
 * @param flags flags for the component
 * 
 * @attention flag: PGUI_LOAD_COMPONENT, loads the component normally
 * @attention flag: PGUI_EMPTY_COMPONENT, loads an empty component
 * 
 * @returns the loaded surface (or NULL if empty)
 */
SDL_Surface* PGUI_Load(const char* fname, int flags = PGUI_LOAD_COMPONENT);

#endif
