//
// Created by blackberry on 27.07.2020.
//

#include "../include/Memory_Functions.h"

void generateNode(mpz_t& result, unsigned int position)

{
    mpz_init_set_d(result, 1);
    mpz_realloc2(result, (position * 2 + 1));
}

void generateTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE],
                  mpz_t& x, mpz_t& y, mpz_t& diff,
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

        mpz_init_set_d(x, 1);                                                                              /// initializes X variable with 1
        mpz_init_set_d(y, 1);
        mpz_init_set_d(diff, 1);
        mpz_init_set_d(results[xy_size], 1);

        mpz_realloc(x, number_size);                                                                 /// allocates space for n bits
        mpz_realloc(y, number_size);                                                                 /// allocates space for n bits
        mpz_realloc(diff, number_size);                                                                 /// allocates space for n
        mpz_realloc(results[xy_size], number_size);

        std::cout << "\nTree generated for depth " << xy_size << "\n";
    }
}