#include <iostream>
#include <ctime>
#include <chrono>
#include "KENG_Country.hpp"

#ifndef TIME_CLOCK
/**
 * @brief Time clock, in order to make a way for updates
 */
#define TIME_CLOCK

typedef size_t llUint;

extern llUint KENG_daysPassedGlobal;
extern Uint KENG_gameSpeed;
extern Uint KENG_gamePause;

/**
 * @brief Initialises a clock
 */
void KENG_CreateClock(void);

/**
 * @brief Updates the time
 */
void KENG_UpdateClock(void);

/**
 * @brief Updates the all countries' stats for each clock tick, depending on the speed
 */
void KENG_UpdateCountryStats(void);

/**
 * @brief Updates the population of all provinces of all countries
 */
void KENG_UpdateProvincePopulations(void);

#endif
