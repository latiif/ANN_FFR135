//
// Created by latiif on 2018-09-24.
//

#include "Misc.h"
#include <random>

double Misc::generateRandom(double a, double b) {
    std::random_device rd;
    std::uniform_real_distribution<> uni(a, b);
    return uni(rd);

}

double Misc::max(double a, double b) {
    return (a>b?a:b);
}
