#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include <cstring>
#include "SDL2_Pixel.hpp"
#include "SDL2_Camera.hpp"
#include "KENG_Country.hpp"
#include "KENG_Province.hpp"

#ifndef _KENG_UNITS_HPP_
/**
 * @brief Military units are handled here
 */
#define _KENG_UNITS_HPP_

/**
 * @brief Unit types
 */
typedef enum unit_types{
    INFANTRY = 0,
    ARTILLERY = 1,
    ARMOR = 2,
    MOTORISED = 3
}unit_t;

/**
 * @brief Unit object
 */
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
    Uint id;
    Uint prov_visited;
}unit;

extern unit* selected_unit;
extern SDL_Texture* inf;
extern SDL_Texture* art;
extern SDL_Texture* arm;
extern SDL_Texture* mot;
/* TODO: Make this a field for each country, let's avoid another global */
extern std::vector<unit> units;

/**
 * @brief Initialises the textures for each unit type
 * 
 * @returns 1 on failure, 0 on success
 */
int KENG_CreateUnitAssets(void);

/**
 * @brief Generates unit coordinates, per province
 * 
 * @param surface Surface to scan for coordinates
 * 
 * @returns 1 on failure, 0 on success
 */
int KENG_GenerateUnitCoords(SDL_Surface* surface);

/**
 * @brief Creates a unit
 * 
 * @param type Type of unit
 * @param country For what country
 * @param prov_id In what province to show the unit
 * @param surface what surface to scan for the position
 * @param cam for unit postitions and to reduce the time it takes to scan the image
 */
void KENG_CreateUnit(unit_t type, KENG_country country, int prov_id, SDL_Surface* surface, camera cam);

/**
 * @brief Moves the selected unit
 * 
 * @param surface Surface to check (clickmap)
 * @param camera to transform unit positions
 * 
 * @warning If A provinece is too big and a part of it is outside of the camera view when clicked, the unit will move on the middle of the PART of the province the camera views
 *          . For this reason, provinces should be small, and have to either be whole onto the screen, or not at all. If a province is half shown, even if it is small, the unit
 *          will move almost to the center, with a small margin of error.
 */
void KENG_MoveUnit(SDL_Surface* surface, camera cam);

/**
 * @brief Draws units
 *
 * @param camera to transform unit positions
 */
void SDL2_DrawUnits(camera cam);

/**
 * @brief Highlights the selected unit
 * 
 * @param camera transform unit positions
 */
void KENG_HiglightSelectedUnit(camera cam);

#endif
