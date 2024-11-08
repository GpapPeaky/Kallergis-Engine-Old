#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "auxf/definitions.aux"
#include "PGUI_Overloads.hpp"
#include "SDL2_Font.hpp"

#ifndef GUI
/**
 * @brief implementation of PeakyGUI in the project
 */
#define GUI

/* Prov inspector adn buttons */
extern PGUI_ActionArguments provAdmDevArgs;
extern PGUI_ActionArguments provMilDevArgs;
extern PGUI_ActionArguments provProdDevArgs;
extern PGUI_Button* adminDev;
extern PGUI_Button* milDev;
extern PGUI_Button* prodDev;
extern PGUI_Item* provInspector;

/* Country Bar */
extern PGUI_Item* countryBar;
extern PGUI_Item* countryInsignia;
extern PGUI_Item* countryFlag;

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
 * @brief Initialises PeakyGUI, country bar
 * 
 * @param country country to initialise the bar for
 * @param rnd renderer
 * 
 * @returns 0 on success, 1 on failure
 */
int PGUI_CreateCountryBar(cou* country, SDL_Renderer* rnd);

/**
 * @brief Initialises PeakyGUI, province inspection
 * 
 * @param rnd renderer
 * 
 * @returns 0 on success, 1 on failure
 */
int PGUI_CreateProvinceInspector(SDL_Renderer* rnd);

/**
 * @brief Updates the province that the gui is currently looking at
 * 
 * @param province province to be shown at the province inspector
 * @param rnd renderer to use (we can remove it)
 * 
 * @returns 0 on success, 1 on failure
 */
int PGUI_UpdateProvinceInspector(prov* province, SDL_Renderer* rnd);

#endif
