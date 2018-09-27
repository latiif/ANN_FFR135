//
// Created by latiif on 9/24/18.
//

#include <string.h>
#include "DataSet.h"
#include "fstream"

DataSet::DataSet(std::string filename) {


    std::ifstream ifs (filename, std::ifstream::in);

    this->total  = 0;
    int nLines = 0;
    while (!ifs.eof())
    {

        double x,y;
        double t;
        char temp;

        ifs>>x>>temp>>y>>temp>>t;


        targets[nLines] = (int)t;
        samples[nLines][0] = x;
        samples[nLines][1] = y;


        nLines++;
    }
    this->total = nLines - 1;

}
