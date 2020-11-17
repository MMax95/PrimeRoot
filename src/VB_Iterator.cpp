//
// Created by blackberry on 30.10.2020.
//

#include "../include/VB_Iterator.h"

bool DEBUG_OUTPUT = false;

///Utility Functions
VB_Iterator::VB_Iterator(const char numberString[1024], uint8_t startingPosition, uint wanted2exp,
                         uint ***generatedModTable, uint64_t *generatedMaskList,
                         bool generateTables)
{
    ///Prepare all the containers for the working stream

    if(mpz_init_set_str(targetNumber, numberString, 10) == 0) ///if the string is a valid number in base 10
    {
        if(wanted2exp <= MAX_ALLOWED_2EXP)
        {
            if(64 % wanted2exp)
            {
                std::cout << "\nChosen exponent must be a divisor of 64" << std::endl;
                return;
            }else{
                base2exp = wanted2exp;
                blocksPerLimb = 64 / base2exp;
                base = pow(2, base2exp); ///assign the working base
                baseMask = base - 1;
                mpz_init_set_ui(temp, 0);
                nSize = segmentNumber(targetNumber); ///set nSize to the size of the target number in the working base
                if(nSize > 1) ///check if the number is not 1 or 0
                {
                    xySize = (nSize % 2) ? (nSize / 2 + 1) : (nSize / 2); /// set the max size of X and Y
                    if(true)
                    {
                        std::cout << "\nBase 2 Exponent: " << (int)base2exp;
                        std::cout << "\nBase: " << base;
                        std::cout << "\nBitmask: " << (int)baseMask;
                        std::cout << "\nNumber Size: " << (int)nSize;
                        std::cout << "\nX, Y Size: " << (int)xySize;
                    }

                    if(generateTables) /// check if the tables must be generated
                    {
                        if(DEBUG_OUTPUT){
                            std::cout << "\nGenerating tables for base " << base << std::endl;
                        }
                        generateStaticStructures(generatedModTable, generatedMaskList);
                    }else{ /// the tables are already in memory
                        if(DEBUG_OUTPUT){
                            std::cout << "\nBinding variables..." << std::endl;
                            std::cout << "\nGiven tables for base " << base << " valid. Binding data structures.";
                        }
                        bindStaticStructures(generatedModTable, generatedMaskList);
                    }

                    if(mpz_sizeinbase(targetNumber, base) != nSize)
                    {
                        std::cout << "Number segmentation error" << std::endl;
                        return;
                    }

                    for(uint8_t i = 0; i < xySize; ++i)
                    {
                        branches[i] = 0;
                        xSegments[i] = ySegments[i] = 0;
                        mpz_init(results[i]);
                        ///Space optimizations will be considered when implementing mpn functionality
                    }

                    mpz_init_set_ui(x, 0);
                    mpz_init_set_ui(y, 0);

                    if(DEBUG_OUTPUT)
                    {
                        std::cout << "All variables successfully initialized" << std::endl;
                    }
                    currentPosition = startingPosition;
                    variablesInitialized = true;

                }else{
                    std::cout << "Invalid number size:\n The input must be a number bigger than " << base << ".\n" << std::endl;
                    return;
                }
            }
        }else{
            std::cout << "\nSelected exponent is too big. Required memory: " << (pow(pow(2, wanted2exp), 2) * 8) / 1000000 << "GB";
        }
    }else{
        mpz_clear(targetNumber);
        std::cout << "Invalid number string:\n The input must be a valid base 10 number.\n" << std::endl;
        return;
    }
}
uint ***VB_Iterator::generateModTable(uint ***modTableDestination) const
{
    uint product;
    uint residue;
    uint carry;

    if(true){
        std::cout << "Allocating mod table containers for base " << base <<  std::endl;
    }

    modTableDestination = new uint **[base]();
    for (uint i = 0; i < base; ++i) {
        modTableDestination[i] = new uint *[base]();
        for (uint j = 0; j < base; ++j) {
            modTableDestination[i][j] = new uint [2]();
        }
    }
    if(DEBUG_OUTPUT) {
        std::cout << "Containers allocated successfully" << std::endl;
        std::cout << "Assigning mod table containers" << std::endl;
    }
    for (uint i = 0; i < base; ++i) {
        for (uint j = 0; j < base; ++j) {
            product = i * j;
            residue = product % base;
            carry = product / base;
            modTableDestination[residue][i][0] = j;
            modTableDestination[residue][i][1] = carry;
        }
    }
    if(DEBUG_OUTPUT){
        std::cout << "Containers assigned successfully" << std::endl;
    }
    return modTableDestination;
}

uint64_t *VB_Iterator::generateMaskList(uint64_t *maskListDestination) const
{
    if(true) {
        std::cout << "\n Generating " << ALU_SIZE / base2exp << "masks" << std::endl;
    }
    maskListDestination = new uint64_t [64/base2exp]();
    int maskNumber = ALU_SIZE / base2exp;
    for(unsigned long long i = 0; i < maskNumber; ++i){///for correct segmentation, the given base should be a divisor of 64
        maskListDestination[i] = UINT64_MAX & (baseMask << ((base2exp * i) % 64UL)); ///we associate a mask to every position.
        ///For a 8 bit table we have 8 masks, one for every 8 bits of the limb
        ///As a further optimization, the target number can have its segments calculated before starting the iteration.
    }

    if(DEBUG_OUTPUT) {
        std::cout << "Masks generated successfully" << std::endl;
    }
    return maskListDestination;
}

bool VB_Iterator::checkModTable(uint ***modTableSource)
{
    if(modTableSource != nullptr)
    {
        return false;
    }
    return true;
}

bool VB_Iterator::checkMaskList(const uint8_t maskListSource[MAX_N_SIZE])
{
    if(maskListSource != nullptr)
    {
        return false;
    }
    return true;
}

void VB_Iterator::generateStaticStructures(uint ***modTableDestination, uint64_t *maskListDestination)
{
    modTable = generateModTable(modTableDestination);
    maskList = generateMaskList(maskListDestination);
    if(DEBUG_OUTPUT){
        std::cout << "\n Static Structures generated" << std::endl;
    }
}

bool VB_Iterator::bindStaticStructures(uint ***modTableSource, uint64_t *maskListSource)
{
    maskList = maskListSource;
    modTable = modTableSource;
    return true; ///A check for proper pointer assigment should be implemented
}

uint8_t VB_Iterator::segmentNumber(mpz_t number)
{
    uint8_t segmentIndex = 0;
    mpz_set(temp, number);
    while(mpz_sgn(temp))
    {
        numberSegments[segmentIndex] = temp->_mp_d[0] & baseMask;
        mpz_div_2exp(temp, temp, base2exp);
        ++segmentIndex;
    }
    return segmentIndex;
}

bool VB_Iterator::addResult(mpz_t xSolution, mpz_t ySolution){
    gmp_printf("\nX: %Zd \n Y: %Zd \n", xSolution, ySolution);
    ///Return true if the result set is different than 1 and N
    return false;
}

///Iterator functions

void VB_Iterator::initialIterator(int position){
    if(position != 0){
        std::cout << "Wrong arguments provided to initial iterator. Position should be 0\n";
        return;
    }

    ///Assign the target number segment to branches[position][0]
    ///Branches[position][1] holds the X&Y pair index of the current node, or equivalently, the value of X[position] for the sum X+Y

    for(branches[position] = 1; branches[position] < base; branches[position] += 2) ///tree branching factor is defined by the base
    ///Since divisors of 2 are taken out and thus defined as 0 in our table

    {
        if(modTable[numberSegments[position]][branches[position]][0] < branches[position])
        {
            ///if the number pointed to by the table is smaller than the current number, we know it was already checked
            continue;
            ///we continue the iteration for the cases where X == Y
        }
        X0 = branches[position];
        Y0 = modTable[numberSegments[position]][X0][0];
        mpz_set_ui(x, X0);
        mpz_set_ui(y, Y0);
        ///Since the value of x*y is within ALU range, we can do a direct multiplication
        mpz_sub_ui(results[0], targetNumber, X0 * Y0);
        ///Initialize the current result as the right shifted previousResult
        mpz_div_2exp(results[0], results[0], base2exp);
        if(X0 == Y0)
        {

            ///do an initial check to see if the number is a perfect square - GMP implementation is faster
            if(true){
                std::cout << "\nInitial Iterator successfully called WidthIterator" << std::endl;
            }

            widthSubIterator(position + 1);
        } else { ///If x[p] != y[p], call depth iterator
            if(true){
                std::cout << "\nInitial Iterator successfully called DepthIterator" << std::endl;
            }
            depthSubIterator(position + 1);
        }
        resetNode(position); ///Possible useless, since values from deeper nodes always come cleaned up
    }
}

void VB_Iterator::depthSubIterator(int position){
    if(position < xySize) {
        if(DEBUG_OUTPUT){
            std::cout << "\nDepthIterator Called on position " << position << std::endl;
        }
        for (branches[position] = 0; branches[position] < base; ++branches[position]) {///Since X and Y are not identical anymore, we have to go through all the possible branches.
            if(DEBUG_OUTPUT){
                std::cout << "\nBranch " << branches[position] << std::endl;
            }
        ///Critical implementation: to avoid using the sum table, the underlying 8 bit unsigned container will be used to increment X and decrement Y on every step,
        /// using the max value to loop around in a cyclic manner
            xSegments[position] = modTable[branches[position]][Y0][0];
            ySegments[position] = modTable[(numberSegments[position] - branches[position])][X0][0];
            if(true){
                std::cout << "\nxSegment " << xSegments[position] << std::endl;
                std::cout << "\nySegment " << ySegments[position] << std::endl;
            }
            getSubResult(xSegments[position],ySegments[position],
                         results[position], results[position - 1]);
            setFactor(xSegments[position], position, x);
            setFactor(ySegments[position], position, y);
            depthSubIterator(position + 1);
        }
        resetNode(position);
    }else if(position == xySize){
        checkResult(position, results[position - 1]);
    }
}

void VB_Iterator::widthSubIterator(int position){

    if(position < xySize) {
        ///Since X0 and Y0 are determined, the both sum and mod tables now have to be used
        ///The for loop can be tweaked for different branch iteration order
        ///Since the width iterator assumes X == Y, half of the sum pairs can be overlooked, as any number bigger than (2^base2exp)/2 will produce mirror branches
        for (branches[position] = 0; branches[position] < pow(2, base2exp); ++branches[position])
        {
            xSegments[position] = modTable[branches[position]][Y0][0];
            ySegments[position] = modTable[(numberSegments[position] - branches[position])][X0][0];
            getSubResult(xSegments[position],ySegments[position],
                         results[position], results[position - 1]);
            setFactor(xSegments[position], position, x);
            setFactor(ySegments[position], position, y);
            if(xSegments[position] == ySegments[position])
            {
                widthSubIterator(position + 1);
            } else { ///If x[p] != y[p], call depth iterator
                depthSubIterator(position + 1);
            }
        }
        resetNode(position);
    }else if(position == xySize){
        checkResult(position, results[position - 1]);
    }

}

void VB_Iterator::checkResult(int position, mpz_t result){
    std::cout << "Checking result on position " << position << std::endl;

    if(position == xySize) {///Sanity check - the check result should always be called at position == xySize
        ///Should be removed after testing to improve performance. Position should also be
        ///replaced with a const reference to xySize

        ///Since the number was already reduced in size, no further modifications are required to the result
        if(mpz_divisible_p(result, x))
        {
            std::cout << "\nResult found X";
            mpz_divexact(temp, result, x);
            mpz_mul_2exp(temp, temp, xySize * position);
            mpz_add(temp, temp, y);

            if(addResult(x, temp)){
                xySize = nSize = 0;
                return;
            }

        }
        if(mpz_divisible_p(result, y))
        {
            std::cout << "\nResult found Y";
            mpz_divexact(temp, result, y);
            mpz_mul_2exp(temp, temp, position * base2exp);
            mpz_add(temp, temp, x);
            if(addResult(temp, y)){
                xySize = nSize = 0;
                return;
            }
        }
    }else{
        std::cout << "Invalid call to checkResult. Position is " << position <<". Should be " << xySize << "\n";
        return;
    }


}

///Step functions
void VB_Iterator::setFactor(uint8_t segment, uint8_t position, mpz_t factor)
{
    factor->_mp_d[position / base2exp] |= (segment << position % base2exp);
}

void VB_Iterator::getSubResult(uint8_t xSegment, uint8_t ySegment, mpz_t result, mpz_t previousResult)
{
    /// result = (((previousResult - (xSegment * y + ySegment * x)) >> p) - (xSegment * ySegment)) >> p;
    ///Build the value subtracted from previous result
    mpz_addmul_ui(temp, x, ySegment);
    mpz_addmul_ui(temp, y, xSegment);
    ///Since we know that we'll get a difference of 0 on the desired position, we can just right shift the results of
    ///(xSegment * y + ySegment * x) and previousResult, subtracting only the carry values and xSegment * ySegment
    mpz_div_2exp(temp, temp, base2exp);
    mpz_add_ui(temp, temp, (xSegment * ySegment));

    ///Initialize the current result as the right shifted previousResult
    mpz_div_2exp(result, previousResult, base2exp);
    mpz_sub(result, result, temp);

//    mpn_zero (temp->_mp_d, temp->_mp_size);
    mpz_set_ui(temp, 0);
}

void VB_Iterator::resetNode(int position){
    ///In order to reuse the available bit masks, we assume that any bits larger than the current position are 0.
    ///We negate our bitmask, and assign the new limb of x as the result of the operation X[position] & !mask[position]
    ///This gives us a situation of 0011 & !(0010) = 0011 & 1101 = 0001 - only the bits < than the mask are kept
    x->_mp_d[position/blocksPerLimb] &= !(maskList[position]);
    y->_mp_d[position/blocksPerLimb] &= !(maskList[position]);
}

int VB_Iterator::startIteration(int strategy = 0)
{
    if(variablesInitialized)
    {
        ///Implement strategic iterators
        initialIterator(currentPosition);
    }else{
        std::cout << "Container variables have not been initialized propperly";
    }
    return 0;
}

void VB_Iterator::testTables()
{
    std::cout << "Test data structures: (M)od Table, Mask (L)ist: \n";
    std::cout << "Test (C)yclic Iterator: 8 bits \n";
    uint target = 0;
    uint factor = 0;
    uint8_t choice = 0;
    uint biggestNumber = 0;
    while(choice != 'Q')
    {
        std::cin >> choice;
        switch (choice) {
            case 'M':
                std::cout << "Mod table testing.\n";
                std::cout << "Choose target: ";
                std::cin >> target;
                std::cout << "Choose factor: ";
                std::cin >> factor;
                std::cout << "Return: " << modTable[target][factor][0] << std::endl;
                std::cout << factor << " * " << (int)modTable[target][factor][0] << " = " << factor * modTable[target][factor][0] << std::endl;
                continue;
            case 'L':
                std::cout << "Mask list testing.";
                std::cout << "Choose position: ";
                std::cin >> target;
                std::cout << "Mask: " << maskList[target];
                continue;
            case 'C':
                for(uint8_t counter = 1; counter < base; ++counter)
                {
                    if(counter == 0){
                        std::cout << "Biggest value: " << biggestNumber <<std::endl;
                        break;
                    }
                    biggestNumber = counter;
                }
                continue;
            default:
                std::cout << "Unknown selection \n";
        }
    }
}