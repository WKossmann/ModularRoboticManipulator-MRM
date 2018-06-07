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
	double angle[3] = {0,0,0};
	int type[3] = {1,2,2};
	double pos[3] = {0,0,0};
    int joint[3] = {0,1,2};
    bool crescente = false;
    double x=0,y=0;
    int passointerno=1;
    int passoexterno=1;
	
	int cont = 0;

    for(int i=140;i>=70;i-=1){
        if(crescente){
            for(int j=70;j<=140;j+=passointerno){
                if(j<85){
                    passointerno = 1;
                }else
                if(j>125){
                    passointerno = 1;
                }else passointerno=3;
                angle[1] = i-90;
                angle[2] = j-90;
                arm.ForwardK(angle,type,3,pos);
                if(pos[2] >=7.5 ){
                    // std::cout << cont << " >> B: " << i << " C: " << j << " -> Z: " << pos[2] << std::endl;
                    cont ++;
                    angle[1]+=90;
                    angle[2]+=90;
                    arm.sendMoveMulti(angle,joint, 3);
                    vision.getVisualPosition(x,y);
                    // std::cout << cont << " >> B:" << i << " C:" << j << " -> X:" << (int)x << " Y:" << (int)y << std::endl;
                    std::cout << i << " " << j << " " << (int)x << " " << (int)y << std::endl;
                }   
            }
            crescente = false;
        }else{
            for(int j=140;j>=70;j-=passointerno){
                if(j<85){
                    passointerno = 1;
                }else
                if(j>125){
                    passointerno = 1;
                }else passointerno=5;
                angle[1] = i-90;
                angle[2] = j-90;
                arm.ForwardK(angle,type,3,pos);
                if(pos[2] >=7.5 ){
                    // std::cout <<  cont << " >> B: " << i << " C: " << j << " -> Z: " << pos[2] << std::endl;
                    cont ++;
                    angle[1]+=90;
                    angle[2]+=90;
                    arm.sendMoveMulti(angle,joint, 3);
                    vision.getVisualPosition(x,y);
                    std::cout << i << " " << j << " " << (int)x << " " << (int)y << std::endl;
                }
            }
            crescente = true;
        }
    }
    std::cout << "Cont: " << cont << std::endl;




    //TODO : Salvar em arquivo

    return 0;
}