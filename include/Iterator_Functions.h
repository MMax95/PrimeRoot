//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_ITERATOR_FUNCTIONS_H
#define PRIMEROOT_ITERATOR_FUNCTIONS_H

#endif //PRIMEROOT_ITERATOR_FUNCTIONS_H

#include "Step_Functions.h"

void   widthIterateAllocator (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   widthIterate (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   widthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   widthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   widthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   widthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);

void   depthIterate (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   depthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   depthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   depthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);
void   depthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);

void            OFI (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                     unsigned int position, unsigned int branches[MAX_N_SIZE]                          );

void    checkResult (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size);