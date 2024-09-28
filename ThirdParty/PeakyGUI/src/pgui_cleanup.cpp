#include "pgui_cleanup.hpp"

void PGUI_Cleanup(void){
    for(auto it = PGUI_GlobalItems.begin() ; it != PGUI_GlobalItems.end() ; ){
        PGUI_Item* item = it->second;

        if(item->itemComponent.background.surface != NULL){
            SDL_FreeSurface(item->itemComponent.background.surface);
            item->itemComponent.background.surface = NULL;
        }
        if(item->itemComponent.background.texture != NULL){
            SDL_DestroyTexture(item->itemComponent.background.texture);
            item->itemComponent.background.texture = NULL;
        }

        /* Dealloc memory for the button graphics */
        for(PGUI_Button*& itemButton : item->itemButtons){ /* HUH? Syntax? */
            PGUI_DeleteButton(itemButton);
            itemButton = NULL;
        }
        // /* Clear the vector */
        item->itemButtons.clear();

        /* Dealloc memory */
        delete item;
        item = NULL;

        it = PGUI_GlobalItems.erase(it);
    }

    return;
}

PGUI_Bool PGUI_MemoryCheck(void){
    for(auto it = PGUI_GlobalItems.begin() ; it != PGUI_GlobalItems.end() ; ){
        PGUI_Item* item = it->second;

        if(item->itemComponent.background.surface == NULL){
            std::printf("\tItem Surface Deallocated\n");
        }else{
            std::printf("\t\tItem Surface Couldn't Be Deleted\n");
        }
        if(item->itemComponent.background.texture == NULL){
            std::printf("\tItem Texture Deallocated\n");
        }else{
            std::printf("\t\tItem Texture Couldn't Be Deleted\n");
        }

        /* Dealloc memory for the button graphics */
        for(PGUI_Button* itemButton : item->itemButtons){
            if(itemButton == NULL){
                std::printf("\t\tButton Deleted\n");
            }else{
                std::printf("\t\t\tButton Couldn't Be Deleted\n");
            }
        }
        /* Clear the vector */
        item->itemButtons.clear();

        /* Dealloc memory */
        if(item == NULL){
            std::printf("Item %d Deleted Successfully\n", item->ID);
        }else{
            std::printf("Item %d Couldn't Be Deleted\n", item->ID);
            return PGUI_False;
        }
    }

    return PGUI_True;
}
