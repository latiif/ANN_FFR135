//
// Created by latiif on 2018-09-24.
//

#include "Misc.h"
#include <random>

double Misc::generateRandom(double mean, double variance) {
    std::random_device rd;
    std::normal_distribution<> uni(mean, variance);
    return uni(rd);

}

double Misc::max(double a, double b) {
    return (a>b?a:b);
}
