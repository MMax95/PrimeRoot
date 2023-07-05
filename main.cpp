#include <iostream>
#include <string>
#include "include/Memory_Functions.h"



int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;
    if(argc > 1)
    {
        const char *number_string = argv[1];
        Runner threads[THREAD_NUMER];
        unsigned int starting_position = 1;

        mpz_t targetNumber;
        mpz_init_set_str(targetNumber, number_string, 10);

        mpz_t one_mpz;
        mpz_init_set_d(one_mpz, 1);

        unique_factors.push_back(Result(one_mpz));
        unique_factors.back().left = unique_factors.back().right = &unique_factors.back();

        unique_factors.push_back(Result(targetNumber));

        Result &rootNode = unique_factors.back();

        if(argc > 2)
        {
            std::string strategy = argv[2];
            StrategyType chosenStrategy;

            if      (strategy == "LL"){
                chosenStrategy = LL;
            }else if(strategy == "LR"){
                chosenStrategy = LR;
            }else if(strategy == "RL"){
                chosenStrategy = RL;
            }else if(strategy == "RR"){
                chosenStrategy = RR;
            }else                     {
                std::cout << "Unknown strategy selected" << std::endl;
                return 3;
            }
            ///Initialize thread containers
            for(Runner thread : threads)
            {
                generateTree(thread.results, thread.branches, thread.x, thread.y,
                             thread.diff, thread.xy_size, thread.number_size);
            }
            clock_t start, end;
            double cpu_time_used;
            start = clock();
            widthIterateAllocator(chosenStrategy, threads, 0, 0, starting_position, unique_factors.back());
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            std::cout << cpu_time_used << "seconds for " << mpz_sizeinbase(targetNumber, 2) << "bits " << std::endl;

            std::cout << "\n";
            char charBuffer[1024] = "";
            strcat(charBuffer, "1");
            std::cout << readResults(&rootNode, charBuffer) << std::endl;
            return 0;
        } else {
            std::cout << "No strategy selected" << std::endl;
            return 2;
        }

    } else {
        printf("No arguments provided.");
        return 1;
    }
}