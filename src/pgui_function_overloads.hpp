#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "province.hpp" /* For the prov struct */

#ifndef PGUIOVERLOAD
/**
 * @brief Create specific functions for out buttons
 */
#define PGUIOVERLOAD

/**
 * @brief 
 * 
 * @param args arguments
 * @note province province to increment the development of
 * 
 * @returns pointer to the province or NULL if not found
 */
PGUI_Wrap pguiwIncrementDevelopment(PGUI_ArgumentVector args);

#endif
