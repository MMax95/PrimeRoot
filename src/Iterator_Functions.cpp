//
// Created by blackberry on 27.07.2020.
//
#define MAX_N_SIZE 1024
#define MAX_XY_SIZE
#include "../include/Iterator_Functions.h"
void widthSource        (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                        unsigned int position, unsigned int branchType, unsigned int branches[]);

void widthIterate       (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                        unsigned int position, unsigned int branchType, unsigned int branches[]);

void widthOFI           (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                        unsigned int position, unsigned int branchType, unsigned int branches[]);

void depthSource        (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                        unsigned int number_size, unsigned int position, unsigned int branches[])
{
    if (position < xy_size)                                                                            /// checks if the position is in generation range
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y);     /// generates node result
        setXY(x, y, position, branches[position]);

        getNodeType(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
        if(branches[position + 1] & 0b10000 && (position + 1 < xy_size))
        {
                branches[position + 1] = !branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]

    } else if (position < number_size)                                                                 /// checks if the position in len(n) range
    {
                          /// checks the result for the given position
    }

}

void depthIterate       (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                        unsigned int number_size, unsigned int position, unsigned int branches[])
{
    if (position < xy_size)                                                                            /// checks if the position is in generation range
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y);     /// generates node result
        setXY(x, y, position, branches[position]);

        getNodeType(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
        if(branches[position + 1] & 0b10000 && (position + 1 < xy_size))
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]

    } else if (position < number_size)                                                                 /// checks if the position in len(n) range
    {
    /// checks the result for the given position
    }
}

void depthOFI           (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[], unsigned int xy_size,
                        unsigned int position, unsigned int branchType, unsigned int branches[])
{
    unsigned int steps = xy_size - msb(x);                                                    /// calculates how many bits are necessary for len(x) + len(y) = len(n)
    results[xy_size] = results[xy_size - 1];                                                                      /// allocates the previous result into a container variable

    for (int i = 0; i < steps; ++i)                                                                    /// lengthens the bigger factor by the number of missing bits from the smaller factor
    {
        if (branches[position] == 9)                                                                   /// if branch type is bigger[p] = 1, smaller[p] = 0, add diff << position to the temporary result
        {
            results[xy_size] += y << position;
            bit_set(x, position);
        }
        ++position;
        getNodeType(results[xy_size], number, position, branches);
    }

    if (number == results[xy_size])                                                             /// compare the result and number starting with the last generated position
    {
//        add_solution(x, y);                                                                 /// adds solution if the numbers match
        gmp_printf("???????????Solution X: %Zd and Y: %Zd found ????????????\n\n", &x.backend(), &y);
        gmp_printf("Number:   %0s\n", &number.backend());
        gmp_printf("Result:   %0s\n", &results[xy_size].backend());
        gmp_printf("X :       %0s\n", &x.backend());
        gmp_printf("Y :       %0s\n", &y.backend());
    }

    for (int i = 0; i <= steps; ++i) {
        --position;
        bit_unset(x, position);
    }

    results[xy_size] = 1;
}

void reallocateThread   (mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[],
                        unsigned int position, unsigned int branchType, unsigned int branches[]);