#include <iostream>
#include <ctime>
#include <chrono>

#ifndef TIME_CLOCK
/**
 * @brief Time clock, in order to make a way for updates
 */
#define TIME_CLOCK

typedef size_t lluint;

extern lluint KENG_daysPassedGlobal;

/**
 * @brief Initialises a clock
 */
void KENG_CreateClock(void);

/**
 * @brief Updates the time
 */
void KENG_UpdateClock(void);

#endif
