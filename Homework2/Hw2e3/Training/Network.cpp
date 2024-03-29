//
// Created by latiif on 9/24/18.
//

#include "Network.h"
#include "vector"
#include <math.h>
#include "random"
#include "Misc.h"
#include <fstream>

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
            (*weightMatrix)[i][j] = Misc::generateRandomNormal(0, 1);

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

    return sgn((*activations)[0]);
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
        (*threshold)[i] = 0;
}

double Network::train(Inputs *pattern, int target) {


    auto layerOne = calculateValues(pattern, w1, th1, 2, w1->size());

    auto layerTwo = calculateValues(layerOne->first, w2, th2, layerOne->first->size(), w2->size());

    auto outputLayer = calculateValues(layerTwo->first, w3, th3, layerTwo->first->size(), w3->size());


    Errors *errors[3];

    /// Train the output layer w3,th3
    errors[2] = new Errors(1);
    for (int i = 0; i < 1; i ++) {
        double error;
        double field = outputLayer->second->at(i);
        double prediction = outputLayer->first->at(i);

        error = activationFunctionDerivative(field) * (target - prediction);

        errors[2]->at(i) = error;

    }

    /// Train the second hidden layer w2, th2
    errors[1] = new Errors(th2->size());

    for (int j = 0; j < th2->size(); j ++) {
        double error = 0.0;
        double field = layerTwo->second->at(j);


        for (int i = 0; i < th3->size(); i ++) {
            error += errors[2]->at(i) * (*w3)[i][j] * activationFunctionDerivative(field);
        }
        errors[1]->at(j) = error;

    }


    /// Train the first hidden layer w1, th1
    errors[0] = new Errors(th1->size());

    for (int j = 0; j < th1->size(); j ++) {
        double error = 0.0;
        double field = layerOne->second->at(j);


        for (int i = 0; i < th2->size(); i ++) {
            error += errors[1]->at(i) * (*w2)[i][j] * activationFunctionDerivative(field);
        }
        errors[0]->at(j) = error;
    }


    /// Update weights for the first layer
    updateWeightMatrixAndTheta(w1, th1, errors[0], pattern);
    updateWeightMatrixAndTheta(w2, th2, errors[1], layerOne->first);
    updateWeightMatrixAndTheta(w3, th3, errors[2], layerTwo->first);

    //Free up memory used
    delete errors[0];
    delete errors[1];
    delete errors[2];
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

void
Network::updateWeightMatrixAndTheta(WeightMatrix *w, Threshold *threshold, Errors *error, Activations *activations) {
    for (int i = 0; i < w->size(); i ++) {
        for (int j = 0; j < w->at(i).size(); j ++) {
            w->at(i)[j] += learningRate * error->at(i) * activations->at(j);
        }

        threshold->at(i) -= learningRate * error->at(i);
    }


}

Network *Network::makeCopy() {
    auto res = new Network(th1->size(), th2->size(), learningRate);

    res->w1 = new WeightMatrix(*w1);
    res->w2 = new WeightMatrix(*w2);
    res->w3 = new WeightMatrix(*w3);

    res->th1 = new Threshold(*th1);
    res->th2 = new Threshold(*th2);
    res->th3 = new Threshold(*th3);


    return res;
}

void Network::saveCSV() {

    writeMatrix(w1, "w1.csv");
    writeMatrix(w2, "w2.csv");
    writeMatrix(w3, "w3.csv");

    writeThreshold(th1, "t1.csv");
    writeThreshold(th2, "t2.csv");
    writeThreshold(th3, "t3.csv");
}

void Network::writeMatrix(WeightMatrix *w, const std::string filename) {
    std::ofstream output;
    output.open(filename);

    for (int row = 0; row < w->size(); row ++) {
        for (int col = 0; col < w->at(row).size(); col ++) {
            output << w->at(row)[col];
            if (col == w->at(row).size() - 1) { output << std::endl; }
            else { output << " , "; }
        }
    }

    output.close();
}

void Network::writeThreshold(Threshold *th, const std::string filename) {
    std::ofstream output;
    output.open(filename);

    for (int row = 0; row < th->size(); row ++) {
        output << th->at(row) << std::endl;
    }

    output.close();
}

