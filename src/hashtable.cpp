#include "hashtable.h"
#include "primes.h"

int hashtable_s;
int p_constant;

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
        printf("Prime For Hash Couldn't Be Found\n");
        exit(EXIT_FAILURE);
    }
}

void init_hash(void){
    provinces_h = (prov_node**) malloc(sizeof(prov_node*) * (int)sqrt(PROV_H_CAP));
    regions_h = (reg_node**) malloc(sizeof(reg_node*) * (int)sqrt(REG_H_CAP));

    int p_prov = prime_selection(PROV_H_CAP, PROV_M);
    int p_reg = prime_selection(REG_H_CAP, REG_M);

    printf("%d %d", p_prov, p_reg);

    a_constant_p = rand() % (p_prov - 1) + 1;
    a_constant_r = rand() % (p_reg - 1) + 1;
    
    b_constant_p = rand() % (p_prov - 1);
    b_constant_r = rand() % (p_reg - 1);
}

ulint h(int idx, HASH_MODE mode){
    
}