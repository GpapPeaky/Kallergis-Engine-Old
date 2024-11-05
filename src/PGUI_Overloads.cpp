#include "PGUI_Overloads.hpp"

PGUI_Wrap pguiwIncrementDevelopment(PGUI_ArgumentVector args){
    prov* province = static_cast<prov*>(args[0]);
    if(province == NULL && args[0] == NULL){
        std::printf("Error: province is NULL\n");
        return NULL;
    }
    int provID = province->prov_id;

    for(auto& prov : provinces){
        if(provID == prov->prov_id){
            prov->province_economy.development.admin++;
            prov->province_economy.development.mil++;
            prov->province_economy.development.prod++;
        }
    }

    return static_cast<void*>(province);   
}

PGUI_Wrap pguiwIncrementProdDev(PGUI_ArgumentVector args){
    prov* province = static_cast<prov*>(args[0]);
    if(province == NULL && args[0] == NULL){
        std::printf("Error: province is NULL\n");
        return NULL;
    }
    int provID = province->prov_id;

    for(auto& prov : provinces){
        if(provID == prov->prov_id){
            prov->province_economy.development.prod++;
        }
    }

    return static_cast<void*>(province);   
}

PGUI_Wrap pguiwIncrementAdminDev(PGUI_ArgumentVector args){
    prov* province = static_cast<prov*>(args[0]);
    if(province == NULL && args[0] == NULL){
        std::printf("Error: province is NULL\n");
        return NULL;
    }
    int provID = province->prov_id;

    for(auto& prov : provinces){
        if(provID == prov->prov_id){
            prov->province_economy.development.admin++;
        }
    }

    return static_cast<void*>(province);   
}

PGUI_Wrap pguiwIncrementMilDev(PGUI_ArgumentVector args){
    prov* province = static_cast<prov*>(args[0]);
    if(province == NULL && args[0] == NULL){
        std::printf("Error: province is NULL\n");
        return NULL;
    }
    int provID = province->prov_id;

    for(auto& prov : provinces){
        if(provID == prov->prov_id){
            prov->province_economy.development.mil++;
        }
    }

    return static_cast<void*>(province);   
}
