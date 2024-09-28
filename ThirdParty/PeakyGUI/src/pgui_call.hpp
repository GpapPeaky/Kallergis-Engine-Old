#include <iostream>
#include <vector> 
#include "pgui_action.hpp"

#ifndef __PGUI_CALL_H__
/**
 * @attention We need to create wrapper functions in order to call them from a PGUI_button
 *  PGUI_Wrap foo(PGUI_ArgumentVector args); // Explicitly functions like his void* foo(std::vector<void*> agrs);
 */
#define __PGUI_CALL_H__

/**
 * @brief A debug print for button presses
 */
void PGUI_DebugPrint(void);

/**
 * @brief A debug print for button presses
 * 
 * @param args arguments ({ })
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_DebugWrapper(PGUI_ArgumentVector args);

/**
 * @brief increments a static count
 */
void PGUI_Increment(void);

/**
 * @brief increments a static count
 * 
 * @param args arguments ({ })
 * 
 * @returns NULL
 */
PGUI_Wrap PGUI_IncrementWrapper(PGUI_ArgumentVector args);

/**
 * @brief Forces an exit
 */
void PGUI_Exit(void);

/**
 * @brief adds up two numbers
 * 
 * @param args arguments and number of arguments
 * 
 * @returns a pointer to the sum
 */
PGUI_Wrap PGUI_Sum(PGUI_ArgumentVector args);

#endif
