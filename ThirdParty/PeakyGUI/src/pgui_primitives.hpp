#include "../../SDL2/include/SDL2/SDL.h"
#include "../../SDL2/include/SDL2/SDL_image.h"
#include "PGUI_debug.hpp"
#include <iostream>



/* TODO: Might add namespaces for more flexible c++ use */

#ifndef __PGUI_PRIMITIVES_H__
#define __PGUI_PRIMITIVES_H__

typedef unsigned int Uint;
typedef bool PGUI_Bool;

/* Redundant definitions */
#define PGUI_SHOWN true
#define PGUI_HIDDEN false

#define PGUI_True true
#define PGUI_False false

typedef SDL_Rect PGUI_Rect;

#define PGUI_UNDECIDED_VALUE 26112004

#define PGUI_EXIT_SUCCESS 0
#define PGUI_EXIT_FAIL -1

typedef struct PGUI_background{
    SDL_Surface* surface;
    SDL_Texture* texture;
}PGUI_Background;

#endif
