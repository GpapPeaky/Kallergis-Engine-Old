#include "province.h"
#include "regions.h"
#include "country.h"
#include "hashtable.h"
#include "init_win.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdlib.h>
#include <fstream>
#include <regex>
#include <string>

#ifndef INIT_MAP
#define INIT_MAP

extern std::vector<reg>  regions; /* Contains data for each region */
extern SDL_Surface* map_surface;
extern SDL_Texture* map_texture;
extern SDL_Surface* map_bg_surface;
extern  SDL_Texture* map_bg_texture;

/**
 * @brief Selects and image for a map
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable init_map(void);

/**
 * @brief parses data from mdf, to assign ma data of provinces to each region
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable prov_to_reg(const std::string fname);

/**
 * @brief parses data from ndf, to assign a name to each region
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable reg_names(const std::string fname);

/**
 * @brief assigns regions to countries
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable reg_to_country(const std::string fname);

/**
 * @brief prints all regions, along with their data
*/
void print_regions(void);

/**
 * @brief prints all countries along with their data
*/
void print_countries(void);

/**
 * @brief Prints the provinces from the province hashtable
 */
void print_provinces(void);

#endif