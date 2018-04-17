//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#ifndef CODE_PARTICLE_H
#define CODE_PARTICLE_H

#include <vector>

using namespace std;

class Particle {
public:
    Particle(vector<double> position);
    ~Particle() = default;
    void move(vector<double> velocity);
    double getPersonalBest();
    vector<double> getPersonalBestPosition();
    vector<double> getPosition();
    vector<double> getVelocity();
private:
    vector<double> position;
    vector<double> velocity;
    vector<double> personalBestPosition;
    double personalBest;

};


#endif //CODE_PARTICLE_H
