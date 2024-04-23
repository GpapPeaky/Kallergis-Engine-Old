#include "regions.h"

#ifndef COU
#define COU

typedef struct country{
    std::string country_name;
    std::vector<reg> country_regs;
    SDL_Surface* country_flag;
}cou;

/**
 * @brief Initialises the data for each country
*/
err_capable country_init(void);

#endif
