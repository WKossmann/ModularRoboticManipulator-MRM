#include <iostream>
#include <unistd.h>
#include "classes/Vision.h"
#include "classes/ModularArm.h"

int main(){
    ModularArm arm;
    Vision vision;

    arm.start();
    vision.start();

    //Definir angulacao:
    double val[5][2] = {    {90.0 ,130.0},
                            {100.0,120.0},
                            {110.0,110.0},
                            {120.0,100.0},
                            {130.0, 90.0}};
	double x[5];
    double y[5];
    int ind[2] = {1,2};

    for(int i=0;i<5;i++){
        arm.sendMoveMulti(val[i], ind, 2);
        sleep(1);
        vision.getVisualPosition(x[i],y[i]);
        std::cout << "X: " << x[i] << " Y: " << y[i] << std::endl; 
    }

    //TODO : Salvar em arquivo

    return 0;
}