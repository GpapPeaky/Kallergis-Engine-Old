#include "KENG_Goods.hpp"

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

SDL_Texture* goods_textures[18];

std::unordered_map<std::string, product> product_map = {
    {"COAL", COAL}, {"IRON", IRON}, {"STEEL", STEEL},
    {"FABRIC", FABRIC}, {"WOOD", WOOD}, {"ARMS", ARMS},
    {"OIL", OIL}, {"RUBBER", RUBBER}, {"GUNPOWDER", GUNPOWDER},
    {"GOLD", GOLD}, {"COPPER", COPPER}, {"LEATHER", LEATHER},
    {"FISH", FISH}, {"GLASS", GLASS}, {"GEMS", GEMS},
    {"STONE", STONE}, {"PAPER", PAPER}, {"FOOD", FOOD}
};

err_capable KENG_CreateGoods(void){
    SDL_Surface* src = IMG_Load("assets/gfx/goods/arms.png");
    goods_textures[ARMS] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/coal.png");
    goods_textures[COAL] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/copper.png");
    goods_textures[COPPER] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/fabric.png");
    goods_textures[FABRIC] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/fish.png");
    goods_textures[FISH] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/food.png");
    goods_textures[FOOD] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/gems.png");
    goods_textures[GEMS] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/glass.png");
    goods_textures[GLASS] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/gold.png");
    goods_textures[GOLD] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/gunpowder.png");
    goods_textures[GUNPOWDER] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/iron.png");
    goods_textures[IRON] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/leather.png");
    goods_textures[LEATHER] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/oil.png");
    goods_textures[OIL] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/paper.png");
    goods_textures[PAPER] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/rubber.png");
    goods_textures[RUBBER] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/steel.png");
    goods_textures[STEEL] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/stone.png");
    goods_textures[STONE] = SDL_CreateTextureFromSurface(renderer, src);

    src = IMG_Load("assets/gfx/goods/wood.png");
    goods_textures[WOOD] = SDL_CreateTextureFromSurface(renderer, src);

    for(int i = 0 ; i < 18 ; i++){
        if(!goods_textures[i]){
            std::printf("Failed To Load Good Texture %d\n", i);
            return FAIL;
        }
    }

    return SUCCESS;
}

/* TODO: make it so that we can put it anywhere */
render_capable SDL2_RenderGoodsBar(void){
    int i = 0;
    for(int j = 0 ; j < 270 + (GOODS_BAR_HORIZONTAL_PX_THRESHOLD * (GOODS_N / 2) - 1) ; /* (goods / 2) * goods_size + threshold * (goods - 1) */ j += (GOOD_SIZE + GOODS_BAR_HORIZONTAL_PX_THRESHOLD)){
        SDL_Rect rect;
        rect.w = GOOD_SIZE;
        rect.h = GOOD_SIZE;
        rect.x = j;
        rect.y = GOODS_BAR_VERTICAL_PX_THRESHOLD;
        SDL_RenderCopy(renderer, goods_textures[i], NULL, &rect);
        i++;
    }
    for(int j2 = 0 ; j2 < 270 + (GOODS_BAR_HORIZONTAL_PX_THRESHOLD * (GOODS_N / 2) - 1) ; j2 += (GOOD_SIZE + GOODS_BAR_HORIZONTAL_PX_THRESHOLD)){
        SDL_Rect rect;
        rect.w = GOOD_SIZE;
        rect.h = GOOD_SIZE;
        rect.x = j2;
        rect.y = 2 * GOODS_BAR_VERTICAL_PX_THRESHOLD + UNIT_SIZE;
        SDL_RenderCopy(renderer, goods_textures[i], NULL, &rect);
        i++;
        if(i > 18){
            return;
        }
    }

    return;
}
