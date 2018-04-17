//
// Created by Davi Grossi Hasuda on 19/03/2018.
//

#include "CostFunction.h"
#include <math.h>

double CostFunction::getCost(vector<double> x) {
    if (x.size() != 2) {
        return -1;
    }
    if (x[0] <= 0) {
        return 999999999999.9;
    }
    double priceFactor = (exp(-(x[0]*x[0]))) / x[0];
    double marketingFactor = 2.0/(1.0 + exp(-x[1]));
    double pricePerUnit = 200;
//    printf("%lf\n", priceFactor*marketingFactor*(x[0]-x[1]-pricePerUnit));
    return (priceFactor*marketingFactor*(x[0]-pricePerUnit))-x[1];
}