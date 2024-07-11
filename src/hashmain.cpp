#include "hashtable.hpp"
#include "primes.hpp"
/* Here is a main function for hashtable testing */

int main(int argv, char* args[]){

    srand(time(NULL));

    prime_array_generation(300);
    init_hash();

    printf(" -prov\n");

    for(int i = 0 ; i < 25 ; i++){
        printf("idx: %d -> %d\n", i, h(i, PROV_M));
    }

    printf(" -reg\n");

    for(int i = 0 ; i < 25 ; i++){
        printf("idx: %d -> %d\n", i, h(i, REG_M));
    }

    printf("terminates correctly");

    return EXIT_SUCCESS;
}
