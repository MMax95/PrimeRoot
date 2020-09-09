//
// Created by blackberry on 27.07.2020.
//

#ifndef PRIMEROOT_STEP_FUNCTIONS_H
#define PRIMEROOT_STEP_FUNCTIONS_H

#include <boost/multiprecision/gmp.hpp>
#include <boost/container/list.hpp>

#define MAX_N_SIZE 1024
#define MAX_XY_SIZE MAX_N_SIZE / 2 + 1
#define THREAD_NUMER 1

using namespace boost::container;
using namespace boost::multiprecision;

enum threadState{
    unititialized = 0,
    idle          = 1,
    running       = 2,
    loading       = 3
};

enum BranchType{
    equalLeft       = 0b11100, ///flipped: 0b00011, offloaded: 0b01100
    equalRight      = 0b10011, ///flipped: 0b01100, offloaded: 0b00011
    oppositeLeft    = 0b11001, ///flipped: 0b00110, offloaded: 0b01001
    oppositeRight   = 0b10110  ///flipped: 0b01001, offloaded: 0b00110
};

enum StrategyType{
    LL   = 0b11001001, ///flipped: 0b00011, offloaded: 0b01100
    LR   = 0b11000110, ///flipped: 0b01100, offloaded: 0b00011
    RL   = 0b00111001, ///flipped: 0b00110, offloaded: 0b01001
    RR   = 0b00110110  ///flipped: 0b01001, offloaded: 0b00110
};

struct Result{
    mpz_t number;
    Result *left;
    Result *right;
//    Result *self;
    Result()
    {
        mpz_int(this->number);
        this->left = nullptr;
        this->right = nullptr;
//        this->self = this;
    }
    Result(mpz_t number)
    {
        mpz_init_set(this->number, number);
        this->left = nullptr;
        this->right = nullptr;
//        this->self = this;
    }

};

extern list<Result> unique_factors;
extern list<Result>::iterator it;

struct Runner{
    mpz_t number;
    mpz_t x;
    mpz_t y;
    mpz_t diff;
    mpz_t results[MAX_XY_SIZE];
    unsigned int runner_index;
    unsigned int strategy;

    unsigned int branches[MAX_N_SIZE];
    unsigned int number_size;
    unsigned int xy_size;
    threadState state;
    bool identical = false;

    unsigned int uniqueXY = 0b11; /// X = 0b10, Y = 0b01

    Result *targetNumber;
    Result *tempX;
    Result *tempY;
};

void         getNodeType    (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeLL  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeLR  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeRL  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);
void         getNodeTypeRR  (const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_N_SIZE]);

void         makeResult     (mpz_t& result, const mpz_t& previousResult, unsigned int position, unsigned int branchType, mpz_t& x, mpz_t& y, mpz_t& diff);
void         setXY          (mpz_t& x, mpz_t& y, unsigned int position, unsigned int branchType);
void         resetXY        (mpz_t& x, mpz_t& y, unsigned int position);
char*        readResults    (Result *root, char charBuffer[1024]);

#endif //PRIMEROOT_STEP_FUNCTIONS_H