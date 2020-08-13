//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_ITERATOR_FUNCTIONS_H
#define PRIMEROOT_ITERATOR_FUNCTIONS_H

#endif //PRIMEROOT_ITERATOR_FUNCTIONS_H
#include "Memory_Functions.h"
#include "Step_Functions.h"

void checkResult    (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[]);

void widthSource    (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[],
              unsigned int threadID, unsigned int* thread_ids);

void widthIterate   (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[]);

void widthOFI       (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[]);

void depthSource    (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[],
              unsigned int threadID, unsigned int* thread_ids);

void depthIterate   (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[]);

void depthOFI       (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int number_size, unsigned int position, unsigned int branches[]);

void squareHunter();

void brancher();

void singleRunner();