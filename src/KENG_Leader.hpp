#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

#ifndef _KENG_LEADER_HPP_
/**
 * @brief struct for country leaders
 */
#define _KENG_LEADER_HPP_

typedef struct KENG_leader{
    std::string leaderName;
    SDL_Texture* leaderIcon;
}KENG_leader;

extern std::string leaderPath;

/**
 * @brief Initialises a leader object
 * 
 * @param leaderName name of leader
 * @param leaderIconName name of the icon to render
 * @param renderer where to render the icon
 * 
 * @returns pointer to the created leader
 */
KENG_leader* KENG_CreateCountryLeader(std::string leaderName, std::string leaderIconName, SDL_Renderer* renderer);

#endif
