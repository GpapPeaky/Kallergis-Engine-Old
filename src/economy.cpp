#include "economy.hpp"

float I(eco local_economy){
    /* If there is Gold, simply add  0.5 to the province income */
    if(local_economy.local_goods.good == GOLD){
        return static_cast<float>((((local_economy.development.admin * 0.02) * (local_economy.infrastructure * 0.01)) + (local_economy.development.prod * 0.01)) * 15) + 0.5;
    }
    /*                           TAX                                                                                | PRODUCTION                                                                            */
    return static_cast<float>((((local_economy.development.admin * 0.02) * (local_economy.infrastructure * 0.01)) + (GP(local_economy.local_goods) * 0.01)  + (local_economy.development.prod * 0.01)) * 15);
}
