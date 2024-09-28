#include "../ThirdParty/PeakyGUI/src/PGUI.hpp"
#include "auxf/definitions.aux"

#ifndef GUI
/**
 * @brief implementation of PeakyGUI in the project
 */
#define GUI

/**
 * @brief Initialises PeakyGUI, buttons, items and assets
 * 
 * @param rnd renderer
 * 
 * @returns 0 on success, 1 on failure
 */
err_capable init_pgui(SDL_Renderer* rnd);

#endif
