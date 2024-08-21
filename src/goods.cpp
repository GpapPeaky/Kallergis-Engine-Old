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
    return static_cast<float>(local_production.population / 1000);
}
