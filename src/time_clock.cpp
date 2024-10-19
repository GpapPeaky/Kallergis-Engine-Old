#include "time_clock.hpp"

lluint global_time_days;

void init_clock(void){
    global_time_days = 0;
    return;
}

void update_clock(void){
    global_time_days += 1;
    return;
}
