//
// Created by blackberry on 27.07.2020.
//

#include "../include/Memory_Functions.h"

void generateNode(mpz_int &result, unsigned int position)

{
    mpz_init_set_d(result.backend().data(), 1);
    mpz_realloc2(result.backend().data(), (position * 2 + 1));
}

void generateTree(mpz_int results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE],
                  mpz_int& x, mpz_int& y, mpz_int& diff,
                  unsigned int xy_size, unsigned int number_size)
{
    {
        for (int i = 0; i < xy_size + 1; ++i)                                                              /// generates xy_size nodes
        {
            generateNode(results[i], i);
        }

        for (int j = 0; j < number_size; ++j)                                                              /// initializes the branch type list with 0s
        {
            branches[j] = 0;
        }

        mpz_init_set_d(x.backend().data(), 1);                                                                              /// initializes X variable with 1
        mpz_init_set_d(y.backend().data(), 1);
        mpz_init_set_d(diff.backend().data(), 1);
        mpz_init_set_d(results[xy_size].backend().data(), 1);

        mpz_realloc2(x.backend().data(), number_size);
        mpz_realloc2(y.backend().data(), number_size);
        mpz_realloc2(diff.backend().data(), number_size);
        mpz_realloc2(results[xy_size].backend().data(), number_size);

        gmp_printf("\nTree generated for depth %d\n", xy_size);
    }
}