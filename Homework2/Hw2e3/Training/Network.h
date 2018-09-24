//
// Created by latiif on 9/24/18.
//

#ifndef TRAINING_NETWORK_H
#define TRAINING_NETWORK_H

#include "vector"

typedef std::vector<std::vector<double>> WeightMatrix;
typedef std::vector<double> Threshold;
typedef std::vector<double> Fields;

class Network {
private:
    void setSize(WeightMatrix* weightMatrix,int d1, int d2);
    double activationFunction(double field);

public:
    WeightMatrix *w1, *w2, *w3;
    Threshold *th1,*th2,*th3;
    Network(int M1, int M2);

    int predict(double pattern[2]);
};


#endif //TRAINING_NETWORK_H
