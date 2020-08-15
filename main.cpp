#include <iostream>
#include "include/Memory_Functions.h"

int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;

    bool use_struct = 1;
    if(use_struct){
        Runner thread_1;

        char number_string[] = "123123112154177777";
        unsigned int base = 10;
        mpz_init_set_str(thread_1.number, number_string, base);
        thread_1.x;
        thread_1.y;
        thread_1.results[MAX_XY_SIZE + 1];


        thread_1.branches[MAX_N_SIZE];

        thread_1.number_size = mpn_sizeinbase(thread_1.number->_mp_d, thread_1.number->_mp_size, 2);
        thread_1.xy_size = thread_1.number_size / 2 + 1;
        unsigned int starting_position = 1;

        std::cout << "Number size:" << thread_1.number_size << "\n";
        std::cout << "XY size: " << thread_1.xy_size << "\n";

        generateTree(thread_1.results, thread_1.branches, thread_1.x, thread_1.y,
                     thread_1.diff, thread_1.xy_size, thread_1.number_size);

        clock_t start, end;
        double cpu_time_used;
        start = clock();
        widthIterate(thread_1.x, thread_1.y, thread_1.diff, thread_1.number, thread_1.results,
                     thread_1.xy_size, starting_position, thread_1.branches, thread_1.number_size);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << cpu_time_used << "seconds for " << thread_1.number_size << "bits" << std::endl;
    }else{
        char number_string[] = "123123112154177777";
        unsigned int base = 10;
        mpz_t number;
        mpz_init_set_str(number, number_string, base);
        mpz_t x;
        mpz_t y;
        mpz_t diff;
        mpz_t results[MAX_XY_SIZE + 1];

        unsigned int branches[MAX_N_SIZE];

        unsigned int number_size = mpn_sizeinbase(number->_mp_d, number->_mp_size, 2);
        unsigned int xy_size = number_size / 2 + 1;
        unsigned int starting_position = 1;

        std::cout << "Number size:" << number_size << "\n";
        std::cout << "XY size: " << xy_size << "\n";

        generateTree(results, branches, x, y, diff, xy_size, number_size);

        clock_t start, end;
        double cpu_time_used;
        start = clock();
        widthIterate(x, y, diff, number, results, xy_size, starting_position, branches, number_size);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << cpu_time_used << "seconds for " << number_size << "bits" << std::endl;

    }
    return 0;
}
