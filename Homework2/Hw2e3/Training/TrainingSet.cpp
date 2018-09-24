//
// Created by latiif on 9/24/18.
//

#include <string.h>
#include "TrainingSet.h"
#include "fstream"

TrainingSet::TrainingSet(std::string filename) {


    std::ifstream ifs (filename, std::ifstream::in);

    int nLines = 0;
    while (!ifs.eof())
    {

        double x,y;
        int t;
        char temp;

        ifs>>x>>temp>>y>>temp>>t>>temp;


        targets[nLines] = t;
        samples[nLines][0] = x;
        samples[nLines][1] = y;


        nLines++;
    }

}
