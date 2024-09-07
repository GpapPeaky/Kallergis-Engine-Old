#include "pgui_primitives.hpp"
#include "pgui_component.hpp"

#ifndef __PGUI_BUTTON_H__
#define __PGUI_BUTTON_H__

typedef struct PGUI_button{
    PGUI_Component component;
    PGUI_ButtonAction action;
}PGUI_Button;

/**
 * @brief Creats a PGUI button
 * 
 * @param action function to call when the button is pressed
 * @param component button's components for rendering
 * 
 * @returns the created button
 */
PGUI_Button PGUI_CreateButton(PGUI_ButtonAction action, PGUI_component component);

/**
 * @brief Checks if a specific PGUI button is pressed
 * 
 * @param button button to check
 * @param x mouse x position
 * @param y mouse y position
 * 
 * @returns true / false
 */
PGUI_Bool PGUI_ButtonPressed(PGUI_Button button, int x, int y);

/**
 * @brief Executes the action function of a pressed button
 * 
 * @param button button to execute the action allocated
 */
void PGUI_ExecuteButtonAction(PGUI_Button button);

#endif
