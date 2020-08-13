//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_MEMORY_FUNCTIONS_H
#define PRIMEROOT_MEMORY_FUNCTIONS_H

#endif //PRIMEROOT_MEMORY_FUNCTIONS_H

#include <pthread.h>


#define MAX_NUMBER_LENGTH 512
#define MAX_TREE_DEPTH 256


unsigned int*   allocateThreads    (unsigned int thread_number);
void            generateNode       (unsigned int position);
void            generateTree       (unsigned int thread_id);
unsigned int    findNewNode        (unsigned int thread_ids[]);
void            cloneThread        (unsigned int source_thread, unsigned int destination_thread,
                                    unsigned int position);

/// void callGPU(); - to be implemented as a check
