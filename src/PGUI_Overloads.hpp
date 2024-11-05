#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "KENG_Province.hpp" /* For the prov struct */

#ifndef PGUIOVERLOAD
/**
 * @brief Create specific functions for out buttons
 */
#define PGUIOVERLOAD

/**
 * @brief Updates the province to be selected for dev increase, for the one last clicked
 * 
 * @param province province to pass as a new argument
 */
void pguiUpdateDevelopmentTargetArguments(prov* province);

/**
 * @brief 
 * 
 * @param args arguments
 * @note province province to increment the development of
 * 
 * @returns pointer to the province or NULL if not found
 */
PGUI_Wrap pguiwIncrementDevelopment(PGUI_ArgumentVector args);

/**
 * @brief 
 * 
 * @param args arguments
 * @note province province to increment the prod development of
 * 
 * @returns pointer to the province or NULL if not found
 */
PGUI_Wrap pguiwIncrementProdDev(PGUI_ArgumentVector args);

/**
 * @brief 
 * 
 * @param args arguments
 * @note province province to increment the admin development of
 * 
 * @returns pointer to the province or NULL if not found
 */
PGUI_Wrap pguiwIncrementAdminDev(PGUI_ArgumentVector args);

/**
 * @brief 
 * 
 * @param args arguments
 * @note province province to increment the mil development of
 * 
 * @returns pointer to the province or NULL if not found
 */
PGUI_Wrap pguiwIncrementMilDev(PGUI_ArgumentVector args);


#endif
