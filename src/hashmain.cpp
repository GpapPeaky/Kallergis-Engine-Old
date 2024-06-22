#include "hashtable.h"
#include "primes.h"
/* Here is a main function for hashtable testing */

int main(int argv, char* args[]){

    prime_array_generation(300);
    print_primes();

    printf("terminates correctly");

    return EXIT_SUCCESS;
}
