#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "auxf/definitions.aux"
#include "pgui_function_overloads.hpp"
#include "font.hpp"

#ifndef GUI
/**
 * @brief implementation of PeakyGUI in the project
 */
#define GUI

extern PGUI_ActionArguments provAdmDevArgs;
extern PGUI_ActionArguments provMilDevArgs;
extern PGUI_ActionArguments provProdDevArgs;
extern PGUI_Button* adminDev;
extern PGUI_Button* milDev;
extern PGUI_Button* prodDev;
extern PGUI_Item* provInspector;

/**
 * @brief Updates the arguments of a specified button
 * 
 * @param button button to update
 * @param newArgs new arguments to pass
 * 
 * @returns a pointer to the updated button
 */
PGUI_Button* PGUI_UpdateButtonArguments(PGUI_Button* button, PGUI_ActionArguments newArgs);

/**
 * @brief Initialises PeakyGUI, buttons, items and assets
 * 
 * @param rnd renderer
 * 
 * @returns 0 on success, 1 on failure
 */
err_capable init_province_inspector(SDL_Renderer* rnd);

/**
 * @brief Updates the province that the gui is currently looking at
 */
err_capable update_province_inspector(prov* province, SDL_Renderer* rnd);

#endif
