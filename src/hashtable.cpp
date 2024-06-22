#include "hashtable.h"
#include "primes.h"

int hashtable_s;
int p_constant;
int a_constant;
int b_constant;

prov_node** provinces_h;
reg_node** regions_h;

int prime_selection(int cap){
	for(int i = 0 ; i < 170 ; i++){
		if(primes[i] > cap){
			return primes[i];
		}
	}

    printf("Prime For Hash Couldn't Be Found\n");
}

void init_hash(void){
    provinces_h = (prov_node**) malloc(sizeof(prov_node*) * PROV_H_CAP);
    regions_h = (reg_node**) malloc(sizeof(reg_node*) * REG_H_CAP);
}

ulint h(int idx, HASH_MODE mode){
    
}