#include "SDL.h"
#include "SDL_rect.h"
#include <iostream>

#ifndef __PGUI_PRIMITIVES_H__
#define __PGUI_PRIMITIVES_H__

typedef bool PGUI_Bool;
#define PGUI_IsButton true
#define PGUI_IsNotButton false

#define PGUI_True true
#define PGUI_False false

typedef SDL_Rect PGUI_Rect;

#define PGUI_UNDECIDED_VALUE 26112004

typedef struct PGUI_background{
    SDL_Surface* surface;
    SDL_Texture* texture;
}PGUI_Background;

typedef void (*PGUI_ButtonAction)();

#endif
