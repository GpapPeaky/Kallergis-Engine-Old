#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "province.hpp" /* For the prov struct */
#include "hashtable.hpp" /* For the province hashtable */

#ifndef PGUIOVERLOAD
/**
 * @brief Create specific functions for out buttons
 */
#define PGUIOVERLOAD

/**
 * @brief 
 * 
 * @param args arguments
 * @note provId province id
 * 
 * @returns pointer to the province
 */
PGUI_Wrap pguiwIncrementDevelopment(PGUI_ArgumentVector args);

#endif
