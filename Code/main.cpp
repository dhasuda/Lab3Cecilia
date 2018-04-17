#include <iostream>
#include <pthread.h>
#include <math.h>
#include "cmake-build-debug/Population.h"

/* Código sequencial */
int main() {

    /* Clock variables */
    struct timespec start, finish;
    double elapsed;

    vector<double> lowerBound;
    lowerBound.push_back(1.0);
    lowerBound.push_back(0.0);

    vector<double> upperBound;
    upperBound.push_back(1000.0);
    upperBound.push_back(1000000.0);

    /* Começando a contar o tempo */
    // clock_t begin = clock();
    clock_gettime(CLOCK_MONOTONIC, &start);

    Population pop = Population(100, 2, lowerBound, upperBound, 1);

    for (int i=0; i<1000; i++) {
        pop.runOneIteration();
    }

    /* Terminando de contar o tempo */
    clock_gettime(CLOCK_MONOTONIC, &finish);

    printf("Price: %lf, Marketing investment: %lf\n", pop.getGlobalBestPosition()[0], pop.getGlobalBestPosition()[1]);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("execution time: %lf\n", elapsed);

    return 0;
}
