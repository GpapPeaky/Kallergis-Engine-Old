#include "province.h"
#include <vector>

#ifndef REG
#define REG

typedef struct region{
    std::vector<prov> reg_provs;
    uint reg_id;
}reg;

#endif