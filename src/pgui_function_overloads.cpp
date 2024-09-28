#include "pgui_function_overloads.hpp"

PGUI_Wrap pguiwIncrementDevelopment(PGUI_ArgumentVector args){
    int provinceID = *static_cast<int*>(args[0]);

    for(int i = 0 ; i < prov_hash_s ; i++){
        prov* current = provinces_h[h(i, PROV_M)];
        while(current != NULL){
            if(provinceID == current->prov_id){
                current->province_economy.development.admin++;
                current->province_economy.development.mil++;
                current->province_economy.development.prod++;
            }
            current = current->next;
        }
    }

    return NULL;    
}
