//
// Created by latiif on 9/24/18.
//

#include "Network.h"
#include "vector"

Network::Network(int M1, int M2) {

    this->w1 =new WeightMatrix();
    this->w2= new WeightMatrix();
    this->w3 = new WeightMatrix();

    this->setSize(w1,M1,2);
    this->setSize(w2,M2,M1);
    this->setSize(w3,1,M2);

    th1 = new Threshold();
    th1->resize(M1);

    th2= new Threshold();
    th2->resize(M2);

    th3 = new Threshold();
    th3->resize(1);



}

void Network::setSize(WeightMatrix *weightMatrix, int d1, int d2) {
    weightMatrix->resize(d1);
    for (int i=0;i<d1;i++) weightMatrix[i].resize(d2);

}

int Network::predict(double pattern[], int num) {

    for (double m1 = 0;m1 < w1->size();m1++){

        for (int i=0;i<num;i++){

        }
    }

    return 0;
}
