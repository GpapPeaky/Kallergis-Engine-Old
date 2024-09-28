#include "pgui_component.hpp"

void PGUI_GetComponentAttributes(PGUI_Component component, int* x, int* y, int* w, int* h, PGUI_Background* background, PGUI_Bool* status){
    if(x) *x = component.rect.x;
    if(y) *y = component.rect.y;
    if(w) *w = component.rect.w;
    if(h) *h = component.rect.h;
    if(background) *background = component.background;
    
    return;
}

void PGUI_QueryComponent(PGUI_component component, int* x, int* y, int* w, int* h, PGUI_Background* background, PGUI_Bool* status){
    PGUI_GetComponentAttributes(component, x, y, w, h, background, status);

    return;
}

PGUI_Component PGUI_CreateComponent(int x, int y, int w, int h, SDL_Surface* surface, SDL_Renderer* rnd){
    PGUI_Component new_component;
    new_component.background.surface = surface;
    if(!surface){
        std::printf("PGUI ERROR: Surface Wrongly Provided\n");
    }
    new_component.background.texture = SDL_CreateTextureFromSurface(rnd, surface);
    if(!new_component.background.texture){
        std::printf("PGUI ERROR: Texture Wrongly Provided\n");
    }
    new_component.rect.x = x;
    new_component.rect.y = y;
    new_component.rect.w = surface->w;
    new_component.rect.h = surface->h;

    return new_component;
}

void PGUI_PrintComponent(PGUI_Component component){
    std::printf("x: %d, y: %d, w: %d, h: %d\n", component.rect.x, component.rect.y, component.rect.w, component.rect.h);

    return;
}
