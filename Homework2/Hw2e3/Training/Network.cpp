//
// Created by latiif on 9/24/18.
//

#include "Network.h"
#include "vector"
#include <math.h>
#include "random"
#include "Misc.h"

Network::Network(int M1, int M2, double learningRate) {

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
    initThreshold(M2, th2);

    th3 = new Threshold();
    th3->resize(1);
    initThreshold(1, th3);

    this->learningRate = learningRate;

}

void Network::setSize(WeightMatrix *weightMatrix, int d1, int d2) {
    weightMatrix->resize(d1);
    for (int i = 0; i < d1; i ++) (*weightMatrix)[i].resize(d2);

    for (int i = 0; i < d1; i ++)
        for (int j = 0; j < d2; j ++)
            (*weightMatrix)[i][j] = Misc::generateRandom(- 1, 1);

}

double Network::activationFunction(double field) {
    return tanh(field);
}

double Network::activationFunctionDerivative(double val) {
    return (1 - pow(tanh(val), 2.0));
}

DetailedResult *
Network::calculateValues(const Inputs *inputs, const WeightMatrix *w, const Threshold *thresholds, int nInputs,
                         int nOutputs) {
    auto result = new DetailedResult(new Activations(nOutputs), new Fields(nOutputs));

    for (int neuron = 0; neuron < nOutputs; neuron ++) {

        double field = 0.0;
        for (int i = 0; i < nInputs; i ++) {
            field += (*w)[neuron][i] * (*inputs)[i];
        }
        (*(*result).first)[neuron] = activationFunction(field - (*thresholds)[neuron]);
        (*(*result).second)[neuron] = field;
    }

    return result;
}

double Network::predict(Inputs *pattern) {

    auto activations = calculateValues(pattern, w1, th1, 2, w1->size())->first;

    activations = calculateValues(activations, w2, th2, activations->size(), w2->size())->first;

    activations = calculateValues(activations, w3, th3, activations->size(), w3->size())->first;

    return (*activations)[0];
}

int Network::sgn(double val) {
    return val >= 0 ? 1 : - 1;
}

double Network::predict(double *pattern, int size) {
    auto inputPattern = new Inputs(size);

    for (int i = 0; i < size; i ++) (*inputPattern)[i] = pattern[i];

    return sgn(predict(inputPattern));
}



void Network::initThreshold(int size, Threshold *threshold) {
    for (int i = 0; i < size; i ++)
        (*threshold)[i] = Misc::generateRandom(0,0);
}

double Network::train(Inputs *pattern, int target) {


    auto layerOne = calculateValues(pattern, w1, th1, 2, w1->size());

    auto layerTwo = calculateValues(layerOne->first, w2, th2, layerOne->first->size(), w2->size());

    auto outputLayer = calculateValues(layerTwo->first, w3, th3, layerTwo->first->size(), w3->size());


    auto errors = new Errors(Misc::max(th2->size(),th1->size()));

    /// Train the output layer w3,th3
    for (int i = 0; i < 1; i ++) {
        double error;
        double field = outputLayer->second->at(i);
        double prediction = outputLayer->first->at(i);

        error = activationFunctionDerivative(field) * (target - prediction);

        errors->at(i) = error;

        for (int j = 0; j < w3->at(i).size(); j ++) {
            (*w3)[i][j] += this->learningRate * error * layerTwo->first->at(j);
        }
        th3->at(i) += this->learningRate * error;
    }

    /// Train the second hidden layer w2, th2
    for (int j = 0; j < th2->size(); j ++) {
        double error = 0.0;
        double field = layerTwo->second->at(j);


        for (int i = 0; i < th3->size(); i ++) {
            error += errors->at(i) * (*w3)[i][j] * activationFunctionDerivative(field);
        }
        errors->at(j) = error;

        for (int i = 0; i < w2->at(j).size(); i ++) {
            (*w2)[j][i] += this->learningRate * error * layerOne->first->at(i);
        }
        th2->at(j) += this->learningRate * error;
    }


    /// Train the first hidden layer w1, th1
    for (int j = 0; j < th1->size(); j ++) {
        double error = 0.0;
        double field = layerOne->second->at(j);


        for (int i = 0; i < th2->size(); i ++) {
            error += errors->at(i) * (*w2)[i][j] * activationFunctionDerivative(field);
        }
        errors->at(j) = error;

        for (int i = 0; i < w1->at(j).size(); i ++) {
            (*w1)[j][i] += this->learningRate * error * layerOne->first->at(i);
        }
        th1->at(j) += this->learningRate * error;
    }

    delete errors;
    delete layerOne;
    delete layerTwo;
    delete outputLayer;

    return 0;
}

double Network::train(double *pattern, int size, int target) {
    auto inputPattern = new Inputs(size);

    for (int i = 0; i < size; i ++) (*inputPattern)[i] = pattern[i];

    return train(inputPattern, target);
}

Network::~Network() {
    delete w1;
    delete w2;
    delete w3;

    delete th1;
    delete th2;
    delete th3;
}

