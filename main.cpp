#include <iostream>
#include "include/Memory_Functions.h"

int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;

    mpz_int number = 1231231121541777;
    mpz_int previousResult;
    mpz_int x;
    mpz_int y;
    mpz_int results[MAX_XY_SIZE + 1];

    unsigned int branches[MAX_N_SIZE];

    unsigned int number_size = msb(number) + 1;
    unsigned int xy_size = number_size / 2 + 1;
    unsigned int position = 1;

    std::cout << "Number size:" << number_size << std::endl;
    std::cout << "XY size: " << xy_size << std::endl;

    generateTree(results, branches, x, y, xy_size, number_size);

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    widthIterate(x, y, number, results, xy_size, number_size, position, branches);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    gmp_printf("%f seconds for %d bits", cpu_time_used, number_size);


    return 0;
}
