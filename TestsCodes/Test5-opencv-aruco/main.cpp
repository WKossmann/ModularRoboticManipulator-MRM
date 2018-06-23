#include "Vision.h"
#include <iostream>
#include <unistd.h>

int main(){
    Vision vision;
    if(vision.start()){ 
        std::cout << "Iniciado  .." << std::endl;
    }else{
        std::cout << "Problema ao iniciar a camera, saindo..." << std::endl;
        return 1;
    }
    double x,y;

    while(1){
        if(vision.getVisualPosition(x,y)){
            std::cout << "X: " << (int)x << " Y: " << (int)y << std::endl;
        }
        cv::waitKey(30);
    }    

    return 0;
}
//G1 A150 B120 C130;