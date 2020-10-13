//
// Created by blackberry on 27.07.2020.
//

#include "../include/Step_Functions.h"
list<Result> unique_factors;

///Single functions
void        getNodeTypeLL(const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_XY_SIZE])
{
    if(mpz_tstbit(number, position) == mpz_tstbit(result, position))
    {
        branches[position] = 0b11100;
    }else{
        branches[position] = 0b11001;
    }
}

void        getNodeTypeLR(const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_XY_SIZE])
{
    ///equalLeft_oppositeRight
    if(mpz_tstbit(number, position) == mpz_tstbit(result, position))
    {
        branches[position] = 0b11100;
    }else{
        branches[position] = 0b10110;
    }
}

void        getNodeTypeRL(const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_XY_SIZE])
{
    ///equalRight_oppositeLeft
    if(mpz_tstbit(number, position) == mpz_tstbit(result, position))
    {
        branches[position] = 0b10011;
    }else{
        branches[position] = 0b11001;
    }
}

void        getNodeTypeRR(const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_XY_SIZE])
{
    ///equalRight_oppositeRight
    if(mpz_tstbit(number, position) == mpz_tstbit(result, position))
    {
        branches[position] = 0b10011;
    }else{
        branches[position] = 0b10110;
    }
}
void         makeResult(mpz_t& result, const mpz_t& previousResult, unsigned int position, unsigned int branchType, mpz_t& x, mpz_t& y, mpz_t& diff)
{
    switch (branchType & 0b11)
    {
        case 0b00:
            mpz_set(result, previousResult);
            return;
        case 0b11:
            mpz_set(result, previousResult);
            mpz_mul_2exp(diff, diff, position);
            mpz_add(diff, x, diff);
            mpz_add(diff, y, diff);
            mpz_mul_2exp(diff, diff, position);
            mpz_add(result, result, diff);
            mpz_div_2exp(diff, diff, position);
            mpz_set_ui(diff, 1);
            return;
        case 0b10:
            mpz_set(result, previousResult);
            mpz_mul_2exp(x, x, position);
            mpz_add(result, result, x);
            mpz_div_2exp(x, x, position);
            return;
        case 0b01:
            mpz_set(result, previousResult);
            mpz_mul_2exp(y, y, position);
            mpz_add(result, result, y);
            mpz_div_2exp(y, y, position);
            return;
    }
}

void         setXY(mpz_t& x, mpz_t& y, unsigned int position, unsigned int branchType)
{
    branchType & 0b01 ? mpz_setbit(x, position) : mpz_clrbit(x, position);
    branchType & 0b10 ? mpz_setbit(y, position) : mpz_clrbit(y, position);
}

void         resetXY(mpz_t& x, mpz_t& y, unsigned int position)
{
    mpz_clrbit(x, position);
    mpz_clrbit(y, position);
}

char*        readResults(Result *root, char charBuffer[1024])
{
    if(mpz_cmp_ui(root->left->number, 1))
    {
        readResults(root->left, charBuffer);
        readResults(root->right, charBuffer);
    }else{
        char temp_char[MAX_N_SIZE];
        mpz_get_str(temp_char, 10, root->number);
        strcat(charBuffer, " * ");
        strcat(charBuffer, temp_char);
    }
    return charBuffer;
}