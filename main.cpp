#include <iostream>
#include "include/Memory_Functions.h"

int main(int argc, char* argv[])
{
    char execution_type = 'x';
    switch (execution_type)
        case 't':
            using namespace boost::multiprecision;

            mpz_int number;
            mpz_int result;
            mpz_int previousResult;
            mpz_int x;
            mpz_int y;
            bool verbose = 0;

            test_getNodeType(number, result, verbose);
            test_setXY(x, y, verbose);
            test_makeResult(result, previousResult, x, y, verbose);
            test_resetXY(x, y, 1);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
