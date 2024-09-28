#include "pgui_primitives.hpp"
#include "pgui_item.hpp"

#ifndef __PGUI_CLEANUP_H__
#define __PGUI_CLEANUP_H__

/**
 * @brief Cleans up all allocated items, and buttons
 */
void PGUI_Cleanup(void);

/**
 * @brief Checks if any memory is not deallocated
 * 
 * @returns 1 for succesful deallocation, 0 if bytes still remain
 */
PGUI_Bool PGUI_MemoryCheck(void);

#endif
