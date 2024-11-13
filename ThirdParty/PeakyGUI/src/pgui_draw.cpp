#include "pgui_draw.hpp"

void PGUI_DrawComponent(PGUI_Component comp, SDL_Renderer* rnd){
    SDL_RenderCopy(rnd, comp.background.texture, NULL, &comp.rect);
    return;
}

void PGUI_HighlightButtonOnClick(PGUI_Button button, SDL_Renderer* rnd){
    SDL_SetRenderDrawColor(rnd, 255 ,255, 255, 150);
    SDL_RenderDrawRect(rnd, &button.component.rect);

    return;
}

void PGUI_DrawItem(PGUI_Item item, SDL_Renderer* rnd){
    PGUI_DrawComponent(item.itemComponent, rnd);
    for(auto button : item.itemButtons){
        PGUI_DrawComponent((*button).component, rnd);
    }

    return;
}

void PGUI_DrawItems(SDL_Renderer* rnd) {
    std::vector<std::pair<int, PGUI_Item*>> itemsToRender(PGUI_GlobalItems.begin(), PGUI_GlobalItems.end());

    std::sort(itemsToRender.begin(), itemsToRender.end(), [](const std::pair<int, PGUI_Item*>& a, const std::pair<int, PGUI_Item*>& b){
        return a.first < b.first;
    });

    for(const auto& pair : itemsToRender){
        PGUI_Item* item = pair.second;
        if(item->visibility == PGUI_True){
            PGUI_DrawItem(*item, rnd);
        }
    }

    return;
}
