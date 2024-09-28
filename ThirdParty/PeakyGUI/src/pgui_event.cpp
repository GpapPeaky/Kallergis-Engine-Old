#include "pgui_event.hpp"

void PGUI_EventCycle(int x, int y){
    for(auto it = PGUI_GlobalItems.begin() ; it != PGUI_GlobalItems.end() ; ++it){
        PGUI_Item* item = it->second;
        
        for(PGUI_Button* butt : (*item).itemButtons){
            if(PGUI_ButtonPressed(*butt, x, y) == PGUI_True && item->visibility == PGUI_True){
                PGUI_ExecuteButtonAction(*butt);
            }
        }
    }

    return;
}