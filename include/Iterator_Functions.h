//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_ITERATOR_FUNCTIONS_H
#define PRIMEROOT_ITERATOR_FUNCTIONS_H

#endif //PRIMEROOT_ITERATOR_FUNCTIONS_H

#include "Step_Functions.h"

void   widthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   widthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   widthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   widthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);

void   depthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   depthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   depthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void   depthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);

void            OFI_L (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                     unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner);
void            OFI_R (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner);

void    checkResult (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void    checkResultL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);
void    checkResultR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                     const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner);


///Memory Functions///

//void    generateNode            (mpz_t &result, unsigned int position);
void    generateTree            (mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y,
                                 mpz_t& diff, unsigned int xy_size, unsigned int number_size);
void    resetTree               (mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y,
                                 mpz_t& diff, unsigned int xy_size);
void    widthIterateAllocator   (unsigned int strategy, Runner *threads, unsigned int thread_ID,
                                 unsigned int runnerNumber, unsigned int position, Result &newNumber);

void    depthIterateAllocator   (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
                                 unsigned int &xy_size,const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, unsigned int strategy,
                                 Runner *threads, unsigned int thread_ID, unsigned int runnerNumber, Result newNumber);

bool    cloneThread             (Runner sourceThread, Runner destinationThread, unsigned int position);
bool    findWork                (Runner *runners, unsigned int runnerNumber, unsigned int runnerID);
void    reallocateThread        ();
void    addResult               (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, unsigned int &xy_size,
                                 unsigned int &number_size, Runner &currentRunner);
