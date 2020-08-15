#include <iostream>
#include "include/Memory_Functions.h"

int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;

    Runner thread_1;

    thread_1.number = 123123112154177777;
    thread_1.x;
    thread_1.y;
    thread_1.results[MAX_XY_SIZE + 1];

    thread_1.branches[MAX_N_SIZE];

    thread_1.number_size = msb(thread_1.number) + 1;
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
    gmp_printf("%f seconds for %d bits", cpu_time_used, thread_1.number_size);


    return 0;
}
