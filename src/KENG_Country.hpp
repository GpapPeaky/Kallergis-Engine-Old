#include <regex>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

#include "KENG_Region.hpp"
#include "KENG_Leader.hpp"

#include "auxf/modules.aux"

#ifndef COU
/**
 * @brief Countries structs, definitions, initialisation functions and other tools
 */
#define COU

/* Country colour alpha */
#define KENG_COUNTRY_ALPHA 150

typedef struct KENG_country{
    std::string country_name;
    std::string tag;
    std::vector<reg> country_regs;
    SDL_Surface* country_flag;
    SDL_Color country_rgb;
    Uint units_num;
    /* Top bar */
    float balance;
    Uint manpower;
    int stab;
    /* Leader */
    KENG_leader* countryLeader;
}KENG_country;

/**
 * @brief Contains all the created country objects
 */
extern std::vector<KENG_country> KENG_globalCountries; /* Contains data for each country */

/**
 * @brief initialises the countries name-tag and rgb value
 * 
 * @param cou Countries file tag -> rgb
 * @param tags tag file name -> tag
 * @param leadersFile leader file name -> leader struct
 * 
 * @returns 1 on failure
 *                0 on success
*/
int KENG_CreateCountries(const std::string cou, const std::string tags, const std::string leadersFile);

/**
 * @brief gets the country object of a specific tag
 * 
 * @param tag Country tag
 * 
 * @returns pointer to the country object
 */
KENG_country* KENG_GetCountry(std::string tag);

/**
 * @brief Renders the leader of a specififed country
 * 
 * @param country country to render the leader of
 * @param renderer which renderer to use for the image
 */
void SDL2_RenderCountryLeader(KENG_country* country, SDL_Renderer* renderer);

#endif
