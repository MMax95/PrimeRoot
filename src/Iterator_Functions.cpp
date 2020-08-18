//
// Created by blackberry on 27.07.2020.
//

#include "../include/Iterator_Functions.h"
char* buffer;
char *printNumber(mpz_t& number)
{
    return mpz_get_str(buffer, 10, number);
}

void widthIterate(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size)
{
    if(position < xy_size) {

        getNodeType(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
        } else if ((branches[position] == oppositeLeft) ||
                   (branches[position] == oppositeRight))
        {
            depthIterate(x, y, diff, number, results, xy_size, position, branches, number_size);
            branches[position] = branches[position] >> 2;
        }

    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   widthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if(position < xy_size) {

        getNodeTypeLL(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
        } else if ((branches[position] == oppositeLeft) ||
                   (branches[position] == oppositeRight))
        {
            depthIterateLL(x, y, diff, number, results, xy_size, position, branches, number_size);
            branches[position] = branches[position] >> 2;
        }

    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   widthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if(position < xy_size) {

        getNodeTypeLR(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
        } else if ((branches[position] == oppositeLeft) ||
                   (branches[position] == oppositeRight))
        {
            branches[position] = branches[position] >> 2;
            depthIterate(x, y, diff, number, results, xy_size, position, branches, number_size);

        }

    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   widthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if(position < xy_size) {

        getNodeTypeRL(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);
        } else if ((branches[position] == oppositeLeft) ||
                   (branches[position] == oppositeRight))
        {

            depthIterateRL(x, y, diff, number, results, xy_size, position, branches, number_size);
            branches[position] = branches[position] >> 2;
        }

    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   widthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    {
        if(position < xy_size) {

            getNodeTypeRR(number, results[position - 1], position, branches);
            if ((branches[position] == equalLeft) ||
                (branches[position] == equalRight))
            {
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
                resetXY(x, y, position);
                branches[position] = branches[position] >> 2;
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
                resetXY(x, y, position);
            } else if ((branches[position] == oppositeLeft) ||
                       (branches[position] == oppositeRight))
            {
                branches[position] = branches[position] >> 2;
                depthIterateRR(x, y, diff, number, results, xy_size, position, branches, number_size);

            }

        }else if(position < number_size)
        {
            checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
        }
    }
}

void depthIterate(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeType(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   depthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeLL(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   depthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeLR(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   depthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeRL(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;
            depthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}
void   depthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], const unsigned int xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeRR(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}

void OFI(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size, unsigned int position, unsigned int branches[MAX_N_SIZE])
{
    unsigned int steps = xy_size - mpz_sizeinbase(y, 2);
    mpz_set(results[position], results[position - 1]);
    for (int i = 0; i < steps; ++i)
    {
        if ((branches[position] & 0b11) == 0b01)
        {
            mpz_mul_2exp(diff, y, position);
            mpz_add(results[xy_size], results[xy_size], diff);
            mpz_setbit(x, position);
        }
        ++position;
        getNodeType(results[xy_size], number, position, branches);
    }
    if (mpz_cmp(number, results[xy_size]) == 0)
    {
        std::cout << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[xy_size]) << std::endl;
    }
    for (int i = 0; i <= steps; ++i)
    {
        --position;
        mpz_clrbit(x, position);
    }
    mpz_set_ui(results[xy_size], 1);
    mpz_set_ui(diff, 1);
}

void checkResult(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size)
{
    if(mpz_tstbit(results[position - 1], number_size) || mpz_tstbit(results[position - 1], number_size + 1))
    {
        return;
    }
    int compared_result = mpn_cmp(results[position - 1]->_mp_d, number->_mp_d, number->_mp_size);
    if (compared_result == 0)
    {
        std::cout << "Result_found " << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[position - 1]);
        return;
    } else if (compared_result > 0)
    {
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b11)
    {
        return;
    } else if ((branches[xy_size]     & 0b11) == 0b11)
    {
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b01)
    {
        OFI(x, y, diff, number, results, xy_size, position, branches);
    } else if ((branches[xy_size - 1] & 0b11) == 0b10)
    {
        OFI(y, x, diff, number, results, xy_size, position, branches);
    } else if ((branches[xy_size - 1] & 0b11) == 0b00)
    {
        OFI(x, y, diff, number, results, xy_size, position, branches);
        OFI(y, x, diff, number, results, xy_size, position, branches);
    }
}