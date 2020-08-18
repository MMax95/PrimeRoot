//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_STEP_FUNCTIONS_H
#define PRIMEROOT_STEP_FUNCTIONS_H

#endif //PRIMEROOT_STEP_FUNCTIONS_H

#include <boost/multiprecision/gmp.hpp>

#define MAX_N_SIZE 1024
#define MAX_XY_SIZE MAX_N_SIZE / 2 + 1

using namespace boost::multiprecision;

enum BranchType{
    equalLeft       = 0b11100, ///flipped: 0b00011, offloaded: 0b01100
    equalRight      = 0b10011, ///flipped: 0b01100, offloaded: 0b00011
    oppositeLeft    = 0b11001, ///flipped: 0b00110, offloaded: 0b01001
    oppositeRight   = 0b10110  ///flipped: 0b01001, offloaded: 0b00110
};


void         getNodeType    (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeLL  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeLR  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeRL  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeRR  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);

void         makeResult     (mpz_t& result, const mpz_t& previousResult, unsigned int position, unsigned int branchType, mpz_t& x, mpz_t& y, mpz_t& diff);
void         setXY          (mpz_t& x, mpz_t& y, unsigned int position, unsigned int branchType);
void         resetXY        (mpz_t& x, mpz_t& y, unsigned int position);