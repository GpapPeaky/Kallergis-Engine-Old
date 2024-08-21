#include "goods.hpp"

const char* goods_names[18] = {
    "COAL",
    "IRON",
    "STEEL",
    "FABRIC",
    "WOOD",
    "ARMS",
    "OIL",
    "RUBBER",
    "GUNPOWDER",
    "GOLD",
    "COPPER",
    "LEATHER",
    "FISH",
    "GLASS",
    "GEMS",
    "STONE",
    "PAPER",
    "FOOD"
};

std::unordered_map<std::string, product> product_map = {
    {"COAL", COAL}, {"IRON", IRON}, {"STEEL", STEEL},
    {"FABRIC", FABRIC}, {"WOOD", WOOD}, {"ARMS", ARMS},
    {"OIL", OIL}, {"RUBBER", RUBBER}, {"GUNPOWDER", GUNPOWDER},
    {"GOLD", GOLD}, {"COPPER", COPPER}, {"LEATHER", LEATHER},
    {"FISH", FISH}, {"GLASS", GLASS}, {"GEMS", GEMS},
    {"STONE", STONE}, {"PAPER", PAPER}, {"FOOD", FOOD}
};

float GP(local_prd local_production){
    switch(local_production.good){
        case COAL:
            return static_cast<float>(local_production.population) / 1000;
            break;
        case IRON:
            return static_cast<float>(local_production.population) / 1500;
            break;
        case STEEL:
            return static_cast<float>(local_production.population) / 2500;
            break;
        case FABRIC:
            return static_cast<float>(local_production.population) / 700;
            break;
        case WOOD:
            return static_cast<float>(local_production.population) / 450;
            break;
        case ARMS:
            return static_cast<float>(local_production.population) / 1700;
            break;
        case OIL:
            return static_cast<float>(local_production.population) / 2750;
            break;
        case RUBBER:
            return static_cast<float>(local_production.population) / 3000;
            break;
        case GUNPOWDER:
            return static_cast<float>(local_production.population) / 1600;
            break;
        case GOLD:
            return 0.0f; /* There will be added +0.5 to the income no matter what */
            break;
        case COPPER:
            return static_cast<float>(local_production.population) / 1150;
            break;
        case LEATHER:
            return static_cast<float>(local_production.population) / 350;
            break;
        case FISH:
            return static_cast<float>(local_production.population) / 150;
            break;
        case GLASS:
            return static_cast<float>(local_production.population) / 2200;
            break;
        case GEMS:
            return static_cast<float>(local_production.population) / 4500;
            break;
        case STONE:
            return static_cast<float>(local_production.population) / 200;
            break;
        case PAPER:
            return static_cast<float>(local_production.population) / 550;
            break;
        case FOOD:
            return static_cast<float>(local_production.population) / 222;
            break;
    default:
        break;
    }
}
