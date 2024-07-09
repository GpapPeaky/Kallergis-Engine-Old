#include "province.h"
#include "regions.h"
#include "country.h"
#include "math.h" /* Requires the -lm flag */
#include "primes.h"
#include "../auxf/modules.aux"

#ifndef HASHTABLE
/**
 * @brief Implementing an O(1) data structure, to write-read the provinces from... The implementetion is the same (or most likely worse) as with the C++ hashmap library
 */
#define HASHTABLE

extern prov** provinces_h;
extern reg** regions_h;

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

/* All insertions will be done inside the map functions */

#endif
