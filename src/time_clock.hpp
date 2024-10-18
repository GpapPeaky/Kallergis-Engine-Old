#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

#ifndef TIME_CLOCK
/**
 * @brief Time clock, in order to make a way for updates
 */
#define TIME_CLOCK

typedef size_t timer;

timer global_time_days;

/**
 * @brief Initialises a clock
 */
void init_clock(void);

/**
 * @brief Updates the time
 */
void update_clock(void);

#endif