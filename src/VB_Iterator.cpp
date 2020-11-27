//
// Created by blackberry on 30.10.2020.
//

bool trigger1 = false;
bool trigger2 = false;
bool trigger3 = false;



#include "../include/VB_Iterator.h"

///Utility Functions
VB_Iterator::VB_Iterator(const char numberString[1024], uint startingPosition, uint wanted2exp,
                         uint ***generatedModTable, mpz_t *generatedMaskList,
                         bool generateTables)
{
    if(mpz_init_set_str(targetNumber, numberString, 10) == 0)
    {
        gmp_printf("Target Number: %Zd\n", targetNumber);
        if(wanted2exp <= MAX_ALLOWED_2EXP)
        {
            if(64 % wanted2exp)
            {
                std::cout << "\nChosen exponent must be a divisor of 64" << std::endl;
                return;
            }else{
                base2exp = wanted2exp;
                base = pow(2, base2exp);
                baseMask = base - 1;
                std::cout << "Selected Base: " << base << "\n";
                mpz_init_set_ui(temp, 0);
                nSize = mpz_sizeinbase(targetNumber, base);
                std::cout << "Number size: " << nSize << std::endl;
                if(nSize > 1)
                {
                    xySize = (nSize % 2) ? (nSize / 2 + 1) : (nSize / 2); ///Do not modify!! Find the bug somewhere else!
                    std::cout << "xySize: " << xySize << std::endl;
                    if(generateTables){
                        generateStaticStructures(generatedModTable, generatedMaskList);
                    }else{
                        bindStaticStructures(generatedModTable, generatedMaskList);
                    }
                    for(uint i = 0; i <= xySize; ++i){
                        branches[i] = 0;
                        xSegments[i] = ySegments[i] = numberSegments[i] = 0;
                        mpz_init(results[i]);
                    }
                    mpz_init_set_ui(x, 0);
                    mpz_init_set_ui(y, 0);
                    mpz_init(resultContainer);
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
    modTableDestination = new uint **[base]();
    for (uint i = 0; i < base; ++i) {
        modTableDestination[i] = new uint *[base]();
        for (uint j = 0; j < base; ++j) {
            modTableDestination[i][j] = new uint [2]();
        }
    }
    for (uint i = 0; i < base; ++i) {
        for (uint j = 0; j < base; ++j)
        {
            product = i * j;
            carry = product / base;
            residue = product % base;
            modTableDestination[residue][i][0] = j;
            modTableDestination[residue][i][1] = carry;
        }
    }
    return modTableDestination;
}

mpz_t *VB_Iterator::generateMaskList(mpz_t *maskListDestination) const
{
    maskListDestination = new mpz_t[ALU_SIZE / base2exp]();
    mpz_init_set_ui(maskListDestination[0], 0);
    mpz_init_set_ui(maskListDestination[1], base - 1);
    for(int i = 2; i < nSize; ++i)
    {
        mpz_init(maskListDestination[i]);
        mpz_mul_2exp(maskListDestination[i], maskListDestination[1], base2exp * (i - 1));
        mpz_add(maskListDestination[i], maskListDestination[i], maskListDestination[i - 1]);
    }
    return maskListDestination;
}

void VB_Iterator::generateStaticStructures(uint ***modTableDestination, mpz_t *maskListDestination)
{
    modTable = generateModTable(modTableDestination);
    maskList = generateMaskList(maskListDestination);
}

bool VB_Iterator::bindStaticStructures(uint ***modTableSource, mpz_t *maskListSource)
{
    maskList = maskListSource;
    modTable = modTableSource;
    return true;
}

bool VB_Iterator::addResult(mpz_t xSolution, mpz_t ySolution){
    gmp_printf("%Zd * %Zd \n", xSolution, ySolution);
    return true;
}

///Iterator functions

void VB_Iterator::initialIterator(int position){
    if(position == 0)
    {
        for(branches[position] = 1; branches[position] < base; ++branches[position])
        {
            if(branches[position] % 2 != 0)
            {
                numberSegments[position] = targetNumber -> _mp_d[0] & baseMask;
                if(modTable[numberSegments[position]][branches[position]][0] < branches[position])
                {
                    continue;
                }
                X0 = xSegments[position] = branches[position];
                Y0 = ySegments[position] = modTable[numberSegments[position]][X0][0];
                setFactor(xSegments[position], position, x);
                setFactor(ySegments[position], position, y);
                mpz_sub_ui(results[0], targetNumber, X0 * Y0);
                mpz_div_2exp(results[0], results[0], base2exp);
                if(X0 == Y0)
                {
                    widthSubIterator(position + 1);
                } else {
                    depthSubIterator(position + 1);
                }
                resetNode(position);
            }else{
                continue;
            }
        }
    }else{
        std::cout << "Wrong arguments provided to initial iterator. Position should be 0\n";
        return;
    }
}

void VB_Iterator::depthSubIterator(int position){
    if(position < xySize) {
        numberSegments[position] = results[position - 1]->_mp_d[0] & baseMask;
        for (branches[position] = 0; branches[position] < base; ++branches[position]) {
            xSegments[position] = modTable[branches[position]][Y0][0];
            ySegments[position] = modTable[(numberSegments[position] - branches[position]) & baseMask][X0][0];
            getSubResult(xSegments[position], ySegments[position], results[position], results[position - 1], position);
            setFactor(xSegments[position], position, x);
            setFactor(ySegments[position], position, y);
            depthSubIterator(position + 1);
            resetNode(position);
        }
    }else if(position == xySize){
        checkResult(position, results[position - 1]);
    }
}


void VB_Iterator::widthSubIterator(int position){
    if(position < xySize) {
        numberSegments[position] = results[position - 1] -> _mp_d[0] & baseMask;
        for (branches[position] = 0; branches[position] < base; ++branches[position]) {
            if(modTable[numberSegments[position]][branches[position]][0] < branches[position]){
                continue;
            }
            xSegments[position] = modTable[branches[position]][Y0][0];
            ySegments[position] = modTable[(numberSegments[position] - branches[position]) & baseMask][X0][0];
            getSubResult(xSegments[position],ySegments[position], results[position], results[position - 1], position);
            setFactor(xSegments[position], position, x);
            setFactor(ySegments[position], position, y);
            if(xSegments[position] == ySegments[position])
            {
                widthSubIterator(position + 1);
            } else {
                depthSubIterator(position + 1);
            }
            resetNode(position);
        }
    }else if(position == xySize){
        checkResult(position, results[position - 1]);
    }
}

void VB_Iterator::checkResult(int position, mpz_t result)
{
    switch(mpz_sgn(result)) {
        case 0:
                addResult(x, y);
            return;
        case 1:
            if( mpz_divisible_p(result, x) )
            {
                mpz_divexact(temp, result, x);
                mpz_mul_2exp(temp, temp, position * base2exp);
                mpz_add(temp, temp, y);
                addResult(x, temp);
                mpz_set_ui(resultContainer, 0);
                mpz_set_ui(temp, 0);
                return;
            }else
            if( mpz_divisible_p(result, y) )
            {
                mpz_divexact(temp, result, y);
                mpz_mul_2exp(temp, temp, position * base2exp);
                mpz_add(temp, temp, x);
                addResult(temp, y);
                mpz_set_ui(resultContainer, 0);
                mpz_set_ui(temp, 0);
                return;
            }
            return;
        case -1:
            return;
    }
}

///Step functions
void VB_Iterator::setFactor(uint segment, int position, mpz_t factor){
    mpz_set_ui(temp, segment);
    mpz_mul_2exp(temp, temp, (position * base2exp));
    mpz_add(factor, factor, temp);
    mpz_set_ui(temp, 0);
}

void VB_Iterator::getSubResult(uint xSegment, uint ySegment, mpz_t result, mpz_t previousResult, int position){
    /// result = (((previousResult - (xSegment * y + ySegment * x)) >> p) - (xSegment * ySegment)) >> p
    mpz_set_ui(temp, (xSegment * ySegment));
    mpz_mul_2exp(temp, temp, base2exp * position);
    mpz_addmul_ui(temp, x, ySegment);
    mpz_addmul_ui(temp, y, xSegment);
    mpz_sub(result, previousResult, temp);
    mpz_div_2exp(result, result, base2exp);
    mpz_set_ui(temp, 0);
}

void VB_Iterator::resetNode(int position){
    mpz_and(temp, x, maskList[position]);
    mpz_set(x, temp);
    mpz_and(temp, y, maskList[position]);
    mpz_set(y, temp);
    mpz_set_ui(temp, 0);
    mpz_set_ui(results[position], 0);
}

int VB_Iterator::startIteration(int strategy = 0)
{
    if(variablesInitialized)
    {
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        initialIterator(currentPosition);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << cpu_time_used << "seconds for " << mpz_sizeinbase(targetNumber, 2) << "bits " << std::endl;
    }else{
        std::cout << "Container variables have not been initialized properly";
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
                        std::cout << "Biggest value: " << biggestNumber << std::endl;
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

int VB_Iterator::depthIteration(int strategy)
{
    if(variablesInitialized)
    {
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        initialIterator(currentPosition);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << cpu_time_used << "seconds for " << mpz_sizeinbase(targetNumber, 2) << "bits. Depth Iterator" << std::endl;
    }else{
        std::cout << "Container variables have not been initialized properly";
    }
    return 0;
}