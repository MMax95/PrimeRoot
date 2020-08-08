//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_STEP_FUNCTIONS_H
#define PRIMEROOT_STEP_FUNCTIONS_H

#endif //PRIMEROOT_STEP_FUNCTIONS_H

#include <boost/multiprecision/gmp.hpp>

using namespace boost::multiprecision;

///Constant variables
enum BranchType{
    equalLeft       = 0b11100, ///flipped: 0b00011, offloaded: 0b01100
    equalRight      = 0b10011, ///flipped: 0b01100, offloaded: 0b00011
    oppositeLeft    = 0b11001, ///flipped: 0b00110, offloaded: 0b01001
    oppositeRight   = 0b10110  ///flipped: 0b01001, offloaded: 0b00110

//    equalLeft       = 0b100, ///flipped: 0b011, offloaded: 0b000
//    equalRight      = 0b111, ///flipped: 0b000, offloaded: 0b011
//    oppositeLeft    = 0b101, ///flipped: 0b010, offloaded: 0b001
//    oppositeRight   = 0b110  ///flipped: 0b001, offloaded: 0b010
};

enum StrategyType{
    equalLeft_oppositeLeft      = 0b1110011001,
    equalRight_oppositeLeft     = 0b1001111001,
    equalLeft_oppositeRight     = 0b1110010110,
    equalRight_oppositeRight    = 0b1001110110
};

///Single functions
unsigned int getNodeType(const mpz_int& number, const mpz_int& result, unsigned int position, BranchType equalBranch, BranchType oppositeBranch);
void         makeResult(mpz_int& result, const mpz_int& previousResult, unsigned int position, unsigned int branchType, const mpz_int& x, const mpz_int& y);

///Composite functions
void         setXY(mpz_int& x, mpz_int& y, unsigned int position, unsigned int branchType);
void         resetXY(mpz_int& x, mpz_int& y, unsigned int position);

///Test functions
unsigned int test_getNodeType(mpz_int number, mpz_int result, bool verbose);
unsigned int test_setXY(mpz_int x, mpz_int y, bool verbose);
unsigned int test_resetXY(mpz_int x,mpz_int y, bool verbose);
unsigned int test_makeResult(mpz_int result, mpz_int previousResult, mpz_int x, mpz_int y, bool verbose);
