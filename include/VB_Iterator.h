//
// Created by blackberry on 30.10.2020.
//

#ifndef PRIMEROOT_VB_ITERATOR_H
#define PRIMEROOT_VB_ITERATOR_H
#define MAX_ALLOWED_2EXP 8
#define ALU_SIZE 64
#define MAX_BASE 256
#define MAX_N_SIZE 64

#include <boost/multiprecision/gmp.hpp>
#include <boost/container/list.hpp>



class VB_Iterator {

private:
    ///Local variables
    uint nSize = 0;
    uint xySize = 0;
    uint X0 = 0;
    uint Y0 = 0;
    uint base2exp = 0;
    uint base = 0;
    uint numberSegments[MAX_N_SIZE];
    uint ***modTable;
    uint branches[MAX_N_SIZE]; ///Remember the target number and the factor index
    uint xSegments[MAX_N_SIZE];
    uint ySegments[MAX_N_SIZE];

    mpz_t targetNumber;
    mpz_t temp;
    mpz_t x;
    mpz_t y;
    mpz_t results[MAX_N_SIZE];
    mpz_t *maskList;
    mpz_t resultContainer;

    bool variablesInitialized = 0;
    int currentPosition = -1;

    ///Utility functions
    uint ***generateModTable(uint ***modTable) const;
    mpz_t *generateMaskList(mpz_t *maskList) const;
    void generateStaticStructures(uint ***modTableDestination, mpz_t *maskListDestination);
    bool bindStaticStructures(uint ***modTableSource, mpz_t *maskListSource);
    static bool addResult(mpz_t xSolution, mpz_t ySolution) ;

    ///Iterator functions
    void initialIterator (int position);
    void widthSubIterator(int position);
    void depthSubIterator(int position);
    void checkResult(int position, mpz_t result);

    ///Step functions
    void setFactor(uint segment, int position, mpz_t number);
    void getSubResult(uint xSegment, uint ySegment, mpz_t result, mpz_t previousResult);
    void resetNode(int position);

public:
    VB_Iterator(const char *numberString, uint startingPosition, uint wanted2exp = 4,
                uint ***generatedModTable = nullptr, mpz_t *generatedMaskList = nullptr,
                        bool generateTables = true);

    //UI Functions

    int startIteration(int strategy);
    int depthIteration(int strategy);

    void testTables();
};


#endif //PRIMEROOT_VB_ITERATOR_H
