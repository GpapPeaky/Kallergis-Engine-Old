#include "KENG_Country.hpp"

#ifndef _KENG_PLAYER_HPP_
/**
 * @brief Player struct, for control over a country
 */
#define _KENG_PLAYER_HPP_

typedef struct KENG_player{
    KENG_country* playerCountry;
    std::string playerName;
    Uint playerID;
}KENG_player;

extern KENG_player* KENG_mainPlayer; 

/**
 * @brief Creates a player, that will facilitate what sort of control he has over the map
 * 
 * @param playerCountry country that the player will control
 * @param playerName player's username
 * @param playerID player's Id
 * 
 * @returns pointer to the created player object
 */
KENG_player* KENG_CreatePlayer(KENG_country* playerCountry, std::string playerName, Uint playerID);

/**
 * @brief Creates the main player, (KENG_mainPlayer)
 *  
 * @param playerCountry country that the player will control
 * @param playerName player's username
 * @param playerID player's Id
 */
void KENG_CreateMainPlayer(KENG_country* playerCountry, std::string playerName, Uint playerID);

/**
 * @brief Prints the attributes of the KENG_mainPlayer
 */
void KENG_PrintPlayerAttributes(void);

#endif
