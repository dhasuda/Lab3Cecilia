//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#include "Population.h"

Population::Population(int numberOfParticles, int xSize, vector<double> lowerBound, vector<double> upperBound, unsigned int seed) {
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
    this->seed = seed;
    for (int i=0; i<numberOfParticles; i++) {
        vector<double> position;
        for (int j=0; j<xSize; j++) {
            double random = (double)rand_r(&seed) / (double)RAND_MAX;
            position.push_back(lowerBound[j] + random*(upperBound[j] - lowerBound[j]));
        }
        Particle newParticle = Particle(position);
        particles.push_back(newParticle);
    }
    globalBest = particles[0].getPersonalBest();
    globalBestPosition = particles[0].getPersonalBestPosition();

    for (int i=0; i<particles.size(); i++) {
        if (particles[i].getPersonalBest() > globalBest) {
            globalBest = particles[i].getPersonalBest();
            globalBestPosition = particles[i].getPersonalBestPosition();
        }
    }
}

void Population::runOneIteration() {

    double w = 1.0;
    double c1 = 0.2;
    double c2 = 0.2;

    for (int i=0; i<particles.size(); i++) {
        vector<double> velocity;

        for (int k = 0; k < lowerBound.size(); k++) {

            velocity.push_back(w * particles[i].getVelocity()[k] +
                               c1 * (double)rand_r(&seed)/(double)RAND_MAX * (particles[i].getPersonalBestPosition()[k] - particles[i].getPosition()[k]) +
                                c2 * (double)rand_r(&seed)/(double)RAND_MAX * (globalBestPosition[k] - particles[i].getPosition()[k]));



            if (particles[i].getPosition()[k] + velocity[k] < lowerBound[k]) {
                velocity[k] = lowerBound[k] - particles[i].getPosition()[k];
            }
            if (particles[i].getPosition()[k] + velocity[k] > upperBound[k]) {
                velocity[k] = upperBound[k] - particles[i].getPosition()[k];
            }

        }

        particles[i].move(velocity);

        if (particles[i].getPersonalBest() > globalBest) {
            globalBest = particles[i].getPersonalBest();
            globalBestPosition = particles[i].getPersonalBestPosition();
        }
    }

}

double Population::getGlobalBest() {
    return this->globalBest;
}

vector<double> Population::getGlobalBestPosition() {
    return this->globalBestPosition;
}

void Population::setGlobalBest(double globalBest, vector<double> globalBestPosition) {
    this->globalBest = globalBest;
    this->globalBestPosition = globalBestPosition;
}

