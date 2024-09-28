#include "pgui_component.hpp"
#include "pgui_button.hpp"
#include "pgui_load.hpp"
#include <unordered_map>
#include <vector>

#ifndef __PGUI_ITEM_H__ 
/**
 * @note Items are dynamically allocated ,instead of the buttons which are simply
 *      saved inside a vector field. (Alloc via 'new', dealloc via 'delete')
 */
#define __PGUI_ITEM_H__

typedef struct PGUI_item{
    PGUI_Component itemComponent; /* Adds the background */
    std::vector<PGUI_Button*> itemButtons; /* Can be empty if the item has no buttons */
    PGUI_Bool visibility;
    Uint ID;
}PGUI_Item;

extern int PGUI_ItemCount;
extern std::unordered_map<int, PGUI_Item*> PGUI_GlobalItems;

/**
 * @brief Creates a new item
 * 
 * @param itemComponent component for background
 * @param buttons item's buttons
 * 
 * @returns a pointer to the created item
 */
PGUI_Item* PGUI_CreateItem(PGUI_Component itemComponent, std::vector<PGUI_Button*> buttons);

/**
 * @brief Creates a new item, better writing
 * 
 * @param x x axis
 * @param y y axis
 * @param itemBackground background surface
 * @param rnd renderer
 * @param buttons item's buttons
 * @param visibility visibility
 * 
 * @returns a pointer to the created item
 */
PGUI_Item* PGUI_CreateItemComplete(int x, int y, SDL_Surface* itemBackground, SDL_Renderer* rnd, std::vector<PGUI_Button*> buttons, PGUI_Bool visibility);

/**
 * @brief Creates a new item, better writing
 * 
 * @param args arguments
 * @note x x axis
 * @note y y axis
 * @note itemBackground background surface
 * @note rnd renderer
 * @note buttons item's buttons
 * 
 * @returns pointer to the created item
 */
PGUI_Wrap PGUI_CreateItemWrapper(PGUI_ArgumentVector args);

/**
 * @brief Destroys a specified item
 * 
 * @param item item to destroy
 */
void PGUI_DestroyItem(PGUI_Item item);

/**
 * @brief Destroys a specified item by id
 * 
 * @attention We encourage user to use this function (and it's wrapper) instead of the PGUI_DestroyItem one if you wan't to handle many buttons
 * 
 * @param itemID id of the item we want to destroy
 */
void PGUI_DestroyItemByID(Uint itemID);

/**
 * @brief Destroys a specified item
 * 
 * @param args arguments
 * @note item to destroy
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_DestroyItemWrapper(PGUI_ArgumentVector args);

/**
 * @brief Destroys a specified item by id
 * 
 * @param args arguments
 * @note item to destroy
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_DestroyItemByIDWrapper(PGUI_ArgumentVector args);

/* Instead of allocating a deallocating memory we will simply change it's visibility */

/**
 * @brief Makes the specified item visible
 * 
 * @param item item to make visible
 */
void PGUI_MakeItemVisible(PGUI_Item* item);

/**
 * @brief Makes the specified item visible
 * 
 * @param args arguments
 * @note item to make visible
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_MakeItemVisibleWrapper(PGUI_ArgumentVector args);

/**
 * @brief Makes the specified item invisible
 * 
 * @param item item to make invisible
 */
void PGUI_MakeItemInvisible(PGUI_Item* item);

/**
 * @brief Makes the specified item invisible
 * 
 * @param args arguments
 * @note item to make invisible
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_MakeItemInvisibleWrapper(PGUI_ArgumentVector args);

/**
 * @brief Makes an item visible if invisible and invisible if visible
 * 
 * @param item item to switch visibility of
 */
void PGUI_ItemVisibilitySwitch(PGUI_Item* item);

/**
 * @brief Makes an item visible if invisible and invisible if visible
 * 
 * @param args arguments
 * @note item to switch visibility of
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_ItemVisibilitySwitchWrapper(PGUI_ArgumentVector args);

/**
 * @brief Creates a button as an item (Item with buttons but no item background)
 * 
 * @param action button's action function
 * @param x x axis
 * @param y y axis
 * @param buttonBackground button's background
 * @param rnd renderer
 * @param visibility visibility of item
 * 
 * @returns a pointer to the created item/button
 */
PGUI_Item* PGUI_CreateButtonAsItem(PGUI_ActionArguments action, int x, int y, SDL_Surface* buttonBackground, SDL_Renderer* rnd,  PGUI_Bool visibility);

#endif
