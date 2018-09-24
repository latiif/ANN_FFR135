#include<iostream>
#include<vector>

#define N 160
#define W 10
#define H 16

using namespace std;


class Hopfield{
public:
    double w [N][N]={0};
    void train(vector<int> pattern){
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                if (i==j) 
                    w[i][j]=0;
                else 
                    w[i][j] += ((double)1/N) * pattern[i] * pattern[j];
            }
        }
    }
};

vector<int> matrix2vector(int matrix[H][W]){
    vector<int> v;
    for (int i=0;i<H;i++)
        for (int j=0; j<W;j++)
            v.push_back(matrix[i][j]);

    return v;

}

int x0[H][W] = {
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,1,1,1,1,-1,-1,-1},
{-1,-1,1,1,1,1,1,1,-1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,1,1,1,-1,-1,1,1,1,-1},
{-1,-1,1,1,1,1,1,1,-1,-1},
{-1,-1,-1,1,1,1,1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};

int main()
{
    Hopfield* hopfield = new Hopfield();

    hopfield->train(matrix2vector(x0));

    cout<<"Hello"<<endl;
    return 0;
}