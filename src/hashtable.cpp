#include "hashtable.h"
#include "primes.h"

int prov_hash_s;
int reg_hash_s;

int p_constant_p;
int p_constant_r;

int a_constant_p;
int b_constant_p;
int a_constant_r;
int b_constant_r;

prov_node** provinces_h;
reg_node** regions_h;

int prime_selection(int cap, HASH_MODE mode){
    if(mode == PROV_M){
        for(int i = 0 ; i < PROV_H_CAP ; i++){
            if(primes[i] > cap){
                return primes[i];
            }
        }
    }else if(mode == REG_M){
        for(int i = 0 ; i < PROV_H_CAP ; i++){
            if(primes[i] > cap){
                return primes[i];
            }
        }
    }else{
        printf("Prime For Hash Couldn't Be Found: Wrong Mode\n");
        exit(EXIT_FAILURE);
    }
}

void init_hash(void){
    p_constant_p = PROV_MAX; /* Max id */
    p_constant_r = REG_MAX;
    
    provinces_h = (prov_node**) malloc(sizeof(prov_node*) * (int)sqrt(PROV_H_CAP));
    regions_h = (reg_node**) malloc(sizeof(reg_node*) * (int)sqrt(REG_H_CAP));

    prov_hash_s = (int)sqrt(PROV_H_CAP);
    reg_hash_s = (int)sqrt(REG_H_CAP);

    printf("size of provinces hash: %d\n", prov_hash_s);
    printf("size of regions hash: %d\n", reg_hash_s);

    int p_prov = prime_selection(2999, PROV_M);
    printf("p_prov = %d\n", p_prov);
    int p_reg = prime_selection(299, REG_M);
    printf("p_reg = %d\n",p_reg);

    a_constant_p = rand() % (p_prov - 1) + 1;
    a_constant_r = rand() % (p_reg - 1) + 1;
    
    b_constant_p = rand() % (p_prov - 1);
    b_constant_r = rand() % (p_reg - 1);

    printf("Selected prov_a: %d\n", a_constant_p);
    printf("Selected prov_b: %d\n", b_constant_p);
    printf("Selected reg_a: %d\n", a_constant_r);
    printf("Selected reg_b: %d\n", b_constant_r);

    return;
}

ulint H(int idx, HASH_MODE mode){
    if(mode == PROV_M){
        return ((((a_constant_p * idx) + b_constant_p) % p_constant_p) % (prov_hash_s + 11));
    }else if(mode == REG_M){
        return ((((a_constant_r * idx) + b_constant_r) % p_constant_r) % (reg_hash_s + 6));
    }else{
        printf("Couldn't Hash Correctly: Wrong Mode\n");
        exit(EXIT_FAILURE);
    }
}

ulint h(int idx, HASH_MODE mode){
    return H(idx, mode) / 2;
}