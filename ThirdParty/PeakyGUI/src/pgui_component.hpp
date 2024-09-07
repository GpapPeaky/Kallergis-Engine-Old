#include "pgui_primitives.hpp"

#ifndef __PGUI_COMPONENT_H__
#define __PGUI_COMPONENT_H__

typedef struct PGUI_component{
    PGUI_Rect rect;
    PGUI_Background background;
    PGUI_Bool status;
}PGUI_Component;

/**
 * @brief Gets the attributes of a component, by reference
 * 
 * @param component component to get the attributes from
 * @param x x position
 * @param y y position
 * @param w width
 * @param h height
 * @param background image data, (SDL_Surface* / SDL_Texture* )
 * @param status button status or not
 * 
 * @attention NULL can be put on fields that are not required by the caller 
 */
void PGUI_GetComponentAttributes(PGUI_Component component, int* x, int* y, int* w, int* h, PGUI_Background* background, PGUI_Bool* status);

/**
 * @brief Creates a new comonent
 * 
 * @param x x position
 * @param y y position
 * @param w width
 * @param h height
 * @param surface background surface
 * @param rnd renderer
 * 
 * @attention the status of each component is declared when a button or background are created
 * @attention the width and height are overiden by the surface's dimensions
 */
PGUI_Component PGUI_CreateComponent(int x, int y, int w, int h, SDL_Surface* surface, SDL_Renderer* rnd);

/**
 * @brief Prints the attributes of a component
 * 
 * @param component component to print 
 */
void PGUI_PrintComponent(PGUI_Component component);

#endif
