#include <iostream>
#include <ctime>
#include <chrono>
#include "KENG_Country.hpp"

#ifndef TIME_CLOCK
/**
 * @brief Time clock, in order to make a way for updates
 */
#define TIME_CLOCK

typedef size_t lluint;

extern lluint KENG_daysPassedGlobal;
extern uint KENG_gameSpeed;
extern uint KENG_gamePause;

/**
 * @brief Initialises a clock
 */
void KENG_CreateClock(void);

/**
 * @brief Updates the time
 */
void KENG_UpdateClock(void);

/**
 * @brief Updates the country object for each clock tick, depending on the speed
 * 
 * @param country country to update
 */
void KENG_UpdateCountryStats(cou* country);

/**
 * @brief Updates the population of all provinces of a country
 * 
 * @param country country to update
 */
void KENG_UpdateProvincePopulations(cou* country);

#endif
