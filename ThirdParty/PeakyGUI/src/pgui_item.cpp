#include "pgui_item.hpp"

std::unordered_map<int, PGUI_Item> PGUI_GlobalItems;
int PGUI_ItemCount = 0;

PGUI_Item PGUI_CreateItem(PGUI_Component component, std::initializer_list<PGUI_Button> buttons){
    PGUI_Item new_item;
    new_item.itemComponent = component;
    new_item.itemButtons = buttons;
    PGUI_GlobalItems[PGUI_ItemCount++] = new_item; /* Pass the item onto the map */

    return new_item;
}
