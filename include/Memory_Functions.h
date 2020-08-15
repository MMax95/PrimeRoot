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
void generateNode(mpz_int &result, unsigned int position);
void generateTree(mpz_int results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE],
                  mpz_int& x, mpz_int& y,
                  unsigned int xy_size, unsigned int number_size);
void cloneThread(int thread_id);

/// void callGPU(); - to be implemented as a check

