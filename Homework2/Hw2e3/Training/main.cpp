#include <iostream>
#include "DataSet.h"

#include "Network.h"
#include "Misc.h"
#include <cstdlib>
#define T 10000

int main(int argc, char **argv) {
    double accuracy = 100.0;

    auto train = new DataSet("../../training_set.csv");
    auto validation = new DataSet("../../training_set.csv");

    int m1,m2;

    m1 = atoi(argv[1]);
    m2 = atoi(argv[2]);

    int counter = 0;
    while (counter ++ < 100) {


        auto network = new Network(m1, m2, 0.01);


        for (int t = 0; t < T; t ++) {

            auto mu = (int) Misc::generateRandom(0, 10000);
            network->train(train->samples[mu], 2, train->targets[mu]);
        }


        int correct = 0;
        int pValue = 5000;
        accuracy = 0.0;
        for (int i = 0; i < pValue; i ++) {
            auto guess = network->predict(validation->samples[i], 2);
            auto target = validation->targets[i];
            correct += (guess == target ? 1 : 0);
            accuracy += abs(guess - target);
        }

        accuracy = accuracy / (2 * pValue);


        if (accuracy <= 0.14) {
            std::cout << accuracy << '\t' << m1 << '\t' << m2 << std::endl;
        }

        delete network;
    }

    return 0;
}
