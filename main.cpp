#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "include/VB_Iterator.h"

int main(int argc, char* argv[]) {
    if(argc > 1)
    {
        uint startingPosition = 0;
        uint wanted2exp = 8;
        uint ***modTablePointer;
        mpz_t *maskListPointer;
        bool generateContainersCheck = true;

        VB_Iterator currentIterator(argv[1], startingPosition, wanted2exp, modTablePointer, maskListPointer, generateContainersCheck);
//        currentIterator.testTables();
        currentIterator.startIteration(0);

    }else{
        uint startingPosition = 0;
        uint wanted2exp = 2;
        uint ***modTablePointer;
        mpz_t *maskListPointer;
        bool generateContainersCheck = true;

        VB_Iterator currentIterator("491225948883077", startingPosition, wanted2exp, modTablePointer, maskListPointer, generateContainersCheck);
        currentIterator.testTables();
        currentIterator.startIteration(0);
//        std::cout << "Please provide a number" << std::endl;
    }
}