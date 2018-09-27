//
// Created by latiif on 2018-09-24.
//

#include "Misc.h"
#include <random>

double Misc::generateRandomNormal(double mean, double variance) {
    std::random_device rd;
    std::normal_distribution<> uni(mean, variance);
    return uni(rd);

}

double Misc::max(double a, double b) {
    return (a > b ? a : b);
}

int Misc::generateRandomUniform(int a, int b) {
    std::random_device rd;
    std::uniform_int_distribution<int> uni(a, b);
    return uni(rd);

}
