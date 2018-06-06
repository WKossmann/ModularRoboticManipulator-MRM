#include "SOMBracoModular.h"
#include <cmath>

SOMBracoModular::SOMBracoModular( ) {

}

void SOMBracoModular::setup(){

}


float SOMBracoModular::distanciaParcial(int caracteristicas[SOM_MAX_F], int i, int j, int min, int max){
  float soma = 0;
  for (int f=min; f<=max; f++){
    soma += pow(caracteristicas[f] - matrizNeuronios[i][j][f],2); 
  }
  return  sqrt(soma); 
}

void SOMBracoModular::melhorDistancia(int caracteristicas[SOM_MAX_F], int &melhorL, int &melhorC){
  melhorL = 0;
  melhorC = 0; 
  //Serial.print( " - " ); 
  float melhorDist = distanciaParcial(caracteristicas,melhorL,melhorC,2,3); 
  for(int i=0; i < SOM_MAX_L; i++) {
    for(int j=0; j < SOM_MAX_C; j++) {
      float d = distanciaParcial(caracteristicas,i,j,2,3);
      if(d < melhorDist){
        melhorL = i;
        melhorC = j;
        melhorDist = d;  
      }
    }
  }
}

void SOMBracoModular::melhorResposta(int caracteristicas[SOM_MAX_F], int & A, int & B){
  int melhorLinha=0; 
  int melhorColuna=0; 
  melhorDistancia(caracteristicas,melhorLinha, melhorColuna);

  A = matrizNeuronios[melhorLinha][melhorColuna][0];
  B = matrizNeuronios[melhorLinha][melhorColuna][1];
}
