//
// Created by latiif on 9/24/18.
//

#ifndef TRAINING_NETWORK_H
#define TRAINING_NETWORK_H

#include "vector"
#include <string>

typedef std::vector<std::vector<double>> WeightMatrix;
typedef std::vector<double> Threshold;
typedef std::vector<double> Activations;
typedef std::vector<double> Fields;

typedef std::vector<double> Errors;

typedef std::pair<Activations *, Fields *> DetailedResult;

typedef std::vector<double> Inputs;

class Network {
private:

    double learningRate;

    void updateWeightMatrixAndTheta(WeightMatrix *w, Threshold *threshold, Errors *error, Activations *activations);

    void setSize(WeightMatrix *weightMatrix, int d1, int d2);

    double activationFunction(double field);

    inline void initThreshold(int size, Threshold *threshold);

    double activationFunctionDerivative(double val);

    int sgn(double);

    DetailedResult *calculateValues(const Inputs *, const WeightMatrix *, const Threshold *, int nInputs, int nOutputs);


    void writeMatrix(WeightMatrix *w, const std::string filename);

    void writeThreshold(Threshold *th, const std::string filename);

public:
    WeightMatrix *w1, *w2, *w3;
    Threshold *th1, *th2, *th3;

    Network(int M1, int M2, double eta);

    ~Network();

    Network *makeCopy();

    double predict(Inputs *pattern);

    double predict(double pattern[], int size);

    double train(double pattern[], int size, int target);

    double train(Inputs *pattern, int target);

    void saveCSV();
};


#endif //TRAINING_NETWORK_H
