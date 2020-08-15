//
// Created by blackberry on 27.07.2020.
//

#include "../include/Step_Functions.h"

///Single functions
void        getNodeType(const mpz_int& number, const mpz_int& result, unsigned int position, unsigned int branches[MAX_XY_SIZE])
{
    ///if(bit_test(number, position) ^ bit_test(result, position))/// - converted to mpz
    if(mpz_tstbit(number.backend().data(), position) ^ mpz_tstbit(result.backend().data(), position))
    {
//        branches[position] = 0b11100;
        branches[position] = 0b11001;

    }else{

//        branches[position] = 0b11001;
        branches[position] = 0b11100;
    }
    ///The operations can and should be avoided by setting return branch types when launching the thread
}
void         makeResult(mpz_int& result, const mpz_int& previousResult, unsigned int position,
                        unsigned int branchType, mpz_int& x, mpz_int& y, mpz_int& diff)
{
    switch (branchType & 0b11)
    {
        case 0b00:
            ///result = previousResult;/// - converted to mpz
            mpz_set(result.backend().data(), previousResult.backend().data());
            return;
        case 0b11:
            ///result = previousResult + ((0b1 << position) + x + y) << position ;/// converted to mpz
            mpz_set(result.backend().data(), previousResult.backend().data());
            mpn_lshift(diff.backend().data()->_mp_d, diff.backend().data()->_mp_d,
                       diff.backend().data()->_mp_size, position);
            mpz_add(diff.backend().data(), x.backend().data(), diff.backend().data());
            mpz_add(diff.backend().data(), y.backend().data(), diff.backend().data());
            mpz_mul_2exp(diff.backend().data(), diff.backend().data(), position);
            mpz_add(result.backend().data(), result.backend().data(), diff.backend().data());
            mpz_div_2exp(diff.backend().data(), diff.backend().data(), position);
            mpz_set_ui(diff.backend().data(), 1);
            return;
        case 0b10:
            ///result = previousResult + (x << position);/// converted to mpz
            mpz_set(result.backend().data(), previousResult.backend().data());
            mpz_mul_2exp(x.backend().data(), x.backend().data(), position);
            mpz_add(result.backend().data(), result.backend().data(), x.backend().data());
            mpz_div_2exp(x.backend().data(), x.backend().data(), position);
            return;
        case 0b01:
            ///result = previousResult + (y << position);///
            mpz_set(result.backend().data(), previousResult.backend().data());
            mpz_mul_2exp(y.backend().data(), y.backend().data(), position);
            mpz_add(result.backend().data(), result.backend().data(), y.backend().data());
            mpz_div_2exp(y.backend().data(), y.backend().data(), position);
            return;
    }


}

///Composite functions
void         setXY(mpz_int& x, mpz_int& y, unsigned int position, unsigned int branchType)
{
    branchType & 0b01 ? mpz_setbit(x.backend().data(), position) : mpz_clrbit(x.backend().data(), position);
    branchType & 0b10 ? mpz_setbit(y.backend().data(), position) : mpz_clrbit(y.backend().data(), position);
}

void         resetXY(mpz_int& x, mpz_int& y, unsigned int position)
{
    mpz_clrbit(x.backend().data(), position);
    mpz_clrbit(y.backend().data(), position);
}
