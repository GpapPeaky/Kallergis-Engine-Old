#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstring>
#include "country.hpp"
#include "province.hpp"
#include "hashtable.hpp"

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
 * @param prov_id In what province to show the unit
 * @param surface what surface to scan for the position
 */
void create_unit(unit_t type, cou country, int prov_id, SDL_Surface* surface);

/**
 * @brief Draws units

 * @param screen Where to draw the units
 */
render_capable draw_units(SDL_Surface* screen);
