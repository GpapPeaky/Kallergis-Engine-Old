#include "province.h"
#include "regions.h"
#include "country.h"

typedef struct prov_node{
    prov data;
    prov* next;
}prov_node;

typedef struct reg_node{
    reg data;
    reg* next;
}reg_node;

/* Countries Hash Might Be Reduntant */

typedef struct cou_node{
    cou data;
    cou* next;
}cou_node;

#ifndef HASHTABLE
#define HASHTABLE

extern prov_node** provinces_h;
extern reg_node** regions_h;

/* Hash Function Constants */

extern int a_constant; /* For the generation of a random hash function (1 ... p - 1) */ 
extern int b_constant; /* For the generation of a random hash function (0 ... p - 1) */ 
extern int p_constant; /* For the generation of a random hash function */

/**
 * @brief Initialises the hash table
 */
void init_hash(void);

/**
 * @brief Hash Function for provinces
 * 
 * @param idx Index to hash
 * @param mode For what to hash ( prov / reg )
 * 
 * @returns The cell where the data is saved
 */
ulint h(int idx, HASH_MODE mode);

/**
 * @brief Selects a prime
 * 
 * @param cap the right biggest smaller prime of the number
 * @param mode For what to hash ( prov / reg )
 * 
 * @returns The selected prime
 */
int prime_selection(int cap, HASH_MODE mode);

#endif
