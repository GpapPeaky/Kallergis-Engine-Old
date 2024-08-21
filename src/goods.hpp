#include <stdio.h>
#include <unordered_map>
#include "../src/auxf/definitions.aux"

#ifndef GOODS
/**
 * @brief Goods for provinces
 */
#define GOODS

extern const char* goods_names[18];

/**
 * @brief 18 different goods can be produced
 */
typedef enum product{
    COAL, IRON, STEEL, FABRIC, WOOD, ARMS, OIL, RUBBER, GUNPOWDER,
    GOLD, COPPER, LEATHER, FISH, GLASS, GEMS, STONE, PAPER, FOOD
}product;

typedef struct local_prd{
    uint population;
    product good;
}local_prd;

extern std::unordered_map<std::string, product> product_map;

/**
 * @brief Calculates the local goods produced
 * 
 * @param local_production Local produce
 * 
 * @returns the amount of goods produced
 */
float GP(local_prd local_production);

#endif