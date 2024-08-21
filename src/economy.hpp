#include "../src/auxf/definitions.aux"
#include "goods.hpp"

#ifndef ECONOMY
/**
 * @brief Development for provinces
 */
#define ECONOMY

typedef struct dev{
    uint admin; /* Administrative development */
    uint mil; /* Military development */
    uint prod; /* Production development */
}dev;

typedef struct economy{
    dev development;
    local_prd local_goods;
    uint infrastructure;
}eco;

/**
 * @brief Calculates an income number for a specific economy
 * 
 * @param local_economy Economy to calculate the income of
 * 
 * @returns The income number
 */
float I(eco local_economy);

#endif
