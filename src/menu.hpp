#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../auxf/definitions.aux"

extern SDL_Surface* menu;

#ifndef MENU
/**
 * @brief Menu and buttons UI interface
 */
#define MENU

typedef struct button{
    SDL_Rect rect;
    const char* text;
    SDL_Surface* img;
}button;

extern std::vector<button*> buttons;

/**
 * @brief Creates a button to a specified screen
 * 
 * @param screen_to_copy_to Where to copy the button
 * @param text Unique text for the purpose of the button (used later in a function)
 * @param file file name for the button's surface
 * @param x x axis
 * @param y axis
 * 
 * @returns A pointer to the created button
 */
button* create_button(SDL_Surface* screen_to_copy_to, const char* text, const char* file, int x, int y);

/**
 * @brief Deletes a button
 * 
 * @param but button to delete
 */
void delete_button(button* but);

/**
 * @brief Cleans the buttons vector of all buttons
 */
void buttons_cleanup(void);

/**
 * @brief Initialises the menu
 * 
 * @param filename Filename of background .bmp file
 */
void init_menu(std::string filename);

/**
 * @brief Draws created buttons on teh screen
 */
render_capable draw_buttons(void);

/**
 * @brief The most important function for buttons, since interactions are handled through here
 *          It scans for the button pressed and returns a pointer to it
 * 
 * @returns A pointer to the interacted button
 */
button* check_for_button_interaction(void);

#endif
