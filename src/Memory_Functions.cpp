//
// Created by blackberry on 27.07.2020.
//

#include "../include/Memory_Functions.h"

void generateNode(mpz_t& result, unsigned int position)

{
    mpz_init_set_d(result, 1);
    mpz_realloc2(result, (position * 2 + 1));
}

void generateTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y, mpz_t& diff, unsigned int xy_size, unsigned int number_size)
{
    for (int i = 0; i < xy_size + 1; ++i)                                                              /// generates xy_size nodes
    {
        generateNode(results[i], i);
    }
    for (int j = 0; j < number_size; ++j)                                                              /// initializes the branch type list with 0s
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

    std::cout << "\nTree generated for depth " << xy_size << "\n";
}
bool cloneThread        (Runner sourceThread, Runner destinationThread, unsigned int position)
{
    bool identical = true;
    mpz_set_ui(destinationThread.x, 1);
    mpz_set_ui(destinationThread.y, 1);
    for(int i = 0; i < position; ++i)
    {
        destinationThread.branches[i] = sourceThread.branches[i];
        setXY(destinationThread.x, destinationThread.y, i, destinationThread.branches[i]);
        if((destinationThread.branches[i] & 0b11) == 0b01 ||
           (destinationThread.branches[i] & 0b11) == 0b10 )
        {
            identical = false;
        }
    }
    mpz_mul(destinationThread.results[position - 1], destinationThread.x, destinationThread.y);
    if(mpz_cmp(sourceThread.results[position - 1], destinationThread.results[position - 1]) == 0)
    {
        std::cout << "Thread " << destinationThread.runnerID << "successfully cloned from thread "
        << sourceThread.runnerID << std::endl;
    }
    destinationThread.branches[position] = !(sourceThread.branches[position]);
    setXY(destinationThread.x, destinationThread.y, position, destinationThread.branches[position]);
    if((destinationThread.branches[position] & 0b11) == 0b01 ||
       (destinationThread.branches[position] & 0b11) == 0b10 )
    {
        identical = false;
    }
    mpz_mul(destinationThread.results[position], destinationThread.x, destinationThread.y);
    mpz_set(destinationThread.number, sourceThread.number);
    destinationThread.number_size = sourceThread.number_size;
    destinationThread.xy_size = sourceThread.xy_size;
    destinationThread.strategy = sourceThread.strategy ^ 0b11111111;
    return identical;
}

void   widthIterateAllocator (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], 
                              const unsigned int xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE], const unsigned int number_size, unsigned int strategy, 
                              Runner *threads, unsigned int thread_ID, unsigned int runnerNumber, unsigned int& runnerIndex)
{
    void (*widthStrategicIterator)(mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*, const unsigned int,
                                   const unsigned int, unsigned int*, const unsigned int);
    void (*depthStrategicIterator)(mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*, const unsigned int,
                                   const unsigned int, unsigned int*, const unsigned int);
    switch (strategy){
        case LL:
            widthStrategicIterator = &widthIterateLL;
            depthStrategicIterator = &depthIterateLL;
            break;
        case LR:
            widthStrategicIterator = &widthIterateLR;
            depthStrategicIterator = &depthIterateLR;
            break;
        case RL:
            widthStrategicIterator = &widthIterateRL;
            depthStrategicIterator = &depthIterateRL;
            break;
        case RR:
            widthStrategicIterator = &widthIterateRR;
            depthStrategicIterator = &depthIterateRR;
            break;
        default:
            std::cout << "Unknown strategy selected" << std::endl;
            return;
    }
    if(position < xy_size) {

        getNodeType(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            if(runnerIndex < runnerNumber){
                ++runnerIndex;
                branches[position] = branches[position] ^ 0b10000;
                threads[runnerIndex].identical = cloneThread(threads[thread_ID], threads[runnerIndex], position);
                threads[runnerIndex].ready = true;

                resetXY(x, y, position);
                branches[position] = branches[position] >> 2;
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthIterateAllocator(x, y, diff, number,
                                      results, xy_size, position, branches, number_size, strategy,
                                      threads, thread_ID, runnerNumber, runnerIndex);
                resetXY(x, y, position);
            }else{
                widthStrategicIterator(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
                resetXY(x, y, position);

                branches[position] = branches[position] >> 2;
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthStrategicIterator(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
                resetXY(x, y, position);
            }
        } else if ((branches[position] == oppositeLeft) ||
                   (branches[position] == oppositeRight))
        {
            branches[position] = branches[position] ^ 0b10000;
            depthIterateAllocator (x, y, diff, number,
                                   results, xy_size, position, branches, number_size, strategy,
                                   threads, thread_ID, runnerNumber, runnerIndex);
            branches[position] = branches[position] >> 2;
        }

    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }
    if(findWork(threads, runnerNumber, thread_ID))
    {
        widthIterateAllocator (x, y, diff, number, 
                               results, xy_size, position, branches, number_size, strategy, 
                               threads, thread_ID, runnerNumber, runnerIndex);
    }else{
        depthIterateAllocator (x, y, diff, number, 
                               results,xy_size, position, branches, number_size, strategy, 
                               threads, thread_ID, runnerNumber, runnerIndex);
    }


}
bool findWork (Runner *runners, unsigned int runnerNumber, unsigned int runnerID)
{
    bool identical;
    for(int i = 0; i < MAX_XY_SIZE; ++i)
    {
        for(int j = 0; j < runnerNumber; ++j)
        {
            if(runners[j].branches[i] > 0b10000)
            {
                identical = cloneThread(runners[runnerID], runners[j], i);
            }
        }
    }
    return identical;
}


void   depthIterateAllocator (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], 
                              unsigned int xy_size, unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int number_size, unsigned int strategy, 
                              Runner *threads, unsigned int thread_ID, unsigned int runnerNumber, unsigned int& runnerIndex)
{
    void (*strategicIterator)(mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*, const unsigned int,
                              const unsigned int, unsigned int*, const unsigned int);
    switch (strategy){
        case LL:
            strategicIterator = &depthIterateLL;
            break;
        case LR:
            strategicIterator = &depthIterateLR;
            break;
        case RL:
            strategicIterator = &depthIterateRL;
            break;
        case RR:
            strategicIterator = &depthIterateRR;
            break;
        default:
            std::cout << "Unknown strategy selected" << std::endl;
            return;
    }

    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        setXY(x, y, position, branches[position]);
        getNodeType(number, results[position], position + 1, branches);                                 /// get next branch
        strategicIterator(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            strategicIterator(x, y, diff, number, results, xy_size, position + 1, branches, number_size);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size);
    }

    if(findWork(threads, runnerNumber, thread_ID))
    {
        widthIterateAllocator (x, y, diff, number, 
                               results, xy_size, position, branches, number_size, strategy, 
                               threads, thread_ID, runnerNumber, runnerIndex);
    }else{
        depthIterateAllocator (x, y, diff, number, 
                               results, xy_size, position, branches, number_size, strategy, 
                               threads, thread_ID, runnerNumber, runnerIndex);
    }
}
