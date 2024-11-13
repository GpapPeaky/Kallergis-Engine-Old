#include <iostream>

#ifndef DBGP
/**
 * @brief debug print macro
 */
#define DBGP

#define KENG_DebugPrint(msg) \
    fprintf(stderr, "%s", msg); \
    fprintf(stderr, " at %s, l: %d: \n", __FILE__, __LINE__);

#endif /* DBGP */
