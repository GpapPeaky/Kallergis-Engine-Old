#include "pgui_call.hpp"

void PGUI_DebugPrint(void){
    std::printf("PGUI function called\n");
    return;
}

void PGUI_Increment(void){
    static int c = 0;
    std::printf("count: %d\n", c++);
}

void PGUI_Exit(void){
    exit(EXIT_SUCCESS);
}
