#pragma once

#include "../ThirdParty/SDL2/include/SDL2/SDL.h"

#include "SDL2_Quad.hpp"

/**
 * @brief Handles main loop events
 * 
 * @param quit Checks if we have quit the main loop
 */
void SDL2_HandleEvents(bool& quit);
