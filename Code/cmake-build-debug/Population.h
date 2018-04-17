//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#ifndef CODE_POPULATION_H
#define CODE_POPULATION_H

#include <vector>
#include "Particle.h"

using namespace std;

class Population {
public:
    Population(int numberOfParticles, int xSize, vector<double> lowerBound, vector<double> upperBound, unsigned int seed);
    ~Population() = default;
    void runOneIteration();
    double getGlobalBest();
    vector<double> getGlobalBestPosition();
    void setGlobalBest(double globalBest, vector<double> globalBestPosition);
private:
    vector<Particle> particles;
    double globalBest;
    vector<double> globalBestPosition;
    vector<double> lowerBound;
    vector<double> upperBound;
    unsigned int seed;
};


#endif //CODE_POPULATION_H
