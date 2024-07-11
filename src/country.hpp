#include "regions.hpp"
#include <regex>
#include <vector>
#include <fstream>
#include <iostream>

#ifndef COU
/**
 * @brief Countries structs, definitions, initialisation functions and other tools
 */
#define COU

typedef struct country{
    std::string country_name;
    std::string tag;
    std::vector<reg> country_regs;
    SDL_Surface* country_flag;
    SDL_Color country_rgb;
}cou;

extern std::vector<cou> countries; /* Contains data for each country */

/**
 * @brief initialises the countries name-tag and rgb value
 * 
 * @param cou Countries file tag -> rgb
 * @param tags tag file name -> tag
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable init_countries(const std::string cou, const std::string tags);

#endif
