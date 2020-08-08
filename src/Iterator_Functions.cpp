//
// Created by blackberry on 27.07.2020.
//
#define MAX_N_SIZE 1024
#define MAX_XY_SIZE
#include "../include/Iterator_Functions.h"
void widthSource(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                 unsigned int position, unsigned int branchType, unsigned int branches[]);

void widthIterate_LFI_LFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                  unsigned int position, unsigned int branchType, unsigned int branches[]);
void widthIterate_RFI_LFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                  unsigned int position, unsigned int branchType, unsigned int branches[]);
void widthIterate_LFI_RFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                  unsigned int position, unsigned int branchType, unsigned int branches[]);
void widthIterate_RFI_RFO(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                  unsigned int position, unsigned int branchType, unsigned int branches[]);

void widthOFI(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
              unsigned int position, unsigned int branchType, unsigned int branches[]);

void depthSource(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                 unsigned int position, unsigned int branchType, unsigned int branches[]);

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

void reallocateThread(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[],
                      unsigned int position, unsigned int branchType);