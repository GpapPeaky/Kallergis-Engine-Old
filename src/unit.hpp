#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstring>
#include "pixels.hpp"
#include "country.hpp"
#include "province.hpp"
#include "hashtable.hpp"
#include "camera.hpp"

typedef enum unit_types{
    INFANTRY = 0,
    ARTILLERY = 1,
    ARMOR = 2,
    MECHANISED = 3
}unit_t;

#ifndef UNITS
/**
 * @brief Military units are handled here
 */
#define UNITS

typedef struct unit{
    /* Stats */
    int men;
    int att;
    int def;
    /* Image data */
    SDL_Texture* img;
    SDL_Rect rect;
    /* Handles most stats */
    unit_t type;
    /* Owner */
    std::string owner_tag;
    uint id;
    uint prov_visited;
}unit;

extern SDL_Texture* inf;
extern SDL_Texture* art;
extern SDL_Texture* arm;
extern SDL_Texture* mec;
extern std::vector<unit> units;

/**
 * @brief Initialises the textures for each unit type
 */
void init_unit_assets(void);

/**
 * @brief Creates a unit
 * 
 * @param type Type of unit
 * @param country For what country
 * @param prov_id In what province to show the unit
 * @param surface what surface to scan for the position
 * @param cam for unit postitions
 */
void create_unit(unit_t type, cou country, int prov_id, SDL_Surface* surface);

/**
 * @brief Draws units

 * @param camera transform unit positions
 */
render_capable draw_units(camera cam);

#endif
