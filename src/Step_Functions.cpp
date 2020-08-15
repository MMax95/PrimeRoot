//
// Created by blackberry on 27.07.2020.
//

#include "../include/Step_Functions.h"

///Single functions
void        getNodeType(const mpz_t& number, const mpz_t& result, unsigned int position, unsigned int branches[MAX_XY_SIZE])
{
    ///if(bit_test(number, position) ^ bit_test(result, position))/// - converted to mpz
    if(mpz_tstbit(number, position) ^ mpz_tstbit(result, position))
    {

        branches[position] = 0b11001;

    }else{

        branches[position] = 0b11100;
    }
    ///The operations can and should be avoided by setting return branch types when launching the thread
}
void         makeResult(mpz_t& result, const mpz_t& previousResult, unsigned int position,
                        unsigned int branchType, mpz_t& x, mpz_t& y, mpz_t& diff)
{
    switch (branchType & 0b11)
    {
        case 0b00:
            ///result = previousResult;/// - converted to mpz
            mpz_set(result, previousResult);
            return;
        case 0b11:
            ///result = previousResult + ((0b1 << position) + x + y) << position ;/// converted to mpz
            mpz_set(result, previousResult);
            mpn_lshift(diff->_mp_d, diff->_mp_d,
                       diff->_mp_size, position);
            mpz_add(diff, x, diff);
            mpz_add(diff, y, diff);
            mpz_mul_2exp(diff, diff, position);
            mpz_add(result, result, diff);
            mpz_div_2exp(diff, diff, position);
            mpz_set_ui(diff, 1);
            return;
        case 0b10:
            ///result = previousResult + (x << position);/// converted to mpz
            mpz_set(result, previousResult);
            mpz_mul_2exp(x, x, position);
            mpz_add(result, result, x);
            mpz_div_2exp(x, x, position);
            return;
        case 0b01:
            ///result = previousResult + (y << position);///
            mpz_set(result, previousResult);
            mpz_mul_2exp(y, y, position);
            mpz_add(result, result, y);
            mpz_div_2exp(y, y, position);
            return;
    }


}

///Composite functions
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
