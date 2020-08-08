//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_ITERATOR_FUNCTIONS_H
#define PRIMEROOT_ITERATOR_FUNCTIONS_H

#endif //PRIMEROOT_ITERATOR_FUNCTIONS_H

#include "Step_Functions.h"

void widthSource(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[],
              unsigned int position, unsigned int branchType);

void widthIterate_LFI_LFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);
void widthIterate_RFI_LFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);
void widthIterate_LFI_RFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);
void widthIterate_RFI_RFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);

void widthOFI(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[],
              unsigned int position, unsigned int branchType);

void depthSource(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[],
              unsigned int position, unsigned int branchType);

void depthIterate_LFI_LFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);
void depthIterate_RFI_LFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);
void depthIterate_LFI_RFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);
void depthIterate_RFI_RFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                          unsigned int position, unsigned int branchType, unsigned int branches[]);

void depthOFI(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[],
              unsigned int position, unsigned int branchType);