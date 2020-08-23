#include <iostream>
#include <string>
#include "include/Memory_Functions.h"

int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;

    if(argc > 1)
    {
        unsigned int runnerIndex = 1;
        const char *number_string = argv[1];
        unsigned int threadNumber = 1;
        Runner threads[threadNumber];
        unsigned int starting_position = 1;
        mpz_init_set_str(threads[0].number, number_string, 10);
        threads[0].number_size = mpn_sizeinbase(threads[0].number->_mp_d, threads[0].number->_mp_size, 2);
        threads[0].xy_size = threads[0].number_size / 2 + 1;

        generateTree(threads[0].results, threads[0].branches, threads[0].x, threads[0].y, threads[0].diff, threads[0].xy_size, threads[0].number_size);

        if(argc > 2)
        {
            std::string strategy = argv[2];
            StrategyType chosenStrategy;
            if(strategy == "LL")
            {
                chosenStrategy = LL;
                std::cout << "Selected strategy: Equal Left - Opposite Left" << std::endl;
            }else if(strategy == "LR")
            {
                chosenStrategy = LR;
                std::cout << "Selected strategy: Equal Left - Opposite Right" << std::endl;
            }else if(strategy == "RL")
            {
                chosenStrategy = RL;
                std::cout << "Selected strategy: Equal Right - Opposite Left" << std::endl;
            }else if(strategy == "RR")
            {
                chosenStrategy = RR;
                std::cout << "Selected strategy: Equal Right - Opposite Right" << std::endl;
            }else{
                std::cout << "Unknown strategy selected" << std::endl;
                return 0;
            }
            clock_t start, end;
            double cpu_time_used;
            start = clock();
            widthIterateAllocator(threads[0].x, threads[0].y, threads[0].diff, threads[0].number, threads[0].results,
                                  threads[0].xy_size, starting_position, threads[0].branches, threads[0].number_size, chosenStrategy,
                                  threads, threads[0].runnerID, threadNumber, runnerIndex);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            std::cout << cpu_time_used << "seconds for " << threads[0].number_size << "bits " << std::endl;
            return 0;
        }


        std::cout << "Default L-L strategy selected" << std::endl;
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        widthIterate(threads[0].x, threads[0].y, threads[0].diff, threads[0].number, threads[0].results, threads[0].xy_size, starting_position, threads[0].branches, threads[0].number_size);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << cpu_time_used << "seconds for " << threads[0].number_size << "bits" << std::endl;


    } else {
        printf("No arguments provided.");
        return 0;
    }
    return 0;
}