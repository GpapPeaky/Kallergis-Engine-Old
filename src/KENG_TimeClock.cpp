#include "KENG_TimeClock.hpp"

lluint KENG_daysPassedGlobal;

void KENG_CreateClock(void){
    KENG_daysPassedGlobal = 0;
    return;
}

void KENG_UpdateClock(void){
    KENG_daysPassedGlobal += 1;
    return;
}
