#include "primes.hpp"

int* primes;
int found_primes = 0;

uint is_prime(int num){
    if(num <= 1) return 0;
    if(num <= 3) return 1;

    if(num % 2 == 0 || num % 3 == 0) return 0;

    int i = 5;
    while(i * i <= num){
        if(num % i == 0 || num % (i + 2) == 0) return 0;
        i += 6;
    }

    return 1;
}

void prime_array_generation(int max_prime){
    int num = 2;
    while(found_primes < 3000 && num < max_prime){
        if(is_prime(num)){
            #ifdef HASH_DBG
                printf("%d\n", num);
            #endif
            found_primes++;
        }
        num++;
    }
    #ifdef HASH_DBG
        printf("Primes %d\n", found_primes);
    #endif

    primes = (int*)malloc(sizeof(int) * found_primes); /* Allocate memory */
    
    found_primes = 0;
    num = 2;
    /* Pass the items here */
    while(found_primes < 3000 && num < max_prime){
        if(is_prime(num)){
            primes[found_primes] = num;
            found_primes++;
        }
        num++;
    }

    return;
}

void print_primes(void){
    for(int i = 0 ; i < found_primes ; i++){
        printf("p = %d\n", primes[i]);
    }

    return;
}
