#include "pgui_component.hpp"
#include "pgui_button.hpp"
#include <unordered_map>
#include <vector>

#ifndef __PGUI_ITEM_H__ 
#define __PGUI_ITEM_H__

typedef struct PGUI_item{
    PGUI_Component itemComponent; /* Adds the background */
    std::vector<PGUI_Button> itemButtons; /* Can be empty if the item has no buttons */
}PGUI_Item;

extern int PGUI_ItemCount;
extern std::unordered_map<int, PGUI_Item> PGUI_GlobalItems;

/**
 * @brief Creates a new item
 * 
 * @param itemComponent component for background
 */
PGUI_Item PGUI_CreateItem(PGUI_Component itemComponent, std::initializer_list<PGUI_Button> buttons);

#endif
