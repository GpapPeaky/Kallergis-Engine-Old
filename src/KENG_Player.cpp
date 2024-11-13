#include "KENG_Player.hpp"

KENG_player* KENG_mainPlayer;

KENG_player* KENG_CreatePlayer(KENG_country* playerCountry, std::string playerName, Uint playerID){
    KENG_player* newPlayer = new KENG_player;

    newPlayer->playerCountry = playerCountry;
    newPlayer->playerID = playerID;
    newPlayer->playerName = playerName;

    return newPlayer;
}

void KENG_CreateMainPlayer(KENG_country* playerCountry, std::string playerName, Uint playerID){
    KENG_mainPlayer = KENG_CreatePlayer(playerCountry, playerName, playerID);

    return;
}

void KENG_PrintPlayerAttributes(void){
    printf("Main player %s, ID: %d, Country: %s\n", KENG_mainPlayer->playerName.c_str(),\
    KENG_mainPlayer->playerID, KENG_mainPlayer->playerCountry->country_name.c_str());

    return;
}
