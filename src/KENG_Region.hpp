#include <vector>
#include "KENG_Province.hpp"

#ifndef REG
/**
 * @brief Region structs, consist of provinces
 */
#define REG

typedef struct region{
    Uint pops;
    std::string reg_name;
    std::vector<prov> reg_provs;
    Uint reg_id;
}reg;

#endif
