#include "hashtable.hpp"

int prov_hash_s;
int reg_hash_s;

int p_constant_p;
int p_constant_r;

int a_constant_p;
int b_constant_p;
int a_constant_r;
int b_constant_r;

prov** provinces_h;
reg** regions_h;

int prime_selection(int cap, HASH_MODE mode){
    printf("Searching For A Prime\n");
    if(mode == PROV_M){
        for(int i = 0 ; i < PROV_H_CAP ; i++){
            if(primes[i] > cap){
                std::printf("Prime Found\n");
                return primes[i];
            }
        }
    }else if(mode == REG_M){
        for(int i = 0 ; i < PROV_H_CAP ; i++){
            if(primes[i] > cap){
                std::printf("Prime Found\n");
                return primes[i];
            }
        }
    }else{
        std::printf("Prime For Hash Couldn't Be Found: Wrong Mode\n");
        exit(EXIT_FAILURE);
    }
}

void init_hash(void){
    p_constant_p = PROV_MAX; /* Max id */
    p_constant_r = REG_MAX;
    
    prov_hash_s = (int)sqrt(PROV_H_CAP);
    reg_hash_s = (int)sqrt(REG_H_CAP);

    provinces_h = (prov**) malloc(sizeof(prov*) * prov_hash_s); /* HUH? But these mallocs work? */
    regions_h = (reg**) malloc(sizeof(reg*) * reg_hash_s);


    for(int i = 0 ; i < prov_hash_s ; i++){
        /* NULL-ifying initial values, to initialise memory addresses */
        provinces_h[i] = NULL;
    }

    for(int j = 0 ; j < reg_hash_s ; ++j){
        /* NULL-ifying initial values, to initialise memory addresses */
        regions_h[j] = NULL;
    }

    #ifdef HASH_DBG
        std::printf("size of provinces hash: %d\n", prov_hash_s);
        std::printf("size of regions hash: %d\n", reg_hash_s);
    #endif

    int p_prov = prime_selection(2999, PROV_M);
    int p_reg = prime_selection(299, REG_M);

    #ifdef HASH_DBG
        std::printf("p_prov = %d\n", p_prov);
        std::printf("p_reg = %d\n",p_reg);
    #endif

    a_constant_p = rand() % (p_prov - 1) + 1;
    a_constant_r = rand() % (p_reg - 1) + 1;
    
    b_constant_p = rand() % (p_prov - 1);
    b_constant_r = rand() % (p_reg - 1);

    #ifdef HASH_DBG
        std::printf("Selected prov_a: %d\n", a_constant_p);
        std::printf("Selected prov_b: %d\n", b_constant_p);
        std::printf("Selected reg_a: %d\n", a_constant_r);
        std::printf("Selected reg_b: %d\n", b_constant_r);
    #endif

    return;
}

ulint H(int idx, HASH_MODE mode){
    if(mode == PROV_M){
        return (((a_constant_p * idx) + b_constant_p) % p_constant_p) % prov_hash_s;
    }else if(mode == REG_M){
        return (((a_constant_r * idx) + b_constant_r) % p_constant_r) % reg_hash_s;
    }else{
        std::printf("Couldn't Hash Correctly: Wrong Mode\n");
        exit(EXIT_FAILURE);
    }
}

ulint h(int idx, HASH_MODE mode){
    if(mode == PROV_M){
        return idx % prov_hash_s;
    }else if(mode == REG_M){
        return idx % reg_hash_s;
    }else{
        std::printf("Couldn't Hash Correctly: Wrong Mode\n");
        exit(EXIT_FAILURE);
    }
}
