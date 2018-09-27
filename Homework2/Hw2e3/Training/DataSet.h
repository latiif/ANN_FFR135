//
// Created by latiif on 9/24/18.
//

#ifndef TRAINING_TRAININGSET_H
#define TRAINING_TRAININGSET_H

#include "string"

#define MAX_DATASET_LENGTH 15000

class DataSet {
public:
    double samples[MAX_DATASET_LENGTH][2];
    int targets[MAX_DATASET_LENGTH];

    DataSet(std::string filename);

    int total;
};


#endif //TRAINING_TRAININGSET_H
