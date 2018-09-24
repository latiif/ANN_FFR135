//
// Created by latiif on 9/24/18.
//

#ifndef TRAINING_TRAININGSET_H
#define TRAINING_TRAININGSET_H

#include "string"

#define DATASET_LENGTH 10000

class DataSet {
public:
    double samples[DATASET_LENGTH][2];
    int targets[DATASET_LENGTH];
    DataSet(std::string filename);
};


#endif //TRAINING_TRAININGSET_H
