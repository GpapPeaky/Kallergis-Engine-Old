#include "hashtable.h"
#include "primes.h"
/* Here is a main function for hashtable testing */

int main(int argv, char* args[]){

    prime_array_generation(300);

    int p1 = prime_selection(10, PROV_M);
    int p2 = prime_selection(10, REG_M);

    printf("selected primes %d - %d\n", p1, p2);

    printf("terminates correctly");

    return EXIT_SUCCESS;
}
