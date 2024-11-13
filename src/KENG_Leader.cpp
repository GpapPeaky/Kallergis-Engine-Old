#include "KENG_Leader.hpp"

std::string leaderPath = "assets/gfx/leaders/countryLeaders/";

KENG_leader* KENG_CreateCountryLeader(std::string leaderName, std::string leaderIconName, SDL_Renderer* renderer){
    KENG_leader* newLeader = new KENG_leader;
    std::string leaderFileName = leaderPath + leaderIconName;

    SDL_Surface* leaderIconSurface = IMG_Load(leaderFileName.c_str());
    if(!leaderIconSurface){
        std::printf("Failed to load country leader's %s surface\n", leaderName.c_str());
    }
    newLeader->leaderIcon = SDL_CreateTextureFromSurface(renderer, leaderIconSurface);
    if(!newLeader->leaderIcon){
        std::printf("Failed to load country leader's %s texture\n", leaderName.c_str());
    }
    newLeader->leaderName = leaderName;

    SDL_FreeSurface(leaderIconSurface);

    return newLeader;
}
