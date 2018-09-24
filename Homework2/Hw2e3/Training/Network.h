//
// Created by latiif on 9/24/18.
//

#ifndef TRAINING_NETWORK_H
#define TRAINING_NETWORK_H

#include "vector"

typedef std::vector<std::vector<double>> WeightMatrix;
typedef std::vector<double> Threshold;
typedef std::vector<double> Fields;
typedef std::vector<double> Inputs;
class Network {
private:
    double generateRandom(double a, double b);
    void setSize(WeightMatrix* weightMatrix,int d1, int d2);
    double activationFunction(double field);
    inline void initThreshold(int size, Threshold* threshold);
    double activationFunctionDerivative(double val);

    int sgn(double);

    Fields* calculateValues(const Inputs*, const WeightMatrix*, const Threshold*,int nInputs, int nOutputs);

public:
    WeightMatrix *w1, *w2, *w3;
    Threshold *th1,*th2,*th3;
    Network(int M1, int M2);

    double predict(Inputs *pattern);
    double predict(double pattern[], int size);
};


#endif //TRAINING_NETWORK_H
