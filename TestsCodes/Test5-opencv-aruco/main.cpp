#include "Vision.h"
#include <iostream>
#include <unistd.h>

int main(){
    Vision vision;
    if(vision.start()){ 
        std::cout << "Started  .." << std::endl;
    }else{
        std::cout << "Deu ruim .." << std::endl;
        return 1;
    }
    double x,y;

    while(1){
        if(vision.getVisualPosition(x,y)){
            // std::cout << "X: " << (int)x << " Y: " << (int)y << std::endl;
        }//
        cv::waitKey(30);
    }    

    return 0;
}