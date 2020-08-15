//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_MEMORY_FUNCTIONS_H
#define PRIMEROOT_MEMORY_FUNCTIONS_H

#endif //PRIMEROOT_MEMORY_FUNCTIONS_H

#include "Iterator_Functions.h"
#include <omp.h>
#include <pthread.h>

struct Runner{
    mpz_t number;
    mpz_t x;
    mpz_t y;
    mpz_t diff;
    mpz_t results[MAX_XY_SIZE + 1];

    unsigned int branches[MAX_N_SIZE];

    unsigned int number_size;
    unsigned int xy_size;
};

void allocateThreads(unsigned int thread_number);
void generateNode(mpz_t &result, unsigned int position);
void generateTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE],
                  mpz_t& x, mpz_t& y, mpz_t& diff,
                  unsigned int xy_size, unsigned int number_size);
void cloneThread(int thread_id);

/// void callGPU(); - to be implemented as a check

