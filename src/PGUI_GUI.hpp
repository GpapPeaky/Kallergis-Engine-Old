#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "auxf/definitions.aux"
#include "KENG_Country.hpp"
#include "PGUI_Overloads.hpp"

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

/* Leader Overview */
extern PGUI_Item* leaderOverviewBackground;

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
int PGUI_CreateCountryBar(KENG_country* country, SDL_Renderer* rnd);

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

/**
 * @brief Initialises PeakyGUI, calendar and game speed manipulator
 * 
 * @param rnd renderer
 * 
 * @returns 0 on success, 1 on failure
 */
int PGUI_CreateCalendar(SDL_Renderer* rnd);

/**
 * @brief Initialise PeakyGUI, country leader overview
 * 
 * @param rnd renderer
 * 
 * @returns 0 on success, 1 on failure
 */
int PGUI_CreateCountryLeaderOverview(SDL_Renderer* rnd);

#endif
