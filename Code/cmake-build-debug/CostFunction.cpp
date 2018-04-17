//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#include "CostFunction.h"
#include <math.h>

double CostFunction::getCost(vector<double> x) {
    if (x.size() != 2) {
        return -1;
    }
    return -(x[0]*x[0] + x[1]*x[1]);
    //return (fabs(x[0]) + fabs(x[1])) / (x[0]*x[0] + x[1]*x[1] + 2);
}