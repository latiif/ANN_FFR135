#include <iostream>
#include "TrainingSet.h"

#include "Network.h"

int main() {

    auto train = new TrainingSet("../../training_set.csv");


    auto network = new Network(2,2);


    std::cout<<network->predict(train->samples[2],2);
    return 0;
}