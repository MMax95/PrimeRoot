//
// Created by blackberry on 27.07.2020.
//

#include "../include/Step_Functions.h"

///Single functions
unsigned int getNodeType(const mpz_int& number, const mpz_int& result, unsigned int position, BranchType equalBranch, BranchType oppositeBranch)
{
    if(bit_test(number, position) ^ bit_test(result, position))
    {
        return oppositeBranch;
    }else{
        return equalBranch;
    }
    ///The operations can and should be avoided by setting return branch types when launching the thread
}
void         makeResult(mpz_int& result, const mpz_int& previousResult, unsigned int position, unsigned int branchType, const mpz_int& x, const mpz_int& y)
{
    switch (branchType & 0b11)
    {
        case 0b00:
            result = previousResult;
            break;
        case 0b11:
            result = previousResult + (((0b1 << position) + x + y) << position);
            break;
        case 0b10:
            result = previousResult + (x << position);
            break;
        case 0b01:
            result = previousResult + (y << position);
            break;
    }


}

///Composite functions
void         setXY(mpz_int& x, mpz_int& y, unsigned int position, unsigned int branchType)
{
    if(branchType & 0b01){
        bit_set(x, position);
//        std::cout << x << std::endl;
    }

    if(branchType & 0b10){
        bit_set(y, position);
//        std::cout << y << std::endl;
    }

}
void         resetXY(mpz_int& x, mpz_int& y, unsigned int position)
{
    bit_unset(x, position);
    bit_unset(y, position);
}

///Test functions
unsigned int test_getNodeType(mpz_int number, mpz_int result, bool verbose)
{

    number = 0b110011;
    result = 0b101011;
    unsigned int nodeType;
    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Strategy EL/OL" << std::endl;
    nodeType = getNodeType(number, result, 1, equalLeft, oppositeLeft);
    if(nodeType != equalLeft)
    {
        if(verbose)
            std::cout << "getNodeType failed at test EL/OL - E " << std::endl;
        return nodeType;
    }

    nodeType = getNodeType(number, result, 3, equalLeft, oppositeLeft);
    if(nodeType != oppositeLeft)
    {
        if(verbose)
            std::cout << "getNodeType failed at test EL/OL - O " << std::endl;
        return nodeType;
    }
    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Strategy EL/OR" << std::endl;
    nodeType = getNodeType(number, result, 2, equalLeft, oppositeRight);
    if(nodeType != equalLeft)
    {
        if(verbose)
            std::cout << "getNodeType failed at test EL/OR - E " << std::endl;
        return nodeType;
    }

    nodeType = getNodeType(number, result, 4, equalLeft, oppositeRight);
    if(nodeType != oppositeRight)
    {
        if(verbose)
            std::cout << "getNodeType failed at test EL/OR - O " << std::endl;
        return nodeType;
    }
    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Strategy ER/OL" << std::endl;
    nodeType = getNodeType(number, result, 1, equalRight, oppositeLeft);
    if(nodeType != equalRight)
    {
        if(verbose)
            std::cout << "getNodeType failed at test ER/OL - E " << std::endl;
        return nodeType;
    }

    nodeType = getNodeType(number, result, 3, equalRight, oppositeLeft);
    if(nodeType != oppositeLeft)
    {
        if(verbose)
            std::cout << "getNodeType failed at test ER/OL - O " << std::endl;
        return nodeType;
    }
    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Strategy ER/OR" << std::endl;
    nodeType = getNodeType(number, result, 1, equalRight, oppositeRight);
    if(nodeType != equalRight)
    {
        if(verbose)
            std::cout << "getNodeType failed at test EL/OL - E " << std::endl;
        return nodeType;
    }

    nodeType = getNodeType(number, result, 3, equalRight, oppositeRight);
    if(nodeType != oppositeRight)
    {
        if(verbose)
            std::cout << "getNodeType failed at test EL/OL - O " << std::endl;
        return nodeType;
    }
    ///---------------------------------------------------------------------------------------------------------///

    std::cout << "getNodeType passed successfully" << std::endl;
    return 0;
}
unsigned int test_setXY(mpz_int x, mpz_int y, bool verbose)
{
    x = 0b1000;
    y = 0b1000;

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Set XY - equal left" << std::endl;
    setXY(x, y, 1, equalLeft);
    if((x != 0b1000) && (y != 0b1000))
    {
        if(verbose)
            std::cout << "setXY failed at test EL" << std::endl;
        return equalLeft & 0b11;
    }
    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Set XY - equal right" << std::endl;
    setXY(x, y, 1, equalRight);
    if((x != 0b1010) && (y != 0b1010))
    {
        if(verbose)
            std::cout << "setXY failed at test ER" << std::endl;
        std::cout << (equalRight & 0b11) << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        return equalRight & 0b11;
    }
    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Set XY - opposite left" << std::endl;
    setXY(x, y, 1, oppositeLeft);
    if((x != 0b1010) && (y != 0b1000))
    {
        if(verbose)
            std::cout << "setXY failed at test OL" << std::endl;
        return oppositeLeft & 0b11;
    }
    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///
    if(verbose)
        std::cout << "Set XY - opposite right" << std::endl;
    setXY(x, y, 1, oppositeRight);
    if((x != 0b1000) && (y != 0b1010))
    {
        if(verbose)
            std::cout << "setXY failed at test OR" << std::endl;
        return oppositeRight & 0b11;
    }
    ///---------------------------------------------------------------------------------------------------------///

    std::cout << "setXY passed successfully" << std::endl;
    return 0;
}
unsigned int test_resetXY(mpz_int x,mpz_int y, bool verbose)
{
    x = 0b10101;
    y = 0b10111;
    resetXY(x, y, 2);
    if((x != 0b10001) || (y != 0b10011))
    {
        std::cout << "resetXY failed" << std::endl;
        return 1;
    }
    std::cout << "resetXY passed successfully" << std::endl;
    return 0;
}
unsigned int test_makeResult(mpz_int result, mpz_int previousResult, mpz_int x, mpz_int y, bool verbose)
{
    result = 0b0;
    previousResult = 0b10001000;
    x = 0b111;
    y = 0b101;

    ///---------------------------------------------------------------------------------------------------------///

    if(verbose)
        std::cout << "Make Result - equal left" << std::endl;
    makeResult(result, previousResult, 3, equalLeft, x, y);
    if(result != 0b10001000)
    {
        std::cout << result << std::endl;
        std::cout << "makeResult failed at test EL" << std::endl;
        return 1;
    }

    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///

    if(verbose)
        std::cout << "Make Result - equal right" << std::endl;
    makeResult(result, previousResult, 3, 0b111, x, y);
    if(result != 0b100101000)
    {
        std::cout << result << std::endl;
        std::cout << "makeResult failed at test ER" << std::endl;
//        return 1;
    }

    ///---------------------------------------------------------------------------------------------------------///

    ///---------------------------------------------------------------------------------------------------------///

    if(verbose)
        std::cout << "Make Result - opposite left" << std::endl;
    makeResult(result, previousResult, 3, oppositeLeft, x, y);
    if(result != 0b10110000)
    {
        std::cout << result << std::endl;
        std::cout << "makeResult failed at test OL" << std::endl;
        return 1;
    }

    ///---------------------------------------------------------------------------------------------------------///

    result = 0b0;
    ///---------------------------------------------------------------------------------------------------------///

    if(verbose)
        std::cout << "Make Result - opposite right" << std::endl;
    makeResult(result, previousResult, 3, 0b110, x, y);
    if(result != 0b11000000)
    {
        std::cout << result << std::endl;
        std::cout << "makeResult failed at test OR" << std::endl;
        return 1;
    }
    ///---------------------------------------------------------------------------------------------------------///

    std::cout << "makeResult passed successfully" << std::endl;
    return 0;
}

