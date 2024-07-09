#include "../auxf/definitions.aux"
#include "../auxf/modules.aux"
#include <stdio.h>
#include <stdlib.h>

extern int* primes;
extern int found_primes;

#ifndef PRIME_SELECT
/**
 * @brief Prime selection module for the hashtable
 */
#define PRIME_SELECT

/**
 * @brief Checks if a number is prime
 * 
 * @param num Number to check
 * 
 * @returns 0 if it is, 1 if it isn't
 */
uint is_prime(int num);

/**
 * @brief Generates an array of primes, for the hashtable to use
 * 
 * @param max_prime Maximum number of a prime to generate
 */
void prime_array_generation(int max_prime);

/**
 * @brief Prints all generated primes
 */
void print_primes(void);

#endif
