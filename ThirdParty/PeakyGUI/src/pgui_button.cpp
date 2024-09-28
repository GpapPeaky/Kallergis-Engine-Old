#include "pgui_button.hpp"

PGUI_Button* PGUI_CreateButton(PGUI_ActionArguments actionArgs, PGUI_component component){
    PGUI_Button* new_button = new PGUI_Button;
    new_button->actionArgs = actionArgs;
    new_button->component = component;

    return new_button;
}

PGUI_Button* PGUI_CreateButtonComplete(PGUI_ActionArguments actionArgs, int x, int y, SDL_Surface* buttonImage, SDL_Renderer* rnd){
    PGUI_Component cmp = PGUI_CreateComponent(x, y, PGUI_UNDECIDED_VALUE, PGUI_UNDECIDED_VALUE, buttonImage, rnd);

    return PGUI_CreateButton(actionArgs, cmp);
}

void* PGUI_CreateButtonWrapper(PGUI_ArgumentVector args){
    int x = reinterpret_cast<int>(args[1]); 
    int y = reinterpret_cast<int>(args[2]);
    SDL_Surface* buttonImage = static_cast<SDL_Surface*>(args[3]);
    SDL_Renderer* rnd = static_cast<SDL_Renderer*>(args[4]);

    // Create PGUI_Button using the complete function
    PGUI_Button* button = PGUI_CreateButtonComplete(
        { nullptr, args, 0 }, x, y, buttonImage, rnd
    );

    return static_cast<void*>(button);
}

PGUI_Bool PGUI_ButtonPressed(PGUI_Button button, int x, int y){
    if((x > button.component.rect.x &&
    y > button.component.rect.y &&
    x < button.component.rect.x + button.component.rect.w &&
    y < button.component.rect.y + button.component.rect.h)){
        return PGUI_True;
    }

    return PGUI_False;
}

void PGUI_ExecuteButtonAction(PGUI_button button){
    if(button.actionArgs.action != NULL){
        void* result = button.actionArgs.action(button.actionArgs.arguments);
    }else{
        printf("Execute Call\n");
    }
}

void PGUI_DeleteButton(PGUI_Button* button){
    if(button->component.background.surface != NULL){
        SDL_FreeSurface(button->component.background.surface);
    }
    if(button->component.background.texture != NULL){
        SDL_DestroyTexture(button->component.background.texture);
    }

    delete button;

    return;
}
