#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "init_win.h"
#include "utils.h"
#include "enemy.h"

#ifndef UI
#define UI

extern SDL_Color text_colour;
extern SDL_Color text_colour_bg;
extern SDL_Surface * text;
extern SDL_Texture * txt;
extern SDL_Texture * b_txt;
extern TTF_Font* font;
extern SDL_FRect rect;
extern SDL_FRect b_rect;
extern SDL_FRect c_rect;

/**
 * @brief Presents data in the UI section of the screen
 * 
 * @param msg Message to display
*/
Render_t render_on_player(const char* msg);

/**
 * @brief Updates the UI stats
*/
Update_t update_stats(void);

/**
 * @brief Initialises The UI
*/
Init_t init_font(void); 

/**
 * @brief Renders Text based on a string
 * 
 * @param msg Message to appear
 * @param position Rectangle to be placed at
*/
Render_t render_text(std::string msg, SDL_FRect* position);

/**
 * @brief Renders stats on hovering a sprite with the mouse
*/
Render_t render_on_mouse_hover(void);

/**
 * @brief checks if the mouse is over a sprite
 * 
 * @param enemy Sprite to check
 * @param x X value of the mouse
 * @param y Y value of the mouse
 * 
 * @returns true If true
 *                 false if not
*/
bool mouse_over_sprite(Enemy enemy, int x, int y);

#endif/* UI */
