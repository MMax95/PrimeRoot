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

    ///!!!!! uint8_t_t8 should be addresed with template metaprogramming
    uint nSize = 0;
    uint8_t xySize = 0;
    uint8_t blocksPerLimb = 0;
    uint X0 = 0;
    uint Y0 = 0;
    uint8_t baseMask = 0;
    unsigned long long base2exp = 0;
    uint base = 0;
    uint8_t numberSegments[MAX_N_SIZE];
    mpz_t *maskList;
    uint8_t ***modTable;
    uint branches[MAX_N_SIZE]; ///Remember the target number and the factor index
    uint8_t xSegments[MAX_N_SIZE];
    uint8_t ySegments[MAX_N_SIZE];

    mpz_t targetNumber;
    mpz_t temp;
    mpz_t x;
    mpz_t y;
    mpz_t results[MAX_N_SIZE];

    bool variablesInitialized = 0;
    int currentPosition = -1;

    ///Utility functions
    uint8_t ***generateModTable(uint8_t ***modTable) const;
    mpz_t *generateMaskList(mpz_t *maskList) const;
    static bool checkModTable(uint8_t ***modTable);
    static bool checkMaskList(const mpz_t *maskList);
    void generateStaticStructures(uint8_t ***modTableDestination, mpz_t *maskListDestination);
    bool bindStaticStructures(uint8_t ***modTableSource, mpz_t *maskListSource);
    uint8_t segmentNumber(mpz_t number);
    static bool addResult(mpz_t xSolution, mpz_t ySolution);

    ///Iterator functions
    void initialIterator (int position);
    void widthSubIterator(int position);
    void depthSubIterator(int position);
    void checkResult(int position, mpz_t result);

    ///Step functions
    void setFactor(uint8_t segment, int position, mpz_t number);
    void getSubResult(uint8_t xSegment, uint8_t ySegment, mpz_t result, mpz_t previousResult);
    void resetNode(int position);

public:
    VB_Iterator(const char *numberString, uint8_t startingPosition, uint wanted2exp = 4,
                uint8_t ***generatedModTable = nullptr, mpz_t *generatedMaskList = nullptr,
                        bool generateTables = true);
    //UI Functions

    int startIteration(int strategy);

    void testTables();
};


#endif //PRIMEROOT_VB_ITERATOR_H
