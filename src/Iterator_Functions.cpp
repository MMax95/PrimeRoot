//
// Created by blackberry on 27.07.2020.
//

#include "../include/Iterator_Functions.h"
char* buffer;
bool printouts = false;

char *printNumber(mpz_t& number)
{
    return mpz_get_str(buffer, 10, number);
}

void   widthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {

        getNodeTypeLL(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateLL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }

    }else if(position < number_size)
    {
        checkResultL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {

        getNodeTypeLR(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateLR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }

    }else if(position < number_size)
    {
        checkResultR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateRL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(position < xy_size) {

        getNodeTypeRL(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            resetXY(x, y, position);
            branches[position] = branches[position] >> 2;
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateRL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }

    }else if(position < number_size)
    {
        checkResultL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(printouts){std::cout << "Width: " << position <<"\n";}

    {
        if(position < xy_size) {
            getNodeTypeRR(number, results[position - 1], position, branches);
            if ((branches[position] == equalLeft) ||
                (branches[position] == equalRight))
            {
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);

                if(printouts){std::cout << " Branch "<< branches[position] << " Right child: ";
                    gmp_printf(mpz_get_str (buffer, 2, results[position]));
                    gmp_printf("\n");}

                widthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
                resetXY(x, y, position);
                branches[position] = branches[position] >> 2;
                if(printouts){std::cout << " Branch "<< branches[position] << " Left child: ";}

                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
                resetXY(x, y, position);
            } else {
                branches[position] = branches[position] & 0b1111;
                depthIterateRR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
            }

        }else if(position < number_size)
        {
            if(printouts){std::cout <<"\n";}

            checkResultR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
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
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    {
        checkResultL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
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
        checkResultR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
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
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;
            depthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    {
        checkResultL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   depthIterateRR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(printouts){std::cout << "Depth: " << position << " Branch: "<< branches[position] <<"\n";}

    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        if(printouts){gmp_printf("Number: ");
            gmp_printf(mpz_get_str (buffer, 2, results[position]));
            gmp_printf("\n\n");}

        setXY(x, y, position, branches[position]);
        getNodeTypeRR(number, results[position], position + 1, branches);                                 /// get next branch
        depthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            depthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    {
        if(printouts){std::cout <<"\n";}

        checkResultR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}

void OFI(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],unsigned int &xy_size,
         unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner)
{
    unsigned int steps = xy_size - mpz_sizeinbase(y, 2);
    mpz_set(results[position], results[position - 1]);
    for (int i = 0; i < steps; ++i)
    {
        if ((branches[position] & 0b11) == (currentRunner.strategy & 0b11))
        {
            mpz_mul_2exp(diff, y, position);
            mpz_add(results[xy_size], results[xy_size], diff);
            mpz_setbit(x, position);
        }
        ++position;
        getNodeType(results[xy_size], number, position, branches);
    }
    if (mpz_cmp(number, results[xy_size]) == 0)
    {

//        std::cout << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[xy_size]) << std::endl;
        addResult(x, y, diff, number, xy_size, currentRunner.number_size, currentRunner);
    }

    for (int i = 0; i <= steps; ++i)
    {
        branches[position] = 0;
        --position;
        mpz_clrbit(x, position);

    }

    mpz_set_ui(results[xy_size], 1);
    mpz_set_ui(diff, 1);
}

void OFI_L(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],unsigned int &xy_size,
         unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner)
{
    if(printouts){std::cout << "\nOFI_L called on position: " << position;}

    unsigned int steps = xy_size - mpz_sizeinbase(y, 2);
    mpz_set(results[position], results[position - 1]);
    for (int i = 0; i < steps; ++i)
    {
        if ((branches[position] & 0b11) == 0b01)
        {
            mpz_mul_2exp(diff, y, position);
            mpz_add(results[xy_size], results[xy_size], diff);
            mpz_setbit(x, position);
        }
        ++position;
        getNodeTypeLL(results[xy_size], number, position, branches);
    }
    if (mpz_cmp(number, results[xy_size]) == 0)
    {

//        std::cout << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[xy_size]) << std::endl;
        addResult(x, y, diff, number, xy_size, currentRunner.number_size, currentRunner);
    }

    for (int i = 0; i <= steps; ++i)
    {
        branches[position] = 0;
        --position;
        mpz_clrbit(x, position);

    }

    mpz_set_ui(results[xy_size], 1);
    mpz_set_ui(diff, 1);
}

void OFI_R(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],unsigned int &xy_size,
           unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner)
{
    unsigned int steps = xy_size - mpz_sizeinbase(x, 2);
    mpz_set(results[position], results[position - 1]);
    if(printouts){std::cout << "\nOFI_R called on position: " << position;
        std::cout << "\nInitial number: ";
        gmp_printf(mpz_get_str (buffer, 2, results[position]));}

    if(printouts){std::cout << "\nInitial x: ";
        gmp_printf(mpz_get_str (buffer, 2, x));
        std::cout << "\nInitial y: ";
        gmp_printf(mpz_get_str (buffer, 2, y));}

    for (int i = 0; i < steps; ++i)
    {
        if ((branches[position] & 0b11) == 0b10)
        {
            mpz_mul_2exp(diff, x, position);
            mpz_add(results[xy_size], results[xy_size], diff);
            mpz_setbit(y, position);
        }
        ++position;
        getNodeTypeRR(results[xy_size], number, position, branches);
    }
    if(printouts){std::cout << "\nFinal number: ";
        gmp_printf(mpz_get_str (buffer, 2, results[xy_size]));
        std::cout << "\nFinal x: ";
        gmp_printf(mpz_get_str (buffer, 2, x));
        std::cout << "\nFinal y: ";
        gmp_printf(mpz_get_str (buffer, 2, y));
        std::cout << "\n";}

    if (mpz_cmp(number, results[xy_size]) == 0)
    {
        addResult(x, y, diff, number, xy_size, currentRunner.number_size, currentRunner);
    }
    for (int i = 0; i <= steps; ++i)
    {
        branches[position] = 0;
        --position;
        mpz_clrbit(y, position);
    }

    mpz_set_ui(results[xy_size], 1);
    mpz_set_ui(diff, 1);
}

void checkResultL(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
                 unsigned int &xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE],
                 unsigned int &number_size, Runner &currentRunner)
{

    if(mpz_tstbit(results[position - 1], number_size) || mpz_tstbit(results[position - 1], number_size + 1))
    {
        return;
    }
    int compared_result = mpn_cmp(results[position - 1]->_mp_d, number->_mp_d, number->_mp_size);
    if (compared_result == 0)
    {
//        std::cout << "Result_found " << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[position - 1]) << "\n";
        addResult(x, y, diff, number, xy_size, number_size, currentRunner);
        return;
    } else if (compared_result > 0)
    {
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b11)
    {
        return;
    } else if ((branches[xy_size    ] & 0b11) == 0b11)
    {
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b01)
    {
        OFI_L(x, y, diff, number, results, xy_size, position, branches, currentRunner);
//        std::cout << "Checkpoint 4 branch X" << std::endl;
    } else if ((branches[xy_size - 1] & 0b11) == 0b10)
    {
        OFI_L(y, x, diff, number, results, xy_size, position, branches, currentRunner);
//        std::cout << "Checkpoint 4 branch Y" << std::endl;
    } else if ((branches[xy_size - 1] & 0b11) == 0b00)
    {
        OFI_L(x, y, diff, number, results, xy_size, position, branches, currentRunner);
        if(xy_size == 0){return;}
        OFI_L(y, x, diff, number, results, xy_size, position, branches, currentRunner);
//        std::cout << "Checkpoint 4 branch XY" << std::endl;
    }
}

void checkResultR(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
                   unsigned int &xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE],
                   unsigned int &number_size, Runner &currentRunner)
{
    if(mpz_tstbit(results[position - 1], number_size) || mpz_tstbit(results[position - 1], number_size + 1))
    {
        return;
    }
    int compared_result = mpn_cmp(results[position - 1]->_mp_d, number->_mp_d, number->_mp_size);
    if (compared_result == 0)
    {
//        std::cout << "Result_found " << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[position - 1]) << "\n";
        addResult(x, y, diff, number, xy_size, number_size, currentRunner);
        return;
    } else if (compared_result > 0)
    {
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b11)
    {
        return;
    } else if ((branches[xy_size    ] & 0b11) == 0b11)
    {
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b01)
    {
        OFI_R(y, x, diff, number, results, xy_size, position, branches, currentRunner);
//        std::cout << "Checkpoint 4 branch X" << std::endl;
    } else if ((branches[xy_size - 1] & 0b11) == 0b10)
    {
        OFI_R(x, y, diff, number, results, xy_size, position, branches, currentRunner);
//        std::cout << "Checkpoint 4 branch Y" << std::endl;
    } else if ((branches[xy_size - 1] & 0b11) == 0b00)
    {
        OFI_R(x, y, diff, number, results, xy_size, position, branches, currentRunner);
        if(xy_size == 0){return;}
        OFI_R(y, x, diff, number, results, xy_size, position, branches, currentRunner);
//        std::cout << "Checkpoint 4 branch XY" << std::endl;
    }

}

///Memory Functions///

//void generateNode(mpz_t& result, unsigned int position)
//
//{
//    mpz_init_set_d(result, 1);
//    mpz_realloc2(result, (position * 2 + 1));
//} - inlined function

void generateTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y, mpz_t& diff, unsigned int xy_size, unsigned int number_size)
{
    for (int i = 0; i < /*xy_size*/MAX_XY_SIZE; ++i)                                                              /// generates xy_size nodes
    {
        mpz_init_set_d(results[i], 1);
        mpz_realloc2(results[i], (i * 2 + 1));
    }
    for (int j = 0; j < /*number_size*/MAX_N_SIZE; ++j)                                                              /// initializes the branch type list with 0s
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

//    std::cout << "\nTree generated for depth " << xy_size << "\n";
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

    resetTree(threads[thread_ID].results, threads[thread_ID].branches,
                 threads[thread_ID].x, threads[thread_ID].y,
                 threads[thread_ID].diff, threads[thread_ID].xy_size);

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
    void (*checkStrategicResult)  (mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*,
                                   unsigned int&, const unsigned int, unsigned int*,
                                   unsigned int&, Runner&);
    switch (strategy){
        case LL:
//            std::cout << "Selected strategy: Equal Left - Opposite Left" << std::endl;
            widthStrategicIterator = &widthIterateLL;
            depthStrategicIterator = &depthIterateLL;
            getStrategicNodeType   = &getNodeTypeLL;
            checkStrategicResult   = &checkResultL;
            break;
        case LR:
//            std::cout << "Selected strategy: Equal Left - Opposite Right" << std::endl;
            widthStrategicIterator = &widthIterateLR;
            depthStrategicIterator = &depthIterateLR;
            getStrategicNodeType   = &getNodeTypeLR;
            checkStrategicResult   = &checkResultL;
            break;
        case RL:
//            std::cout << "Selected strategy: Equal Right - Opposite Left" << std::endl;
            widthStrategicIterator = &widthIterateRL;
            depthStrategicIterator = &depthIterateRL;
            getStrategicNodeType   = &getNodeTypeRL;
            checkStrategicResult   = &checkResultL;
            break;
        case RR:
//            std::cout << "Selected strategy: Equal Right - Opposite Right" << std::endl;
            widthStrategicIterator = &widthIterateRR;
            depthStrategicIterator = &depthIterateRR;
            getStrategicNodeType   = &getNodeTypeRR;
            checkStrategicResult   = &checkResultL;
            break;
        default:
            std::cout << "Unknown strategy selected" << std::endl;
            return;
    }
    if(position < xy_size) {
        getStrategicNodeType(number, results[position - 1], position, branches);
        if ((branches[position] == equalLeft) ||
            (branches[position] == equalRight))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);
            if(thread_ID  < runnerNumber){
                std::cout << "Budded identical branch" << std::endl;
                ++thread_ID;
                branches[position] = branches[position] & 0b11101111;
//                threads[runnerIndex].identical = cloneThread(threads[thread_ID], threads[runnerIndex], position);

                resetXY(x, y, position);
                branches[position] = branches[position] >> 2;
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthIterateAllocator(strategy, threads, thread_ID, runnerNumber, position, newNumber);
                resetXY(x, y, position);
            }else{
                if(printouts){std::cout << "Linear identical branch" << std::endl;}

                widthStrategicIterator(x, y, diff, number, results, xy_size, position + 1,
                                       branches, number_size, threads[thread_ID]);
                resetXY(x, y, position);

                branches[position] = branches[position] >> 2;
                makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
                setXY(x, y, position, branches[position]);
                widthStrategicIterator(x, y, diff, number, results, xy_size, position + 1,
                                       branches, number_size, threads[thread_ID]);
                resetXY(x, y, position);
            }
        } else {
            if(thread_ID < runnerNumber)
            {
                std::cout << "Budding opposite branch" << std::endl;

                branches[position] = branches[position] & 0b1111;
                depthIterateAllocator (x, y, diff, number,
                                       results, xy_size, position, branches, number_size, strategy,
                                       threads, thread_ID, runnerNumber, newNumber);
            }else{
                if(printouts){std::cout << "Linear opposite branch" << "\n";
                    std::cout << "Initial branch: " << branches[position] << "\n";}

                branches[position] = branches[position] & 0b1111;
                depthStrategicIterator (x, y, diff, number, results, xy_size, position,
                                        branches, number_size, threads[thread_ID]);
            }
        }

    }else if(position < number_size)
    {
        checkStrategicResult(x, y, diff, number, results, xy_size, position, branches, number_size, threads[thread_ID]);
    }


    for(Result &factor: unique_factors)
    {
        if(factor.left == nullptr)
        {
            if(printouts)
            {
                gmp_printf("Factor %Zd selected", factor.number);
                getchar();
            }

            widthIterateAllocator(strategy, threads, thread_ID, runnerNumber, position, factor);
        }
    }

}
bool findWork (Runner *runners, unsigned int runnerNumber, unsigned int runnerID)
{
    ///check for results with no numbers assigned
    for(Result &factor: unique_factors)
    {
        if(factor.left == nullptr)
        {
            if(printouts)
            {
                gmp_printf("Factor %Zd selected", factor.number);
                getchar();
            }
            ///Remember factor
        }
    }
    ///Check if there are threads working on the number
    bool identical = false;
    for(int i = 0; i < MAX_XY_SIZE; ++i)
    {

        for(int j = 0; j < runnerNumber; ++j)
        {
            if(runners[j].branches[i] > 0b10000)
            {
                std::cout << "Identical branch found: "<< runners[j].branches[i] << " on position "<< i << std::endl;
//                identical = cloneThread(runners[runnerID], runners[j], i);
            }
        }
    }
    return identical;
}


void   depthIterateAllocator (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
                              unsigned int &xy_size, unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, unsigned int strategy,
                              Runner *threads, unsigned int thread_ID, unsigned int runnerNumber, Result newNumber)
{
    void (*strategicIterator)(mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*, unsigned int&,
                              const unsigned int, unsigned int*, unsigned int&, Runner&);
    void (*checkStrategicResult)  (mpz_t&, mpz_t&, mpz_t&, mpz_t&, mpz_t*,
                                   unsigned int&, const unsigned int, unsigned int*,
                                   unsigned int&, Runner&);
    switch (strategy){
        case LL:
            strategicIterator = &depthIterateLL;
            checkStrategicResult   = &checkResultL;
            break;
        case LR:
            strategicIterator = &depthIterateLR;
            checkStrategicResult   = &checkResultL;
            break;
        case RL:
            strategicIterator = &depthIterateRL;
            checkStrategicResult   = &checkResultL;
            break;
        case RR:
            strategicIterator = &depthIterateRR;
            checkStrategicResult   = &checkResultL;
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
        strategicIterator(x, y, diff, number, results, xy_size, position + 1,
                          branches, number_size, threads[thread_ID]);
        if(branches[position + 1] & 0b10000 /*&& (position + 1 < xy_size)*/)
        {
            branches[position + 1] = branches[position + 1] >> 2;                                          /// switches the child node (00 to 11) or (01 to 10)
            strategicIterator(x, y, diff, number, results, xy_size, position + 1,
                              branches, number_size, threads[thread_ID]);
        }
        resetXY(x, y, position);                                                                       /// resets X[position] and Y[position]
    } else if (position <= number_size)
    {
        checkStrategicResult(x, y, diff, number, results, xy_size, position,
                    branches, number_size, threads[thread_ID]);
    }
}

void    addResult  (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, unsigned int &xy_size,
                    unsigned int &number_size, Runner &currentRunner)
{

    using namespace boost::container;
    int xComp = mpz_cmp_ui(x, 1);
    int yComp = mpz_cmp_ui(y, 1);

//    gmp_printf("%Zd * %Zd = %Zd\n", x, y, number);
    if(xComp && yComp)
    {
        unsigned int uniqueXY = 0b11;
        ///stop all threads working on N - make threads wait for reallocation

        ///check for any occurrence of X or Y in unique factors list
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
            case 0b00: ///both X and Y are already in the factor list

                break;
            case 0b01: ///Y is already in the list

                unique_factors.push_back(Result(x));
                currentRunner.targetNumber->left = &unique_factors.back();
                break;
            case 0b10: ///X is already in the list
                unique_factors.push_back(Result(y));
                currentRunner.targetNumber->right = &unique_factors.back();
                break;
            case 0b11: ///Neither X nor Y are in the list
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