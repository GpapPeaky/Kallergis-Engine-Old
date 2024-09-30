#include "economy.hpp"

float I(eco local_economy){
    /* If there is Gold, simply add  0.5 to the province income */
    if(local_economy.local_goods.good == GOLD){
        return static_cast<float>((((local_economy.development.admin * 0.02) * (local_economy.infrastructure * 0.01)) + (local_economy.development.prod * 0.01)) * 15) + 0.5;
    }
    /*                           TAX                                                                                | PRODUCTION                                                                            */
    return static_cast<float>((((local_economy.development.admin * 0.02) * (local_economy.infrastructure * 0.01)) + (GP(local_economy) / 5300)  + (local_economy.development.prod * 0.001)) * 15);
}

float GP(eco local_eco){

    local_prd local_production = local_eco.local_goods;

    switch(local_production.good){
        case COAL:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 1000;
            break;
        case IRON:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 1500;
            break;
        case STEEL:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 2500;
            break;
        case FABRIC:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 700;
            break;
        case WOOD:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 450;
            break;
        case ARMS:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 1700;
            break;
        case OIL:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 2750;
            break;
        case RUBBER:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 3000;
            break;
        case GUNPOWDER:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 1600;
            break;
        case GOLD:
            return 0.0f; /* There will be added +0.5 to the income no matter what */
            break;
        case COPPER:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 1150;
            break;
        case LEATHER:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 350;
            break;
        case FISH:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 150;
            break;
        case GLASS:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 2200;
            break;
        case GEMS:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 4500;
            break;
        case STONE:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 200;
            break;
        case PAPER:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 550;
            break;
        case FOOD:
            return static_cast<float>(local_production.population + (GOOD_STABILITY_CONSTANT * local_eco.development.prod)) / 222;
            break;
    default:
        break;
    }

    std::printf("Good Requested Not Found\n");
    return 0;
}
