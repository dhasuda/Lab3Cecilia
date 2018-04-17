#include <iostream>
#include "cmake-build-debug/Population.h"

int main() {

    vector<double> lowerBound;
    lowerBound.push_back(-1.0);
    lowerBound.push_back(-1.0);

    vector<double> upperBound;
    upperBound.push_back(10.0);
    upperBound.push_back(10.0);

    Population pop = Population(100, 2, lowerBound, upperBound);

    printf("Initial global best: %lf\n", pop.getGlobalBest());

    for (int i=0; i<100; i++) {
        pop.runOneIteration();
        printf("middle global best: %lf\n", pop.getGlobalBest());
    }

    printf("Final global best: %lf\n", pop.getGlobalBest());

    return 0;
}