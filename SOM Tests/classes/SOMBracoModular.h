#ifndef SOMMODULARARM_h
#define SOMMODULARARM_h

#define SOM_N_MAX 30
#define SOM_F_MAX 10 
#include <cmath>
#include <vector>


class SOMModulaArm
{
  public:
    SOMModulaArm(std::vector< std::vector< std::vector <double> > > inputMatrix, int sizeOfSOM, int depthOfSOM, int inputMinIndex, int inputMaxIndex);
    void bestDistance(double features[SOM_F_MAX], int &index_best_l, int &index_best_c);
    double parcialDistance(double features[SOM_F_MAX], int i, int j);
    void bestResponse(double targetFeatures[SOM_F_MAX], double responseFeatures[SOM_F_MAX] );
 

  private:
    int som_n; // Tamanho da matriz
    int som_f; // Tamanho do vetor de caracteristicas (features)

    int input_min;
    int input_max;

    double neuralMatrix[SOM_N_MAX][SOM_N_MAX][SOM_F_MAX];

}; 


SOMModulaArm::SOMModulaArm(std::vector< std::vector< std::vector <double> > > inputMatrix, int sizeOfSOM, int depthOfSOM, int inputMinIndex, int inputMaxIndex) {
    som_n = sizeOfSOM;
    som_f = depthOfSOM;
    input_min = inputMinIndex;
    input_max = inputMaxIndex;
    for(int i=0;i<som_n;i++){
      for(int j=0;j<som_n;j++){
        for(int k=0;k<som_f;k++){
          neuralMatrix[i][j][k] = inputMatrix[i][j][k];
        }
      }
    }
}

double SOMModulaArm::parcialDistance(double features[SOM_F_MAX], int i, int j){
  double soma = 0;
  for (int f=input_min; f<=input_max; f++){
    soma += pow(features[f] - neuralMatrix[i][j][f],2); 
  }
  return  sqrt(soma); 
}

void SOMModulaArm::bestDistance(double features[SOM_F_MAX], int &index_best_l, int &index_best_c){
  index_best_l = 0;
  index_best_c = 0;
  float bestDistance = parcialDistance(features,index_best_l,index_best_c); 
  for(int i=0; i < som_n; i++) {
    for(int j=0; j < som_n; j++) {
      float d = parcialDistance(features,i,j);
      if(d < bestDistance){
        index_best_l = i;
        index_best_c = j;
        bestDistance = d;  
      }
    }
  }
}

void SOMModulaArm::bestResponse(double features[SOM_F_MAX], double responseFeatures[SOM_F_MAX]){
  int bestLine=0; 
  int bestColumn=0; 
  bestDistance(features, bestLine, bestColumn);

  for(int i=0;i<som_f;i++){
    responseFeatures[i] = neuralMatrix[bestLine][bestColumn][i];
  }
}
 
#endif
