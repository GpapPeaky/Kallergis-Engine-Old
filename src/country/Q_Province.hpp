#pragma once

#include "../../ThirdParty/SDL2/include/SDL2/SDL.h"
#include "../../ThirdParty/SDL2/include/SDL2/SDL_image.h"

/* Quad-base province object */
typedef struct Q_Province {
    SDL_Color rgb;          /* This can work as identification */
    unsigned int pop;       /* Population */
}Q_Province;

/**
 * @brief Parse the province file
**/
void Q_CreateProvinces(void);
