#include "pgui_button.hpp"

PGUI_Button PGUI_CreateButton(PGUI_ButtonAction action, PGUI_component component){
    static int buttonID = 0;
    PGUI_Button new_button;
    new_button.action = action;
    new_button.component.rect = component.rect;
    new_button.component.background = component.background;
    new_button.component.status = PGUI_IsButton;

    return new_button;
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
    if(button.action != NULL){ button.action(); }else{ printf("Execute Call\n"); }
    return;
}
