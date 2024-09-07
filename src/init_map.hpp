#include "economy.hpp"
#include "province.hpp"
#include "regions.hpp"
#include "country.hpp"
#include "hashtable.hpp"
#include "init_win.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "auxf/definitions.aux"
#include <stdlib.h>
#include <fstream>
#include <regex>
#include <string>

#ifndef INIT_MAP
/**
 * @brief Initialisation functions for the map
 */
#define INIT_MAP

extern std::vector<reg> regions;

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
 * @brief Resizes a bmp surface to w / h
 * 
 * @param surface surface to resize
 * @param w width to resize to
 * @param h height to resize to
 * 
 * @returns The resized surface
 */
SDL_Surface* resize_bitmap(SDL_Surface* surface, float w, float h);

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