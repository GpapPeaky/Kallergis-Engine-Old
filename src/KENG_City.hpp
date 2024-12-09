#ifndef __KENG_CITY_HPP__
/**
 * @brief City objects for the map, on a seperate thread
 */
#define __KENG_CITY_HPP__

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "SDL2_Font.hpp"
#include "SDL2_Camera.hpp"
#include <unordered_map>
#include <string>

typedef struct KENG_City{
    SDL_Rect cityRect;
    std::string cityName;
    SDL_Surface* citySurface;
    SDL_Texture* cityTexture;
}KENG_City;

extern std::unordered_map<int, KENG_City> KENG_Cities;

/**
 * @brief Generates an ID based on the previously generate ones
 * 
 * @returns The generated ID
 */
static int KENG_GenerateCityID(void);

/**
 * @brief Creates a city to load onto the map, saves the object in KENG_Cities
 * 
 * @param x X axis (relative to the bitmap)
 * @param y Y axis
 * @param cityName Name of the city
 * @param citySurface City indicator
 * @param rnd Renderer to use
 * 
 * @returns 0 on success, 1 on failure
 */
int KENG_CreateCity(int x, int y, std::string cityName, SDL_Surface* citySurface, SDL_Renderer* rnd);

/**
 * @brief Renders the cities 
 * 
 * @param rnd Renderer to use
 * @param cam Camera, for scaling
 * 
 * @attention Quite the expensive function, for that we will run it on a different thread
 */
void SDL2_RenderCities(SDL_Renderer* rnd, camera cam);

#endif
