//
// Created by blackberry on 27.07.2020.
//

#include "../include/Iterator_Functions.h"

char* buffer;
const bool PRINTOUTS = false;

char *printNumber(mpz_t& number)
{
    return mpz_get_str(buffer, 10, number);
}

void   widthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(PRINTOUTS){std::cout << "WidthLL: " << position << "\n";}
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);

            if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Left child: ";
                gmp_printf(mpz_get_str (buffer, 2, results[position]));
                gmp_printf("\n");}

            getNodeTypeLL(number, results[position], position + 1, branches);
            widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Right child: ";
                    gmp_printf(mpz_get_str (buffer, 2, results[position]));
                    gmp_printf("\n");}

                branches[position + 1] = branches[position + 1] >> 2;
                widthIterateLL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateLL(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}
void   widthIterateLR (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(PRINTOUTS){std::cout << "WidthLR: " << position << "\n";}
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);

            if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Left child: ";
                gmp_printf(mpz_get_str (buffer, 2, results[position]));
                gmp_printf("\n");}

            getNodeTypeLR(number, results[position], position + 1, branches);
            widthIterateLR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Right child: ";
                    gmp_printf(mpz_get_str (buffer, 2, results[position]));
                    gmp_printf("\n");}

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
    if(PRINTOUTS){std::cout << "WidthRL: " << position << "\n";}
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);

            if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Left child: ";
                gmp_printf(mpz_get_str (buffer, 2, results[position]));
                gmp_printf("\n");}

            getNodeTypeRL(number, results[position], position + 1, branches);
            widthIterateRL(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Right child: ";
                    gmp_printf(mpz_get_str (buffer, 2, results[position]));
                    gmp_printf("\n");}

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
    if(PRINTOUTS)
        {
        std::cout << "WidthRR: " << position << "\n";
        std::cout << " Branch " << branches[position] << " \n";
        }
    if(position < xy_size) {
        if (((branches[position] & 0b11) == 0b11) || ((branches[position] & 0b11) == 0b00))
        {
            makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
            setXY(x, y, position, branches[position]);

            if(PRINTOUTS){std::cout << "Result  ";
                gmp_printf(mpz_get_str (buffer, 2, results[position]));
                gmp_printf("\n");}

            getNodeTypeRR(number, results[position], position + 1, branches);
            widthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            if(branches[position + 1] & 0b10000)
            {
                if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Right child: ";
                    gmp_printf(mpz_get_str (buffer, 2, results[position]));
                    gmp_printf("\n");}

                branches[position + 1] = branches[position + 1] >> 2;
                widthIterateRR(x, y, diff, number, results, xy_size, position + 1, branches, number_size, currentRunner);
            }
            resetXY(x, y, position);
        } else {
            branches[position] = branches[position] & 0b1111;
            depthIterateRR(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
        }
    }else if(position < number_size)
    {
        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}


void   depthIterateLL (mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE], unsigned int &xy_size,
                       const unsigned int position, unsigned int branches[MAX_N_SIZE], unsigned int &number_size, Runner &currentRunner)
{
    if(PRINTOUTS){std::cout << "DepthLL: " << position << " Branch: " << branches[position] << "\n";}
    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        if(PRINTOUTS){gmp_printf("Number: ");
            gmp_printf(mpz_get_str (buffer, 2, results[position]));
            gmp_printf("\n\n");}

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
    {
        if(PRINTOUTS){std::cout << "\n";}

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
    if(PRINTOUTS){std::cout << "DepthRR: " << position << " Branch: " << branches[position] << "\n";}

    if (position < xy_size)
    {
        makeResult(results[position], results[position - 1], position, branches[position], x, y, diff);
        if(PRINTOUTS){gmp_printf("Number: ");
            gmp_printf(mpz_get_str (buffer, 2, results[position]));
            gmp_printf("\n\n");}

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
        if(PRINTOUTS){std::cout << "\n";}

        checkResult(x, y, diff, number, results, xy_size, position, branches, number_size, currentRunner);
    }
}

void OFI(mpz_t& bigger, mpz_t& smaller, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],unsigned int &xy_size,
         unsigned int position, unsigned int branches[MAX_N_SIZE], Runner &currentRunner)
{
    if(PRINTOUTS){
        std::cout << "OFI called at position: " << position << "\n";
        std::cout << "Initial X, Y: "; gmp_printf("%Zd, %Zd \n", bigger, smaller);
    }

    unsigned int steps = xy_size - mpz_sizeinbase(smaller, 2);
    mpz_set(results[position], results[position - 1]);


    for (int i = 0; i < steps; ++i)
    {
        if (mpz_tstbit(number, position) ^ mpz_tstbit(results[xy_size], position))
        {
            mpz_mul_2exp(diff, smaller, position);
            mpz_add(results[xy_size], results[xy_size], diff);
            mpz_setbit(bigger, position);
        }
        ++position;
    }

    if(PRINTOUTS){std::cout << "\nFinal number: ";
        gmp_printf(mpz_get_str (buffer, 2, results[xy_size]));
        std::cout << "\nFinal x: ";
        gmp_printf(mpz_get_str (buffer, 2, bigger));
        std::cout << "\nFinal y: ";
        gmp_printf(mpz_get_str (buffer, 2, smaller));
        std::cout << "\n";}

    if (mpz_cmp(number, results[xy_size]) == 0)
    {

//        if(PRINTOUTS){std::cout << printNumber(x) << " * " << printNumber(y) << " = " << printNumber(results[xy_size]) << std::endl;}
        addResult(bigger, smaller, diff, number, xy_size, currentRunner.number_size, currentRunner);
    }

    for (int i = 0; i <= steps; ++i)
    {
        mpz_clrbit(bigger, position);
        --position;
    }
    if(PRINTOUTS){
        std::cout << "Final   X, Y: ";
        gmp_printf("%Zd, %Zd \n", bigger, smaller);
    }
    mpz_set_ui(results[xy_size], 1);
    mpz_set_ui(diff, 1);
}

void checkResult(mpz_t& x, mpz_t& y, mpz_t& diff, mpz_t& number, mpz_t results[MAX_XY_SIZE],
                 unsigned int &xy_size, const unsigned int position, unsigned int branches[MAX_N_SIZE],
                 unsigned int &number_size, Runner &currentRunner)
{

    if(mpz_tstbit(results[position - 1], number_size) || mpz_tstbit(results[position - 1], number_size + 1))
    {
        if(PRINTOUTS){std::cout << "Number size overflow\n";}
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
        if(PRINTOUTS){std::cout << "Result > Number";}
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b11)
    {
        if(PRINTOUTS){std::cout << "Branch " << branches[xy_size] << " X and Y length full;\n";}
        return;
    } else if ((branches[xy_size    ] & 0b11) == 0b11)
    {
        if(PRINTOUTS){std::cout << "Branch " << branches[xy_size] << " at xy_size size overflow\n";}
        return;
    } else if ((branches[xy_size - 1] & 0b11) == 0b01)
    {
        if(PRINTOUTS){std::cout << "Branch " << branches[xy_size - 1] << " running OFI on X\n";}
        OFI(x, y, diff, number, results, xy_size, position, branches, currentRunner);
    } else if ((branches[xy_size - 1] & 0b11) == 0b10)
    {
        if(PRINTOUTS){std::cout << "Branch " << branches[xy_size - 1] << " running OFI on Y\n";}
        OFI(y, x, diff, number, results, xy_size, position, branches, currentRunner);
    } else if ((branches[xy_size - 1] & 0b11) == 0b00)
    {
        if(PRINTOUTS){std::cout << "Branch " << branches[xy_size - 1] << " running OFI on X and Y\n";}
        OFI(x, y, diff, number, results, xy_size, position, branches, currentRunner);
        if(xy_size == 0){return;}
        OFI(y, x, diff, number, results, xy_size, position, branches, currentRunner);
    }
}

///Memory Functions///

void generateTree(mpz_t results[MAX_XY_SIZE], unsigned int branches[MAX_XY_SIZE], mpz_t& x, mpz_t& y, mpz_t& diff, unsigned int xy_size, unsigned int number_size)
{
    for (int i = 0; i < /*xy_size*/MAX_XY_SIZE; ++i)                                                              /// generates xy_size nodes
    {
        mpz_init_set_d(results[i], 1);
//        mpz_realloc2(results[i], (i * 2 + 1));
        /* Bad allocation logic, since for position 1, result will have 3 bits
         * allocated, but since len(x)/(y) is 2, the max possible result will have
         * 4 bits. As such, the new allocation formula should have the format
         * (i + 1) * 2 to follow the len(x)+len(y)<=len(n) + 1*/
        mpz_realloc2(results[i], ((i+1) * 2));
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
//            if(PRINTOUTS){std::cout << "Selected strategy: Equal Left - Opposite Left" << std::endl;}
            widthStrategicIterator = &widthIterateLL;
            depthStrategicIterator = &depthIterateLL;
            getStrategicNodeType   = &getNodeTypeLL;
            break;
        case LR:
//            if(PRINTOUTS){std::cout << "Selected strategy: Equal Left - Opposite Right" << std::endl;}
            widthStrategicIterator = &widthIterateLR;
            depthStrategicIterator = &depthIterateLR;
            getStrategicNodeType   = &getNodeTypeLR;
            break;
        case RL:
//            if(PRINTOUTS){std::cout << "Selected strategy: Equal Right - Opposite Left" << std::endl;}
            widthStrategicIterator = &widthIterateRL;
            depthStrategicIterator = &depthIterateRL;
            getStrategicNodeType   = &getNodeTypeRL;
            break;
        case RR:
            if(PRINTOUTS){std::cout << "Selected strategy: Equal Right - Opposite Right" << std::endl;}
            widthStrategicIterator = &widthIterateRR;
            depthStrategicIterator = &depthIterateRR;
            getStrategicNodeType   = &getNodeTypeRR;
            break;
        default:
            std::cout << "Unknown strategy selected" << std::endl;
            return;
    }

    getStrategicNodeType(number, results[position - 1], position, branches);

    if ((branches[position] == equalLeft) || (branches[position] == equalRight))
    {
        if(PRINTOUTS){std::cout << "Linear identical branch" << "\n";}
        widthStrategicIterator(x, y, diff, number, results, xy_size, position,
                               branches, number_size, threads[thread_ID]);
        if(branches[position] & 0b10000)
        {
            if(PRINTOUTS){std::cout << " Branch " << branches[position] << " Right child: ";
                gmp_printf(mpz_get_str (buffer, 2, results[position]));
                gmp_printf("\n");}

            branches[position] = branches[position] >> 2;
            widthStrategicIterator(x, y, diff, number, results, xy_size, position,
                                   branches, number_size, threads[thread_ID]);
        }
        resetXY(x, y, position);
    } else {
        if(PRINTOUTS){std::cout << "Linear opposite branch" << "\n";}
        branches[position] = branches[position] >> 2;
        depthStrategicIterator (x, y, diff, number, results, xy_size, position,
                                branches, number_size, threads[thread_ID]);

    }
    ////Reallocation zone

    threads[thread_ID].targetNumber = nullptr;


    for(Result &factor: unique_factors)
    {
        if(factor.left == nullptr)
        {
            if(PRINTOUTS)
            {
                gmp_printf("Factor %Zd selected", factor.number);
                getchar();
            }

            widthIterateAllocator(strategy, threads, thread_ID, runnerNumber, position, factor);
        }
    }

}
void findWork (Runner *threads, unsigned int runnerNumber, unsigned int thread_ID)
{
    Result *lastFactor;
    bool identical;
    ///check for results with no numbers assigned
    for(Result &factor: unique_factors)
    {
        if(factor.left == nullptr)
        {
            if(PRINTOUTS)
            {
                gmp_printf("Factor %Zd selected", factor.number);
                getchar();
            }
            lastFactor = &factor;
        }
    }
    ///Check if there are threads working on the number
    for(int i = 0; i < runnerNumber; ++i)
    {
        if(threads[i].targetNumber == lastFactor)
        ///Get the node closest to the root
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
//        widthIterateAllocator()
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