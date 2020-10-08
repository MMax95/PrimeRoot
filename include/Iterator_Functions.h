//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_ITERATOR_FUNCTIONS_H
#define PRIMEROOT_ITERATOR_FUNCTIONS_H

#endif //PRIMEROOT_ITERATOR_FUNCTIONS_H

#include "Step_Functions.h"

void   widthIterateLL          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   widthIterateLR          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   widthIterateRL          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   widthIterateRR          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);

void   depthIterateLL          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   depthIterateLR          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   depthIterateRL          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   depthIterateRR          (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);

void   checkResult             (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                                const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
//void   OFI                     (mpz_t& bigger, mpz_t& smaller, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],unsigned int &xy_size,
//                                unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner);

///Memory Functions///

void    generateTree            (mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y,
                                 mpz_t& diff, unsigned int xy_size, unsigned int number_size);
void    resetTree               (mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y,
                                 mpz_t& diff, unsigned int xy_size);
void    widthIterateAllocator   (unsigned int strategy, Runner *threads, unsigned int thread_ID,
                                 unsigned int runnerNumber, unsigned int position, Result &newNumber);
void    findWork                (Runner *runners, unsigned int runnerNumber, unsigned int runnerID);
bool    cloneThread             (Runner sourceThread, Runner destinationThread, int position);
void    addResult               (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, unsigned int &xy_size,
                                 unsigned int &number_size, Runner &currentRunner);
