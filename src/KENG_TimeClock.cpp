#include "KENG_TimeClock.hpp"

llUint KENG_daysPassedGlobal;
Uint KENG_gameSpeed;
Uint KENG_gamePause;

void KENG_CreateClock(void){
    KENG_daysPassedGlobal = 0;
    KENG_gameSpeed = SPEED3_CYCLES_PER_UPDATE;
    KENG_gamePause = NOT_PAUSED;
    return;
}

void KENG_UpdateClock(void){
    KENG_daysPassedGlobal += 1;
    return;
}

void KENG_UpdateCountryStats(void){
    for(auto& country : KENG_globalCountries){
        for(auto& reg : country.country_regs){
            for(auto& prov : reg.reg_provs){
                #ifdef UPDATE_PRINTS
                    printf("Money added: %.2f from %s\n", I(prov.province_economy), prov.prov_name.c_str());
                #endif
                country.balance += I(prov.province_economy);
                country.manpower += prov.province_economy.local_goods.population / 1000;

                /* Add a manpower cap */
            }
        }
    }

    return;
}

void KENG_UpdateProvincePopulations(void){
    /* This will update in all countries */
    for(auto& country : KENG_globalCountries){
        for(auto& reg : country.country_regs){
            for(auto& prov : reg.reg_provs){
                double growthRate = (prov.province_economy.development.admin +
                        prov.province_economy.development.mil +
                        prov.province_economy.development.prod) * 0.000001f;

                int growthAmount = static_cast<int>(prov.province_economy.local_goods.population * growthRate) / 10;

                if(growthAmount == 0){
                    prov.province_economy.local_goods.population += 1; /* just add +1 */
                    #ifdef UPDATE_PRINTS
                        printf("local: Population added: %d to %s %d\n", 1, prov.prov_name.c_str(), prov.province_economy.local_goods.population);
                    #endif
                }else{
                    prov.province_economy.local_goods.population += growthAmount;
                    #ifdef UPDATE_PRINTS
                        printf("local:  Population added: %d to %s %d\n", growthAmount, prov.prov_name.c_str(), prov.province_economy.local_goods.population);
                    #endif
                }
            }
        }
    }

    /* FOR PGUI, PGUI checks the global provinces vector */
    for(auto& prov : provinces){
        double growthRate = (prov->province_economy.development.admin +
        prov->province_economy.development.mil +
        prov->province_economy.development.prod) * 0.000001f;
        int growthAmount = static_cast<int>(prov->province_economy.local_goods.population * growthRate) / 10;

        if(growthAmount == 0){
            prov->province_economy.local_goods.population += 1; /* just add +1 */
            #ifdef UPDATE_PRINTS
                printf("pgui: Population added: %d to %s %d\n", 1, prov->prov_name.c_str(), prov->province_economy.local_goods.population);
            #endif
        }else{
            prov->province_economy.local_goods.population += growthAmount;
            #ifdef UPDATE_PRINTS
                printf("pgui: Population added: %d to %s %d\n", growthAmount, prov->prov_name.c_str(), prov->province_economy.local_goods.population);
            #endif
        }
    }

    return;
}
