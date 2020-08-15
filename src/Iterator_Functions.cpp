//
// Created by blackberry on 27.07.2020.
//

#include "../include/Iterator_Functions.h"
char* buffer;
char *print_binary(mpz_t& number)                                                                       /// returns a string with the number in binary
{

    return mpz_get_str(buffer, 10, number);
}

void widthIterate(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size,
                  const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size)

{
    if(position < xy_size) {
        unsigned int strategy = 11001001; ///to be introduced as parameter

        getNodeType(number, results[position - 1], position, branches);
//        std::cout << "Width step: " << position << " branch " << branches[position] << "\n";

        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1],
                       position, branches[position], x, y, diff);
//            std::cout << "Node result: " << results[position] << "\n";
            setXY(x, y, position, branches[position]);
//            std::cout << "X/Y: " << x << "/" << y << "\n\n";
            widthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
            resetXY(x, y, position);

            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1],
                       position, branches[position], x, y, diff);

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
        ///
    }
}

void depthIterate(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size,
                  const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size)
{
    if (position < xy_size)                                                                            /// checks if the position is in generation range
    {
//        std::cout << "\nDepth step: " << position << " branch " << branches[position] << "\n";
        makeResult(results[position], results[position - 1],
                  position, branches[position], x, y, diff);

//        std::cout << "Node result: " << results[position] << "\n";
        setXY(x, y, position, branches[position]);
//        std::cout << "X/Y: " << x << "/" << y << "\n\n";

        getNodeType(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 && (position + 1 < xy_size))
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterate(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]

    } else if (position < number_size)                                                                 /// checks if the position in len(n) range
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
}

void OFI(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
         unsigned int xy_size, unsigned int position, unsigned int branches[MAX_N_SIZE])
{

//    std::cout << "OFI accessed with position " << position << ", result "<< print_binary(results[xy_size]) << "\n";
    unsigned int steps = xy_size - mpz_sizeinbase(y, 2);
    ///results[position] = results[position - 1];/// - converted to backend mpz_t
    mpz_set(results[position], results[position - 1]);

    for (int i = 0; i < steps; ++i)
    {
//        std::cout << "OFI: " << position <<  " branch " << branches[position] << "\n";

        if ((branches[position] & 0b11) == 0b01)
        {
            ///results[xy_size] += (y << position);/// - converted to mpz
            mpz_mul_2exp(diff, y, position);
            mpz_add(results[xy_size], results[xy_size], diff);
            ///bit_set(x, position);/// - converted to backend mpz
            mpz_setbit(x, position);
        }
//        std::cout << "X: " << x << " Y: " << y << "\n";
//        std::cout << "Result: " << results[xy_size] << "\n\n";
            ++position;

            getNodeType(results[xy_size], number, position, branches);

    }

    ///if (number == results[xy_size])/// - converted to backend mpz
    if (mpz_cmp(number, results[xy_size]) == 0)
    {

        std::cout << print_binary(x) << " * " << print_binary(y) << " = " << print_binary(results[xy_size]) << std::endl;
    }

    for (int i = 0; i <= steps; ++i)
    {
        --position;
        ///bit_unset(x, position);/// - converted to mpz
        mpz_clrbit(x, position);
    }
    ///results[xy_size] = 1;/// - converted to mpz
    mpz_set_ui(results[xy_size], 1);
    mpz_set_ui(diff, 1);
}

void checkResult(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int xy_size,
                 const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size)
{
//    std::cout << "checkResult: " << position << "\n"
    ///if ((bit_test(results[position - 1], number_size)) || (bit_test(results[position - 1], number_size + 1)))/// - converted to mpz
    if((mpz_tstbit(results[position - 1], number_size) == 1) ||
       (mpz_tstbit(results[position - 1], number_size + 1) == 1))
    {
//        std::cout << "Overflow bit triggered on number " << results[position - 1];
        return;                                                                                        /// comparing 2 bits instead of the whole number, allows for cheap branch pruning
    }

    ///if (results[position - 1] == number) /// - converted to mpz
    int compared_result = mpn_cmp(results[position - 1]->_mp_d,
                                  number->_mp_d,
                                  number->_mp_size);
    if (compared_result == 0)
    {
        std::cout << "Result_found " << print_binary(x) << " * " << print_binary(y) << " = " << print_binary(results[position - 1]);
        return;

    ///} else if (results[position - 1] > number)/// - converted to mpz
    } else if (compared_result > 0)
    {                                                                                                  /// should never be called because of the overflow bit check. Kept for sanity check
//        std::cout << "Overflow bit triggered on number " << results[position - 1];
        return;

    } else if ((branches[xy_size - 1] & 0b11) == 0b11)
    {
//        std::cout << "XY max size reached on position " << xy_size - 1 << "with branch" << branches[xy_size - 1];
        return;                                                                                        /// drops the branch

    } else if ((branches[xy_size] & 0b11) == 0b11)                                                                 /// checks if the next bits of X and Y are both equal to 1
    {
//        std::cout << "XY max size reached on position " << xy_size << "with branch" << branches[xy_size];
        return;                                                                                        /// drops the branch

    } else if ((branches[xy_size - 1]  & 0b11) == 0b01)                                                             /// checks if X > Y
    {
        OFI(x, y, diff, number, results, xy_size, position, branches);                       /// starts the one factor iteration

    } else if ((branches[xy_size - 1]  & 0b11)  == 0b10)                                                             /// checks if Y > X
    {
        OFI(y, x, diff, number, results, xy_size, position, branches);                          /// starts the one factor iteration

    } else if ((branches[xy_size - 1]  & 0b11) == 0b00)                                                            /// checks if the numbers have the last bits equal to 0
    {
        OFI(x, y, diff, number, results, xy_size, position, branches);                          /// starts the one factor iteration as X > Y
        OFI(y, x, diff, number, results, xy_size, position, branches);                          /// starts the one factor iteration as Y > X
    }
    return;
}
