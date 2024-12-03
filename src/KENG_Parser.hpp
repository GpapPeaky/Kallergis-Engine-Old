#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <fstream>
#include <regex>
#include <string>
#include "SDL2_Window.hpp"
#include "KENG_Economy.hpp"
#include "KENG_Goods.hpp"
#include "KENG_Province.hpp"
#include "KENG_Region.hpp"
#include "KENG_Country.hpp"
#include "KENG_City.hpp"
#include "auxf/definitions.aux"

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
int KENG_ProvinceToRegion(const std::string fname);

/**
 * @brief parses data from ndf, to assign a name to each region
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
int KENG_CreateRegionNames(const std::string fname);

/**
 * @brief assigns regions to countries
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
int KENG_RegionsToCountry(const std::string fname);

/**
 * @brief Creates the cities read from file (cities.mdf)
 * 
 * @param fname File to read
 * @param rnd Renderer to use
 * 
 * @returns 1 on failure
 *              0 on success
 */
int KENG_CreateCitiesFromFile(const std::string fname, SDL_Renderer* rnd);

/**
 * @brief Resizes a bmp surface to w / h
 * 
 * @param surface surface to resize
 * @param w width to resize to
 * @param h height to resize to
 * 
 * @returns The resized surface
 */
SDL_Surface* SDL2_ResizeBitmap(SDL_Surface* surface, float w, float h);

/**
 * @brief prints all regions, along with their data
*/
void KENG_PrintRegions(void);

/**
 * @brief prints all countries along with their data
*/
void KENG_PrintCountries(void);

/**
 * @brief Prints the provinces from the province hashtable
 */
void KENG_PrintProvinces(void);

#endif