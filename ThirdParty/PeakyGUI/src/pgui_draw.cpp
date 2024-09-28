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

void PGUI_DrawItems(SDL_Renderer* rnd){
    for(auto it = PGUI_GlobalItems.begin() ; it != PGUI_GlobalItems.end() ; ++it){
        PGUI_Item* item = it->second;
        
        if(item->visibility == PGUI_True){
                PGUI_DrawItem(*item, rnd); /* If visible show it */
        }
    }

    return;
}

