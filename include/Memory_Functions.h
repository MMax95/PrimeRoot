//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_MEMORY_FUNCTIONS_H
#define PRIMEROOT_MEMORY_FUNCTIONS_H

#endif //PRIMEROOT_MEMORY_FUNCTIONS_H

#include "Iterator_Functions.h"
#include <omp.h>
#include <pthread.h>

void allocateThreads(unsigned int thread_number);
void generateNode(int position);
void generateTree(int thread_id);
void cloneThread(int thread_id);

/// void callGPU(); - to be implemented as a check

