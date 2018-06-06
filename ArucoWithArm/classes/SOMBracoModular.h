
#ifndef SOMARDINO_H
#define SOMARDINO_H

#define SOM_MAX_L 6
#define SOM_MAX_C 6
#define SOM_MAX_F 4 
#include <cmath>

class SOMBracoModular
{
  public:
    SOMBracoModular( );
    void setup();
    void melhorDistancia(int caracteristicas[SOM_MAX_F], int &melhorL, int &melhorC);
    float distanciaParcial(int caracteristicas[SOM_MAX_F], int i, int j, int min, int max); 
    char getLabel(int i, int j); 
    void melhorResposta(int caracteristicas[SOM_MAX_F], int & A, int & B);
 

  private:
    int matrizNeuronios[SOM_MAX_L][SOM_MAX_C][SOM_MAX_F] = 
{
 { {139, 135, 223, 82},  {139, 129, 223, 97},  {139, 124, 224, 113},  {139, 119, 226, 130},  {139, 115, 228, 139},  {139, 113, 230, 147} },
 { {139, 130, 225, 97},  {139, 126, 225, 107},  {139, 121, 226, 121},  {139, 115, 229, 141},  {139, 112, 232, 149},  {139, 108, 235, 160} },
 { {139, 118, 233, 130},  {139, 116, 233, 135},  {139, 115, 232, 140},  {139, 110, 234, 154},  {139, 108, 235, 159},  {139, 104, 239, 169} },
 { {139, 99, 247, 180},  {139, 97, 251, 186},  {139, 95, 255, 189},  {139, 94, 257, 192},  {139, 94, 257, 192},  {139, 94, 255, 192} },
 { {139, 92, 255, 197},  {139, 90, 260, 202},  {139, 88, 265, 206},  {139, 86, 270, 210},  {139, 84, 273, 212},  {139, 85, 273, 211} },
 { {138, 90, 256, 199},  {139, 87, 265, 208},  {139, 84, 271, 215},  {139, 80, 280, 223},  {139, 77, 287, 229},  {139, 74, 294, 233} }
}; 

  
}; 




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
 
#endif
