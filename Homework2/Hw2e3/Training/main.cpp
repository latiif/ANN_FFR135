#include <iostream>
#include "DataSet.h"
#include "algorithm"
#include "Network.h"
#include "Misc.h"
#include <cstdlib>


#define V 5000
#define ETA 0.0099

int main(int argc, char **argv) {
    double classificationError = 100.0;

    auto train = new DataSet("../../training_set.csv");
    auto validation = new DataSet("../../validation_set.csv");

    int m1, m2;

    m1 = atoi(argv[1]);
    m2 = atoi(argv[2]);

    auto T = train->total;
    auto EPOCHS = T * 100;

    double bestClassification = 100.0;
    double lastClassification = 0.0;

    auto network = new Network(m1, m2, ETA);
    Network *bestNetwork = nullptr;

    int count = 0;

    while (count ++ < EPOCHS) {

        int mu = Misc::generateRandomUniform(0, T - 1);


        network->train(train->samples[mu], 2, train->targets[mu]);

        if (count % T == 0) {
            int correct = 0;
            int pValue = V;
            classificationError = 0.0;
            for (int i = 0; i < pValue; i ++) {
                auto guess = network->predict(validation->samples[i], 2);
                auto target = validation->targets[i];
                correct += (guess == target ? 1 : 0);
                classificationError += abs((int) (guess - target));
            }

            classificationError = (classificationError * 1.0) / (2 * pValue);


            if (classificationError <= 1) {

                if (classificationError < bestClassification) {
                    bestClassification = classificationError;
                    delete bestNetwork;
                    bestNetwork = network->makeCopy();
                }

                if (classificationError == lastClassification) {
                    break;
                }
                lastClassification = classificationError;
            }
        }
    }

    if (bestClassification < 0.12 && bestNetwork != nullptr) {
        bestNetwork->saveCSV();
    }



    /// Since the problem is 2D, we can ask the network to imagine what it has learned
    if (bestNetwork != nullptr) {
        int c = 0;
        for (double x = - 1; x <= 1; x += 0.02) {
            for (double y = - 1; y <= 1; y += 0.02) {
                c ++;
                auto input = new Inputs(2);
                (*input)[0] = x;
                (*input)[1] = y;
                auto res = bestNetwork->predict(input);
                std::cout << (res == - 1 ? 0 : 1);
                if (c % 100 == 0) std::cout << std::endl;
                delete (input);
            }
        }
        std::cout << "Best:\t" << bestClassification << "\tETA:\t" << ETA << '\t' << m1
                  << '\t' << m2
                  << std::endl;
    }


    delete network;
    delete bestNetwork;


    return 0;
}

