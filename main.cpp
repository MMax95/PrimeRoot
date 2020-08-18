#include <iostream>
#include <string>
#include "include/Memory_Functions.h"

int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;

    if(argc > 1)
    {
        const char *number_string = argv[1];

        Runner thread_1;
        unsigned int starting_position = 1;
        mpz_init_set_str(thread_1.number, number_string, 10);
        thread_1.number_size = mpn_sizeinbase(thread_1.number->_mp_d, thread_1.number->_mp_size, 2);
        thread_1.xy_size = thread_1.number_size / 2 + 1;

        generateTree(thread_1.results, thread_1.branches, thread_1.x, thread_1.y, thread_1.diff, thread_1.xy_size, thread_1.number_size);

        if(argc > 2)
        {
            std::string strategy = argv[2];
            if(strategy == "LL")
            {
                std::cout << "Selected strategy: Equal Left - Opposite Left" << std::endl;
                clock_t start, end;
                double cpu_time_used;
                start = clock();
                widthIterateLL(thread_1.x, thread_1.y, thread_1.diff, thread_1.number, thread_1.results, thread_1.xy_size, starting_position, thread_1.branches, thread_1.number_size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << cpu_time_used << "seconds for " << thread_1.number_size << "bits " << std::endl;

            }else if(strategy == "LR")
            {
                std::cout << "Selected strategy: Equal Left - Opposite Right" << std::endl;
                clock_t start, end;
                double cpu_time_used;
                start = clock();
                widthIterateLR(thread_1.x, thread_1.y, thread_1.diff, thread_1.number, thread_1.results, thread_1.xy_size, starting_position, thread_1.branches, thread_1.number_size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << cpu_time_used << "seconds for " << thread_1.number_size << "bits " << std::endl;

            }else if(strategy == "RL")
            {
                std::cout << "Selected strategy: Equal Right - Opposite Left" << std::endl;
                clock_t start, end;
                double cpu_time_used;
                start = clock();
                widthIterateRL(thread_1.x, thread_1.y, thread_1.diff, thread_1.number, thread_1.results, thread_1.xy_size, starting_position, thread_1.branches, thread_1.number_size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << cpu_time_used << "seconds for " << thread_1.number_size << "bits " << std::endl;

            }else if(strategy == "RR")
            {
                std::cout << "Selected strategy: Equal Right - Opposite Right" << std::endl;
                clock_t start, end;
                double cpu_time_used;
                start = clock();
                widthIterateRR(thread_1.x, thread_1.y, thread_1.diff, thread_1.number, thread_1.results, thread_1.xy_size, starting_position, thread_1.branches, thread_1.number_size);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                std::cout << cpu_time_used << "seconds for " << thread_1.number_size << "bits " << std::endl;

            }else{
                std::cout << "Unknown strategy selected" << std::endl;
                return 0;
            }
            return 0;
        }


        std::cout << "Default L-L strategy selected" << std::endl;
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        widthIterate(thread_1.x, thread_1.y, thread_1.diff, thread_1.number, thread_1.results, thread_1.xy_size, starting_position, thread_1.branches, thread_1.number_size);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << cpu_time_used << "seconds for " << thread_1.number_size << "bits" << std::endl;


    } else {
        printf("No arguments provided.");
        return 0;
    }
    return 0;
}