#include "pgui_primitives.hpp"
#include "pgui_component.hpp"
#include "pgui_action.hpp"

#ifndef __PGUI_BUTTON_H__
#define __PGUI_BUTTON_H__

typedef struct PGUI_button{
    PGUI_Component component;
    PGUI_ActionArguments actionArgs;
}PGUI_Button;

/**
 * @brief Creates a PGUI button
 * 
 * @param action function to call when the button is pressed
 * @param component button's components for rendering
 * 
 * @returns a pointer to the created button
 */
PGUI_Button* PGUI_CreateButton(PGUI_ActionArguments action, PGUI_component component);

/**
 * @brief Creates a PGUI button, better writing
 * 
 * @param action function to call when the button is pressed
 * @param x x axis
 * @param y y axis
 * @param buttonImage button's image
 * @param rnd renderer
 * 
 * @returns a pointer to the created button
 */
PGUI_Button* PGUI_CreateButtonComplete(PGUI_ActionArguments action, int x, int y, SDL_Surface* buttonImage, SDL_Renderer* rnd);

/**
 * @brief Wrapper function for creating buttons
 * 
 * @param args arguments
 * @note action function to call when the button is pressed
 * @note x x axis
 * @note y y axis
 * @note buttonImage button's image
 * @note rnd renderer
 * 
 * @returns a pointer to the created button
 */
PGUI_Wrap PGUI_CreateButtonWrapper(PGUI_ArgumentVector args);

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

/**
 * @brief Deletes a specified button
 * 
 * @param button button to delete
 */
void PGUI_DeleteButton(PGUI_Button* button);

#endif
