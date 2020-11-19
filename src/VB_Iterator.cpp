//
// Created by blackberry on 30.10.2020.
//

#include "../include/VB_Iterator.h"

bool DEBUG_OUTPUT = false;
bool DEPTH_ITERATOR_DEBUG = false;
bool INIT_ITERATOR_DEBUG = false;
bool RESULT_DEBUG = false;
bool CHECK_DEBUG = false;
mpz_t debugContainer;

///Utility Functions
VB_Iterator::VB_Iterator(const char numberString[1024], uint8_t startingPosition, uint wanted2exp,
                         uint8_t ***generatedModTable, mpz_t *generatedMaskList,
                         bool generateTables)
{
    ///Prepare all the containers for the working stream
    mpz_init(debugContainer);
    if(mpz_init_set_str(targetNumber, numberString, 10) == 0) ///if the string is a valid number in base 10
    {
        gmp_printf("\nTarget Number: %Zd", targetNumber);
        ///Implement test, if number is smaller than base^2, it can be found inside the mod table
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
uint8_t ***VB_Iterator::generateModTable(uint8_t ***modTableDestination) const
{
    uint product;
    uint residue;
    uint carry;

    if(true){
        std::cout << "Allocating mod table containers for base " << base <<  std::endl;
    }

    modTableDestination = new uint8_t **[base]();
    for (uint i = 0; i < base; ++i) {
        modTableDestination[i] = new uint8_t *[base]();
        for (uint j = 0; j < base; ++j) {
            modTableDestination[i][j] = new uint8_t [2]();
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

mpz_t *VB_Iterator::generateMaskList(mpz_t *maskListDestination) const
{
    if(true) {
        std::cout << "\n Generating " << ALU_SIZE / base2exp << "masks" << std::endl;
    }

    ///temp is not usable here, since it is of type mpz_srcptr not mpz_ptr
    maskListDestination = new mpz_t[ALU_SIZE / base2exp]();
    mpz_init_set_ui(maskListDestination[0], 0);
    mpz_init_set_ui(maskListDestination[1], base - 1);
    for(int i = 2; i < nSize; ++i)
    {
        mpz_init(maskListDestination[i]);
        mpz_mul_2exp(maskListDestination[i], maskListDestination[1], base2exp * (i - 1));
        mpz_add(maskListDestination[i], maskListDestination[i], maskListDestination[i - 1]);
        ///Since masks are only used in resetting X and Y, we need all the bits up to a position for an and operation
        ///All reset masks need to be position - 1 * mask size
    }
    if(DEBUG_OUTPUT) {
        std::cout << "Masks generated successfully" << std::endl;
    }
    return maskListDestination;
}

bool VB_Iterator::checkModTable(uint8_t ***modTableSource)
{
    if(modTableSource != nullptr)
    {
        return false;
    }
    return true;
}

bool VB_Iterator::checkMaskList(const mpz_t maskListSource[MAX_N_SIZE])
{
    if(maskListSource != nullptr)
    {
        return false;
    }
    return true;
}

void VB_Iterator::generateStaticStructures(uint8_t ***modTableDestination, mpz_t *maskListDestination)
{
    modTable = generateModTable(modTableDestination);
    maskList = generateMaskList(maskListDestination);
    if(DEBUG_OUTPUT){
        std::cout << "\n Static Structures generated" << std::endl;
    }
}

bool VB_Iterator::bindStaticStructures(uint8_t ***modTableSource, mpz_t *maskListSource)
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
    mpz_set_ui(temp, 0);
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

    for(branches[position] = 1; branches[position] < base; ++branches[position]) ///tree branching factor is defined by the base
    ///Since divisors of 2 are taken out and thus defined as 0 in our table

    {
        if(branches[position]%2)
        {
//            if(modTable[numberSegments[position]][branches[position]][0] < branches[position])
//            {
//            ///if the number pointed to by the table is smaller than the current number, we know it was already checked
//            continue;
//            ///we continue the iteration for the cases where X == Y
//            }
            xSegments[position] = X0 = branches[position];
            ySegments[position] = Y0 = modTable[numberSegments[position]][X0][0];

            mpz_set_ui(x, X0);
            mpz_set_ui(y, Y0);
            ///Since the value of x*y is within ALU range, we can do a direct multiplication
            mpz_sub_ui(results[0], targetNumber, X0 * Y0);
            ///Initialize the current result as the right shifted previousResult
            mpz_div_2exp(results[0], results[0], base2exp);
            if(INIT_ITERATOR_DEBUG){
                std::cout << "\nPosition: " << position << ". xSegment " << (uint)xSegments[position] << ". ySegment " << (uint)ySegments[position] << "\n";
                gmp_printf("Running Result: %Zd\n\n", results[position]);
                if(branches[position] == 13UL)
                {
                    DEPTH_ITERATOR_DEBUG = true;
                    RESULT_DEBUG = true;
                    CHECK_DEBUG = true;
                }
            }
            if(X0 == Y0)
            {

                ///do an initial check to see if the number is a perfect square - GMP implementation is faster
                if(DEBUG_OUTPUT){
                    std::cout << "\nInitial Iterator successfully called WidthIterator" << std::endl;
                }
                widthSubIterator(position + 1);
            } else { ///If x[p] != y[p], call depth iterator
                if(DEBUG_OUTPUT){
                    std::cout << "\nInitial Iterator successfully called DepthIterator" << std::endl;
                    gmp_printf("X: %Zd \n", x);
                    gmp_printf("Y: %Zd \n", y);
                }
                depthSubIterator(position + 1);
                if(DEPTH_ITERATOR_DEBUG){
                    DEPTH_ITERATOR_DEBUG = false;
                    INIT_ITERATOR_DEBUG = false;
                    RESULT_DEBUG = false;
                    CHECK_DEBUG = false;
                }
            }
//            resetNode(position); ///Possible useless, since values from deeper nodes always come cleaned up

        }else{
            if(INIT_ITERATOR_DEBUG)std::cout << "Excluded divisible factor" << branches[position] << std::endl;
            continue;
        }

    }
}

void VB_Iterator::depthSubIterator(int position){
    if(DEPTH_ITERATOR_DEBUG){
        std::cout << "DepthIterator Called on position " << position << "\n";
    }
    if(position < xySize) {
        numberSegments[position] = results[position - 1]->_mp_d[0] & 0b11111111; ///to avoid using sum table, segments must be targeted on the previous result
        if(DEPTH_ITERATOR_DEBUG){
            std::cout << "Iterating target segment " << (uint)numberSegments[position] << "\n";
            gmp_printf("X: %Zd\n Y: %Zd\n", x, y);
        }
        for (branches[position] = 0; branches[position] < base; ++branches[position]) {///Since X and Y are not identical anymore, we have to go through all the possible branches.
            if(DEPTH_ITERATOR_DEBUG){
                std::cout << "Branch " << branches[position] << "\n";
            }
        ///Critical implementation: to avoid using the sum table, the underlying 8 bit unsigned container will be used to increment X and decrement Y on every step,
        /// using the max value to loop around in a cyclic manner
            xSegments[position] = modTable[branches[position]][Y0][0];
            ySegments[position] = modTable[(uint8_t)(numberSegments[position] - branches[position])][X0][0];
            getSubResult(xSegments[position],ySegments[position],
                         results[position], results[position - 1]);
            setFactor(xSegments[position], position, x);
            setFactor(ySegments[position], position, y);
            if(DEPTH_ITERATOR_DEBUG){
                std::cout << "xSegment " << (uint)xSegments[position] << ". ySegment " << (uint)ySegments[position] << ".\n";
                gmp_printf("Running result: %Zd\n\n", results[position]);
            }
            depthSubIterator(position + 1);
        }
        if(DEPTH_ITERATOR_DEBUG)std::cout << "Calling Depth reset" << std::endl;
        resetNode(position);
    }else if(position == xySize){
        if(DEPTH_ITERATOR_DEBUG) {gmp_printf("Checking result\n\n");}
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
    if(DEBUG_OUTPUT){
        std::cout << "Checking result on position " << position << std::endl;
    }

    if(mpz_sgn(result) >= 0) {

        if(mpz_divisible_p(result, x))
        {
            mpz_divexact(temp, result, x);
            if(CHECK_DEBUG){
                std::cout << "\nResult found, case R divisible by X\n";
                gmp_printf("Initial X: %Zd \n", x);
                gmp_printf("Initial Y: %Zd \n", y);
                gmp_printf("Initial R: %Zd \n", result);
                gmp_printf("R / X: %Zd \n", temp);
            }
            mpz_mul_2exp(temp, temp, position * base2exp);
            if(CHECK_DEBUG){
                gmp_printf("(R / X) << p: %Zd \n", temp);
            }
            mpz_ior(temp, temp, y);
            if(addResult(x, temp)){
                mpz_set_ui(temp, 0);
//                xySize = nSize = 0;
                return;
            }
            mpz_set_ui(temp, 0);
        }
        if(mpz_divisible_p(result, y))
        {
            mpz_divexact(temp, result, y);
            if(CHECK_DEBUG){
                std::cout << "\nResult found, case R divisible by Y\n";
                gmp_printf("Initial X: %Zd \n", x);
                gmp_printf("Initial Y: %Zd \n", y);
                gmp_printf("Initial R: %Zd \n", result);
                gmp_printf("R / Y: %Zd \n", temp);
            }
            mpz_mul_2exp(temp, temp, position * base2exp);
            if(CHECK_DEBUG){
                gmp_printf("(R / Y) << p: %Zd \n", temp);
            }
            mpz_ior(temp, temp, x);
            if(addResult(temp, y)){
                mpz_set_ui(temp, 0);
//                xySize = nSize = 0;
                return;
            }
            mpz_set_ui(temp, 0);
        }
    }else {
        if(DEBUG_OUTPUT)std::cout << "Result Overflow\n";
        return;
    }
//    if(DEBUG_OUTPUT)std::cout << "CheckResult reset called\n";
//    resetNode(position - 1);
    ///This reset should not be necessary, as the number should be reset by the iterator calling the check function
}

///Step functions
void VB_Iterator::setFactor(uint8_t segment, uint8_t position, mpz_t factor)
{
    /////X and Y are not assigned properly due to incorrect position calculation
    if(DEBUG_OUTPUT)gmp_printf("Factor %Zd changed to ", factor);
    mpz_set_ui(temp, segment);
    mpz_mul_2exp(temp, temp, position * base2exp);
    mpz_add(factor, factor, temp);
    mpz_set_ui(temp, 0);
    if(DEBUG_OUTPUT)gmp_printf("%Zd \n", factor);

}

void VB_Iterator::getSubResult(uint8_t xSegment, uint8_t ySegment, mpz_t result, mpz_t previousResult)
{
    /// result = (((previousResult - (xSegment * y + ySegment * x)) >> p) - (xSegment * ySegment)) >> p;
    ///Build the value subtracted from previous result
    if(RESULT_DEBUG)
    {
        std::cout << "Entering subResult. xSegment: " << xSegment << ", ySegment: "<< ySegment << "\n";
        gmp_printf("Initial X: %Zd\nInitial Y: %Zd\nPrevious Result: %Zd\nEntering Temp: %Zd\n", x, y, previousResult, temp);
    }
    mpz_addmul_ui(temp, x, ySegment);
    mpz_addmul_ui(temp, y, xSegment);
    if(RESULT_DEBUG)
    {
        mpz_mul_ui(debugContainer, x, ySegment);
        gmp_printf("X * ySegment: %Zd\n", debugContainer);
        mpz_mul_ui(debugContainer, y, xSegment);
        gmp_printf("Y * xSegment: %Zd\n", debugContainer);
        gmp_printf("(X*ySegment) + (Y*xSegment) = %Zd", temp);
    }

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
//    x->_mp_d[position/blocksPerLimb] &= !(maskList[position % blocksPerLimb]);
//    y->_mp_d[position/blocksPerLimb] &= !(maskList[position % blocksPerLimb]);


    if(DEBUG_OUTPUT)gmp_printf("Number X: %Zd reset to ",x);
    mpz_and(x, x, maskList[position]);
    if(DEBUG_OUTPUT)gmp_printf("%Zd\n", x);

    if(DEBUG_OUTPUT)gmp_printf("Number Y: %Zd reset to ",y);
    mpz_and(y, y, maskList[position]);
    if(DEBUG_OUTPUT)gmp_printf("%Zd\n", y);
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
    std::cout << "Test data structures: (M)od Table, Mask (L)ist, Number (S)egments: \n";
    std::cout << "Test (C)yclic Iterator: 8 bits \n";
    uint target = 0;
    uint factor = 0;
    uint8_t choice = 0;
    uint biggestNumber = 0;
    char *charBuffer;
    while(choice != 'Q')
    {
        std::cin >> choice;
        switch (choice) {
            case 'S':
                std::cout << "Number: "; gmp_printf("%Zd\n", targetNumber);
                std::cout << "Segments: " << nSize << "\n";
                std::cout << "Select segment:";
                std::cin >> target;
                std::cout << "\nTarget segment:" << (uint)numberSegments[target] << std::endl;
                continue;
            case 'M':
                std::cout << "Mod table testing.\n";
                std::cout << "Choose target: ";
                std::cin >> target;
                std::cout << "Choose factor: ";
                std::cin >> factor;
                std::cout << "Return: " << (int)modTable[target][factor][0] << std::endl;
                std::cout << factor << " * " << (int)modTable[target][factor][0] << " = " << factor * modTable[target][factor][0] << std::endl;
                continue;
            case 'L':
                std::cout << "Mask list testing.";
                std::cout << "Choose position: ";
                std::cin >> target;
                mpz_get_str(charBuffer, 2, maskList[target]);
                std::cout << "Mask: " << charBuffer << std::endl;
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