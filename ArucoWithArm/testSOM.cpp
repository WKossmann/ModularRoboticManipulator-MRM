#include <iostream>
#include <unistd.h>
#include "classes/Vision.h"
#include "classes/ModularArm.h"
#include "classes/SOMBracoModular.h"

int main(){
    ModularArm arm;
    Vision vision;

    arm.start();
    vision.start();

    SOMBracoModular som;

    int amostra[4] = {0,0,230,150};
    std::cout << "ALVO:  " << amostra[2] << " " << amostra[3] << std::endl;

    int angle[2];
    double angledouble[2];
    int joint[2] = {1,2};


    som.melhorResposta(amostra,angle[0],angle[1]);
    angledouble[0] = (double)angle[0];
    angledouble[1] = (double)angle[1];

    std::cout << "ANGULO SOM:   " << angledouble[0] << " " << angledouble[1] << std::endl;

    arm.sendMoveMulti(angledouble, joint, 2);

    double x,y;
    vision.getVisualPosition(x,y);

    std::cout << "IMAGE: " << x << " " << y << std::endl; 

    //TODO : Salvar em arquivo

    return 0;
}