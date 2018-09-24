//
// Created by latiif on 9/24/18.
//

#include "Network.h"
#include "vector"
#include <math.h>
#include "random"

Network::Network(int M1, int M2) {

    this->w1 = new WeightMatrix();
    this->w2 = new WeightMatrix();
    this->w3 = new WeightMatrix();

    this->setSize(w1, M1, 2);
    this->setSize(w2, M2, M1);
    this->setSize(w3, 1, M2);

    th1 = new Threshold();
    th1->resize(M1);
    initThreshold(M1, th1);


    th2 = new Threshold();
    th2->resize(M2);
    initThreshold(M2,th2);

    th3 = new Threshold();
    th3->resize(1);
    initThreshold(1,th3);


}

void Network::setSize(WeightMatrix *weightMatrix, int d1, int d2) {
    weightMatrix->resize(d1);
    for (int i = 0; i < d1; i ++) (*weightMatrix)[i].resize(d2);

    for (int i=0;i<d1;i++)
        for (int j=0;j<d2;j++)
            (*weightMatrix)[i][j]= generateRandom(-0.2,0.2);

}

double Network::activationFunction(double field) {
    return tanh(field);
}

double Network::activationFunctionDerivative(double val) {
    return (1 - pow(tanh(val), 2.0));
}

Fields *Network::calculateValues(const Inputs *inputs, const WeightMatrix *w, const Threshold *thresholds, int nInputs,
                                 int nOutputs) {
    auto result = new Fields(nOutputs);

    for (int neuron = 0; neuron < nOutputs; neuron ++) {

        double field = 0.0;
        for (int i = 0; i < nInputs; i ++) {
            field += (*w)[neuron][i] * (*inputs)[i];
        }
        (*result)[neuron] = activationFunction(field - (*thresholds)[neuron]);
    }

    return result;
}

double Network::predict(Inputs *pattern) {

    auto fields = calculateValues(pattern, w1, th1, 2, w1->size());

    fields = calculateValues(fields, w2, th2, fields->size(), w2->size());

    fields = calculateValues(fields, w3, th3, fields->size(), w3->size());

    return (*fields)[0];
}

int Network::sgn(double val) {
    return val >= 0 ? 1 : - 1;
}

double Network::predict(double *pattern, int size) {
    auto inputPattern = new Inputs(size);

    for (int i = 0; i < size; i ++) (*inputPattern)[i] = pattern[i];

    return predict(inputPattern);
}

double Network::generateRandom(double a, double b) {
    std::random_device rd;
    std::uniform_real_distribution<> uni(a, b);
    return uni(rd);
}

void Network::initThreshold(int size, Threshold *threshold) {
    for (int i=0;i<size;i++)
        (*threshold)[i]=generateRandom(-1,1);
}

