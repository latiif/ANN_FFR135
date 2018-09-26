#include <iostream>
#include "DataSet.h"
#include "algorithm"
#include "Network.h"
#include "Misc.h"
#include <cstdlib>

#define T 10000
#define V 5000

int main(int argc, char **argv) {
    double classificationError = 100.0;

    auto train = new DataSet("../../training_set.csv");
    auto validation = new DataSet("../../validation_set.csv");

    int m1, m2;

    m1 = atoi(argv[1]);
    m2 = atoi(argv[2]);


    auto network = new Network(m1, m2, 0.01);


    auto stochasticWalk = new std::vector<int>(T);
    for (int i = 0; i < T; i ++) stochasticWalk->at(i) = i;
    std::random_shuffle(stochasticWalk->begin(), stochasticWalk->end());

    bool target = false;

    int count = 0;

    while (!stochasticWalk->empty()) {
        int mu = stochasticWalk->back();
        stochasticWalk->pop_back();

        target = !target;


        count ++;
        network->train(train->samples[mu], 2, train->targets[mu]);

        if (count % 50 == 0) {
            int correct = 0;
            int pValue = 5000;
            classificationError = 0.0;
            for (int i = 0; i < pValue; i ++) {
                auto guess = network->predict(validation->samples[i], 2);
                auto target = validation->targets[i];
                correct += (guess == target ? 1 : 0);
                classificationError += abs((int) (guess - target));
            }

            classificationError = (classificationError * 1.0) / (2 * pValue);


            if (classificationError < 0.14) {
                std::cout << correct << '\t' << classificationError << '\t' << "at patch\t" << count << '\t' << m1
                          << '\t' << m2
                          << std::endl;
                int c = 0;
                for (double x = -1;x<=1;x+=0.02){
                    for (double y = -1;y<=1;y+=0.02){
                        c++;
                        auto input = new Inputs(2);
                        (*input)[0] = x;
                        (*input)[1] = y;
                        auto res = network->predict(input);
                        std::cout<<(res==-1?0:1);
                        if (c%100==0) std::cout<<std::endl;
                        delete(input);
                    }
                }

                break;
            }

        }
    }



    delete network;


    return 0;
}

