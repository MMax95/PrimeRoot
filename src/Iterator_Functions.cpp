//
// Created by blackberry on 27.07.2020.
//

#include "../include/Iterator_Functions.h"

void   widthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            getNodeTypeLL(number, results[position], position + 1, branches);
            widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                branches[position + 1] = branches[position + 1] >> 2;
                widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateLL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
    }else if(position == xy_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            getNodeTypeLR(number, results[position], position + 1, branches);
            widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                branches[position + 1] = branches[position + 1] >> 2;
                widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateLR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            getNodeTypeRL(number, results[position], position + 1, branches);
            widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                branches[position + 1] = branches[position + 1] >> 2;
                widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateRL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            getNodeTypeRR(number, results[position], position + 1, branches);
            widthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                branches[position + 1] = branches[position + 1] >> 2;
                widthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateRR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);
    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}


void   depthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeLL(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        if(branches[position + 1] & 0b10000)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    { ///Important notice! position must be smaller or EQUAL to number size
    ///This is important, since a prime factor can be the size 2, thus creating a min size R of 4. If the position based
    ///iterator stopper will be kept, the <= check is mandatory to prevent extra work, while allowing the discovery of the
    ///small sized primes
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   depthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeLR(number, results[position], position + 1, branches);
        depthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;
            depthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);

    } else if (position <= number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   depthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeRL(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        if(branches[position + 1] & 0b10000)
        {
            branches[position + 1] = branches[position + 1] >> 2;
            depthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   depthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeTypeRR(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        if(branches[position + 1] & 0b10000)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}

void checkResult(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
                 unsigned int &xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE],
                 unsigned int &number_size, Runner &currentRunner) {

    if (mpz_tstbit(results[position - 1], number_size)) {
        return;
    }
    mpz_sub(results[position], number, results[position - 1]);
    switch (mpz_sgn(results[position])) {
        case 1:
            mpz_div_2exp(results[position], results[position], position);
            if(mpz_divisible_p(results[position], x)){
                mpz_divexact(diff, results[position], x);
                mpz_mul_2exp(diff, diff, position);
                mpz_add(diff, diff, y);
                addResult(x, diff, diff, number, xy_size, number_size, currentRunner);
                if (xy_size == 0) { return; }
            }
            if(mpz_divisible_p(results[position], y)){
                mpz_divexact(diff, results[position], y);
                mpz_mul_2exp(diff, diff, position);
                mpz_add(diff, x, diff);
                addResult(diff, y, diff, number, xy_size, number_size, currentRunner);
            }
            mpz_set_ui(diff, 1);
            return;
        case 0:
            addResult(x, y, diff, number, xy_size, number_size, currentRunner);
            return;
    }
}

///Memory Functions///

void generateTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y, mpz_t& diff, unsigned int xy_size, unsigned int number_size)
{
    for (int i = 0; i < MAX_XY_SIZE; ++i)                                                              /// generates xy_size nodes
    {
        mpz_init_set_d(results[i], 1);
        mpz_realloc2(results[i], ((i+1) * 2));
    }
    for (int j = 0; j < MAX_N_SIZE; ++j)                                                              /// initializes the branch type list with 0s
    {
        branches[j] = 0;
    }
    mpz_init_set_d(x, 1);                                                                              /// initializes X variable with 1
    mpz_init_set_d(y, 1);
    mpz_init_set_d(diff, 1);
    mpz_init_set_d(results[xy_size], 1);
    mpz_realloc(x, number_size);                                                                 /// allocates space for n bits
    mpz_realloc(y, number_size);                                                                 /// allocates space for n bits
    mpz_realloc(diff, number_size);                                                                 /// allocates space for n
    mpz_realloc(results[xy_size], number_size);
}

void resetTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y, mpz_t& diff, unsigned int xy_size)
{
    for (int i = 0; i < MAX_XY_SIZE; ++i)                                                              /// generates xy_size nodes
    {
        mpz_set_d(results[i], 1);
    }
    for (int j = 0; j < MAX_N_SIZE; ++j)                                                              /// initializes the branch type list with 0s
    {
        branches[j] = 0;
    }
    branches[0] = 0b11;
    mpz_set_d(x, 1);                                                                              /// initializes X variable with 1
    mpz_set_d(y, 1);
    mpz_set_d(diff, 1);
    mpz_set_d(results[xy_size], 1);
}

void   widthIterateAllocator (unsigned int strategy, Runner *threads, unsigned int thread_ID,
                              unsigned int runnerNumber, unsigned int position, Result &newNumber)
{
    mpz_init_set(threads[thread_ID].number, newNumber.number);
    threads[thread_ID].number_size = mpn_sizeinbase(threads[0].number->_mp_d,
                                                    threads[0].number->_mp_size, 2);
    threads[thread_ID].xy_size     = threads[thread_ID].number_size / 2 + 1;

    if(position == 1)
    {
        resetTree(threads[thread_ID].results, threads[thread_ID].branches,
                  threads[thread_ID].x, threads[thread_ID].y,
                  threads[thread_ID].diff, threads[thread_ID].xy_size);
    }
    mpz_t &x = threads[thread_ID].x;
    mpz_t &y = threads[thread_ID].y;
    mpz_t &diff = threads[thread_ID].diff;
    mpz_t &number = threads[thread_ID].number;
    mpz_t *results = threads[thread_ID].results;
    unsigned int &xy_size = threads[thread_ID].xy_size;
    unsigned int &number_size = threads[thread_ID].number_size;
    unsigned int *branches = threads[thread_ID].branches;
    threads[thread_ID].targetNumber = &newNumber;
    threads[thread_ID].strategy = strategy;


    void (*widthStrategicIterator)(mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*, unsigned int&,
                                   const unsigned int, unsigned int*, unsigned int&, Runner&);
    void (*depthStrategicIterator)(mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*, unsigned int&,
                                   const unsigned int, unsigned int*, unsigned int&, Runner&);
    void (*getStrategicNodeType)  (const mpz_t&, const mpz_t&, unsigned int, unsigned int*);

    switch (strategy){
        case LL:
            widthStrategicIterator = &widthIterateLL;
            depthStrategicIterator = &depthIterateLL;
            getStrategicNodeType   = &getNodeTypeLL;
            break;
        case LR:
            widthStrategicIterator = &widthIterateLR;
            depthStrategicIterator = &depthIterateLR;
            getStrategicNodeType   = &getNodeTypeLR;
            break;
        case RL:
            widthStrategicIterator = &widthIterateRL;
            depthStrategicIterator = &depthIterateRL;
            getStrategicNodeType   = &getNodeTypeRL;
            break;
        case RR:
            widthStrategicIterator = &widthIterateRR;
            depthStrategicIterator = &depthIterateRR;
            getStrategicNodeType   = &getNodeTypeRR;
            break;
        case SH:
            widthStrategicIterator = &squareRoot;
            depthStrategicIterator = &squareRoot;
            getStrategicNodeType   = &getNodeTypeLL;
            addResult(x, y, diff, number, xy_size, number_size, threads[thread_ID]);
            break;
        default:
            std::cout << "Unknown strategy selected" << std::endl;
            return;
    }

    getStrategicNodeType(number, results[position - 1], position, branches);

    if ((branches[position] == equalLeft) || (branches[position] == equalRight))
    {
        widthStrategicIterator(x, y, diff, number, results, xy_size, position,
                               branches, number_size, threads[thread_ID]);
        if(branches[position] & 0b10000)
        {
            branches[position] = branches[position] >> 2;
            widthStrategicIterator(x, y, diff, number, results, xy_size, position,
                                   branches, number_size, threads[thread_ID]);
        }
        resetXY(x, y, position);
    } else {
        branches[position] = branches[position] >> 2;
        depthStrategicIterator (x, y, diff, number, results, xy_size, position,
                                branches, number_size, threads[thread_ID]);
    }
    threads[thread_ID].targetNumber = nullptr;
    for(Result &factor: unique_factors)
    {
        if(factor.left == nullptr)
        {
            widthIterateAllocator(strategy, threads, thread_ID, runnerNumber, position, factor);
        }
    }

}
void findWork (Runner *threads, unsigned int runnerNumber, unsigned int thread_ID)
{
    Result *lastFactor;
    bool identical;
    for(Result &factor: unique_factors)
    {
        if(factor.left == nullptr)
        {
            lastFactor = &factor;
        }
    }
    for(int i = 0; i < runnerNumber; ++i)
    {
        if(threads[i].targetNumber == lastFactor)
        {
            for(int j = 0; j < MAX_XY_SIZE; ++j)
            {
                if(threads[i].branches[j] & 0b10000)
                {
                    threads[i].branches[j] &= 0b1111;
                    identical = cloneThread(threads[j], threads[thread_ID], i);
                    i = runnerNumber;
                    break;
                }
            }
        }
    }
    if(identical)
    {

    }
}

bool    cloneThread(Runner sourceThread, Runner destinationThread, int position)
{
    sourceThread.branches[position] &= 0b1111;
    bool identical = true;
    mpz_set(destinationThread.number, sourceThread.number);
    destinationThread.targetNumber = sourceThread.targetNumber;
    destinationThread.strategy = !sourceThread.strategy;

    for(int i = 0; i < position; ++i)
    {
        destinationThread.branches[i] = sourceThread.branches[i];
        setXY(destinationThread.x, destinationThread.y, i, destinationThread.branches[i]);
        if((destinationThread.branches[i] & 0b11) == 0b10 || (destinationThread.branches[i] & 0b11) == 0b01)
        {
            identical = false;
        }
    }
    destinationThread.branches[position] = sourceThread.branches[position];
    if((destinationThread.branches[position] & 0b11) == 0b10 || (destinationThread.branches[position] & 0b11) == 0b01)
    {
        identical = false;
    }
    destinationThread.branches[position] = destinationThread.branches[position] >> 2;
    makeResult(destinationThread.results[position], sourceThread.results[position - 1], position, destinationThread.branches[position], destinationThread.x, destinationThread.y, destinationThread.diff);
    return identical;
}

void    addResult  (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, unsigned int &xy_size,
                    unsigned int &number_size, Runner &currentRunner)
{
    using namespace boost::container;
    int xComp = mpz_cmp_ui(x, 1);
    int yComp = mpz_cmp_ui(y, 1);
    if(xComp && yComp)
    {
        unsigned int uniqueXY = 0b11;
        for(Result &factor : unique_factors)
        {
            if(mpz_cmp(factor.number, x) == 0)
            {
                currentRunner.targetNumber->left = &(factor);
                uniqueXY -= 0b01;
            }
            if(mpz_cmp(factor.number, y) == 0)
            {
                currentRunner.targetNumber->right = &factor;
                uniqueXY -= 0b10;
            }
        }

        switch (uniqueXY)
        {
            case 0b00:
                break;
            case 0b01:
                unique_factors.push_back(Result(x));
                currentRunner.targetNumber->left = &unique_factors.back();
                break;
            case 0b10:
                unique_factors.push_back(Result(y));
                currentRunner.targetNumber->right = &unique_factors.back();
                break;
            case 0b11:
                unique_factors.push_back(Result(x));
                currentRunner.targetNumber->left = &unique_factors.back();
                unique_factors.push_back(Result(y));
                currentRunner.targetNumber->right = &unique_factors.back();
                break;
        }
        number_size = xy_size = 0;

    }else if((xComp == 0) || (yComp == 0)){
        if (currentRunner.targetNumber->left == nullptr &&
            currentRunner.targetNumber->right == nullptr)
        {
            currentRunner.targetNumber->left = &unique_factors.front();
            currentRunner.targetNumber->right = currentRunner.targetNumber;
        }
    }
}

void squareRoot (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                 const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            getNodeTypeLL(number, results[position], position + 1, branches);
            squareRoot(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                branches[position + 1] = branches[position + 1] >> 2;
                squareRoot(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        }
    }else if(position <= number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}

