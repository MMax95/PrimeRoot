//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_ITERATOR_FUNCTIONS_H
#define PRIMEROOT_ITERATOR_FUNCTIONS_H

#endif //PRIMEROOT_ITERATOR_FUNCTIONS_H

#include "Step_Functions.h"

void   widthIterate(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                    unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE]);

void   depthIterate(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                    unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE]);

void            OFI(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                    unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE]);

void    checkResult(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                    unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE]);