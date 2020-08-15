//
// Created by blackberry on 27.07.2020.
//

#include "../include/Iterator_Functions.h"

void widthIterate(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                  unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE])

{
    if(position < xy_size) {
        unsigned int strategy = 11001001; ///to be introduced as parameter

        getNodeType(number, results[position - 1], position, branches);
//        std::cout << "Width step: " << position << " branch " << branches[position] << std::endl;

        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1],
                       position, branches[position], x, y);
//            std::cout << "Node result: " << results[position] << "\n";
            setXY(x, y, position, branches[position]);
//            std::cout << "X/Y: " << x << "/" << y << "\n\n";
            widthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
            setXY(x, y, position, 0b00);

            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1],
                       position, branches[position], x, y);

            setXY(x, y, position, branches[position]);
            widthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
            setXY(x, y, position, 0b00);

        } else if ((branches[position] == oppositeLeft) ||
                   (branches[position] == oppositeRight))
        {

            depthIterate(x, y, number, results, xy_size, number_size, position, branches);
            branches[position] = branches[position] >> 2;

        }

    }else if(position < number_size)
    {
        checkResult(x, y, number, results, xy_size, number_size, position, branches);
        ///
    }
}

void depthIterate(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                  unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE])
{
    if (position < xy_size)                                                                            /// checks if the position is in generation range
    {
//        std::cout << "\nDepth step: " << position << " branch " << branches[position] << std::endl;
        makeResult(results[position], results[position - 1],
                  position, branches[position], x, y);

//        std::cout << "Node result: " << results[position] << "\n";
        setXY(x, y, position, branches[position]);
//        std::cout << "X/Y: " << x << "/" << y << "\n\n";

        getNodeType(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
        if(branches[position + 1] & 0b10000 && (position + 1 < xy_size))
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterate(x, y, number, results, xy_size, number_size, position + 1, branches);
        }
        setXY(x, y, position, 0b00);                                                                       /// resets X[position] and Y[position]

    } else if (position < number_size)                                                                 /// checks if the position in len(n) range
    {
        checkResult(x, y, number, results, xy_size, number_size, position, branches);
    }
}

void OFI(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
         unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE])
{
    results[position] = results[position - 1];
//    std::cout << "OFI accessed with position " << position << ", result "<< results[xy_size] << "\n";
    unsigned int steps = xy_size - msb(y);                                                    /// calculates how many bits are necessary for len(x) + len(y) = len(n)

    for (int i = 0; i < steps; ++i)
    {
//        std::cout << "OFI: " << position <<  " branch " << branches[position] << "\n";

        if ((branches[position] & 0b11) == 0b01)
        {
            results[xy_size] += (y << position);
            bit_set(x, position);
        }
//        std::cout << "X: " << x << " Y: " << y << "\n";
//        std::cout << "Result: " << results[xy_size] << "\n\n";
            ++position;
            getNodeType(results[xy_size], number, position, branches);
    }

    if (number == results[xy_size])                                                             /// compare the result and number starting with the last generated position
    {
        std::cout << x << " * " << y << " = " << results[xy_size] << std::endl;
    }

    for (int i = 0; i <= steps; ++i)
    {
        --position;
        bit_unset(x, position);
    }
    results[xy_size] = 1;
}

void checkResult(mpz_int& x, mpz_int& y, mpz_int& number, mpz_int results[MAX_XY_SIZE], unsigned int xy_size,
                 unsigned int number_size, unsigned int position, unsigned int branches[MAX_N_SIZE])
{
//    std::cout << "checkResult: " << position << std::endl;
    if ((bit_test(results[position - 1], number_size)) || (bit_test(results[position - 1], number_size + 1)))          /// checks bits result[position] and result[position + 1] for overflow
    {
//        std::cout << "Overflow bit triggered on number " << results[position - 1];
        return;                                                                                        /// comparing 2 bits instead of the whole number, allows for cheap branch pruning
    }

    if (results[position - 1] == number)                                                                          /// compare the result and number starting with the last generated position
    {
        std::cout << "Result_found " << x << " * " << y << " = " << results[position - 1];
        return;

    } else if (results[position - 1] > number)
    {                                                                                                  /// should never be called because of the overflow bit check. Kept for sanity check
//        std::cout << "Overflow bit triggered on number " << results[position - 1];
    } else if ((branches[xy_size - 1] & 0b11) == 0b11)                                                             /// checks if the factors have the last bits set to 1
    {
        // if the last bits of X and Y are set, there are no further branches that can be accessed,
        // since len(x) + len(y) must be equal to len(n) or len(n) + 1
        return;                                                                                        /// drops the branch

    } else if ((branches[xy_size] & 0b11) == 0b11)                                                                 /// checks if the next bits of X and Y are both equal to 1
    {
        // if x[xy_size] and y[xy_size] are both 1, that means len(x) + len(y) > len(n) + 1
        return;                                                                                        /// drops the branch

    } else if ((branches[xy_size - 1]  & 0b11) == 0b01)                                                             /// checks if X > Y
    {
        OFI(x, y, number, results, xy_size, number_size, position, branches);                       /// starts the one factor iteration

    } else if ((branches[xy_size - 1]  & 0b11)  == 0b10)                                                             /// checks if Y > X
    {
        OFI(y, x, number, results, xy_size, number_size, position, branches);                          /// starts the one factor iteration

    } else if ((branches[xy_size - 1]  & 0b11) == 0b00)                                                            /// checks if the numbers have the last bits equal to 0
    {
        OFI(x, y, number, results, xy_size, number_size, position, branches);                          /// starts the one factor iteration as X > Y
        OFI(y, x, number, results, xy_size, number_size, position, branches);                          /// starts the one factor iteration as Y > X
    }
    return;
}
