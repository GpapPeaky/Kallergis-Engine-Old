#pragma once

#include "SDL2_Images.hpp"

#include <string>           /* For std::to_string in the BSC_RenderStat function */
#include <cmath>            /* For std::fabs in the BSC_RenderStat function */

/**
 * @brief Object for handling fonts (text)
 * as textures (no need to cache)
 */
typedef struct SDL2_TextureFont{
    unsigned int fontSize;      /* Size of text */
    SDL2_Images font;           /* Font data (spritesheet) */
    unsigned int sheetWidth;    /* Font sheet width */
    unsigned int sheetHeight;   /* Font sheet height */
    unsigned int letterSpace;   /* Space between each letter */
}SDL2_TextureFont;

/**
 * @brief Space between 2 letters (2px)
 */
#define KENG_LETTER_SPACE 2

/**
 * @brief Small tolerance of error in float comparison
 */
#define KENG_EPSILON 0.0000001f

/**
 * @brief Font global
 * 
 * @attention letter sprite is (9x9) and the
 * sheet is of size 8x5
 */
extern SDL2_TextureFont* KENG_CWWBFont;

/**
 * @brief Initialises the font from the font spritesheet
 * 
 * @param filename Font spritesheet
 * @param fontSize Size of font
 * 
 * @returns The created font
 */
SDL2_TextureFont* SDL2_CreateTextureFont(const char* filename, unsigned int fontSize);

/**
 * @brief Maps a character to the font sheet coordinates
 * to render it
 * 
 * @warning Only supports the CWWB font sheet
 * 
 * @param font Font sheet to use
 * @param c Character to map
 * 
 * @returns A source rectangle, for the rendering
 */
SDL_Rect SDL2_MapCharacterToTextureFont(SDL2_TextureFont* font, char c);

/**
 * @brief Renders a character with a font
 * 
 * @param font Font to use
 * @param c Character to render
 * @param x X coordinate
 * @param y Y coordinate
 */
void SDL2_RenderFontCharacter(SDL2_TextureFont* font, char c, int x, int y);

/**
 * @brief Renders a string with a font
 * 
 * @param font Font to use
 * @param str String to render
 * @param x X coordinate
 * @param y Y coordinate
 */
void SDL2_RenderFontText(SDL2_TextureFont* font, const char* str, int x, int y);

/**
 * @brief Renders a float like the %.2f
 * delimeter in the print functions
 * 
 * @param value Value to render
 * 
 * @returns The created string
 */
std::string SDL2_2PointFloatString(float value);
