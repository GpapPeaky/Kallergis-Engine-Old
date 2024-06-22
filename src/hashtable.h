#include "province.h"
#include "regions.h"
#include "country.h"
#include "math.h" /* Requires the -lm flag */

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

extern int prov_hash_s;
extern int reg_hash_s;

extern int p_constant_p; /* For the generation of a random hash function */
extern int p_constant_r; /* For the generation of a random hash function */

extern int a_constant_p; /* For the generation of a random hash function (1 ... p - 1) */ 
extern int b_constant_p; /* For the generation of a random hash function (0 ... p - 1) */ 
extern int a_constant_r; /* For the generation of a random hash function (1 ... p - 1) */ 
extern int b_constant_r; /* For the generation of a random hash function (0 ... p - 1) */ 

/**
 * @brief Initialises the hash table
 */
void init_hash(void);

/**
 * @brief Hash Function for provinces
 * @warning The true hash function is this devided by 2
 * 
 * @param idx Index to hash
 * @param mode For what to hash ( prov / reg )
 * 
 * @returns The cell where the data is saved
 */
ulint H(int idx, HASH_MODE mode);

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
