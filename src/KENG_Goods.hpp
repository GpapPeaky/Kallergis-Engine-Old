#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <unordered_map>
#include "SDL2_Window.hpp"
#include "auxf/definitions.aux"

#ifndef GOODS
/**
 * @brief Goods for provinces
 */
#define GOODS

extern const char* goods_names[18];
extern SDL_Texture* goods_textures[18];

/**
 * @brief 18 different goods can be produced
 */
typedef enum product{
    COAL, IRON, STEEL, FABRIC, WOOD, ARMS, OIL, RUBBER, GUNPOWDER,
    GOLD, COPPER, LEATHER, FISH, GLASS, GEMS, STONE, PAPER, FOOD
}product;

typedef struct local_prd{
    Uint population;
    product good;
}local_prd;

extern std::unordered_map<std::string, product> product_map;

/**
 * @brief Intialises the goods textures
 * 
 * @returns 1 on failure, 0 on success
 */
int KENG_CreateGoods(void);

/**
 * @brief Renders the goods bar onto the screen
 */
void SDL2_RenderGoodsBar(void);

#endif