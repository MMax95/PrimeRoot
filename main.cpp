#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "include/VB_Iterator.h"

int main(int argc, char* argv[]) {
    if(argc > 1)
    {
        uint8_t startingPosition = 0;
        uint wanted2exp = 8;
        uint8_t ***modTablePointer;
        mpz_t *maskListPointer;
        bool generateContainersCheck = true;

        VB_Iterator currentIterator(argv[1], startingPosition, wanted2exp, modTablePointer, maskListPointer, generateContainersCheck);
        std::cout << "Checkpoint main" << std::endl;
//        currentIterator.testTables();
        currentIterator.startIteration(0);

    }else{
        std::cout << "Please provide a number" << std::endl;
    }
}