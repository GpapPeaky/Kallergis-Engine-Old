#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstring>
#include "country.hpp"

typedef enum unit_types{
    INFANTRY = 0,
    ARTILLERY = 1,
    ARMOR = 2,
    MECHANISED = 3
}unit_t;

typedef struct unit{
    /* Stats */
    int men;
    int att;
    int def;
    /* Image data */
    SDL_Surface* img;
    SDL_Rect rect;
    /* Handles most stats */
    unit_t type;
    /* Owner */
    std::string owner_tag;
    uint id;
}unit;

extern std::vector<unit> units;

/**
 * @brief Creates a unit
 * 
 * @param type Type of unit
 * @param country For what country
 * @param x x axis
 * @param y y axis
 */
void create_unit(unit_t type, cou country, int x, int y);

/**
 * @brief Draws units

 * @param screen Where to draw the units
 */
render_capable draw_units(SDL_Surface* screen);
