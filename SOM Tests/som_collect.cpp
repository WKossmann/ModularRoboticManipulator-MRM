#include <iostream>
#include <fstream>

#include <unistd.h>
#include "classes/Vision.h"
#include "classes/ModularArm.h"

#define QTD_POINTS 10000

int main(){
    ModularArm arm;
    Vision vision;

    arm.start();
    vision.start();

    //Variaveis:
	double angle[3] = {0,0,0};
	int type[3] = {1,2,2};
	double pos[3] = {0,0,0};
    int joint[3] = {0,1,2};
    bool crescente = false;
    int x=0,y=0;
    // int passointerno=1;
    // int passoexterno=1;
    int points_x[QTD_POINTS], points_y[QTD_POINTS];
    int angle_1[QTD_POINTS], angle_2[QTD_POINTS];
	int cont = 0;

    std::cout << "Colecting, please wait ...." << std::endl;

    for(int i=140;i>=75;i-=3){
        if(crescente){
            for(int j=70;j<=140;j+=3){
                // if(j<85){
                //     passointerno = 1;
                // }else
                // if(j>125){
                //     passointerno = 1;
                // }else passointerno=3;
                angle[1] = i-90;
                angle[2] = j-90;
                arm.ForwardK(angle,type,3,pos);
                if(pos[2] >=7.5 ){
                    // std::cout << cont << " >> B: " << i << " C: " << j << " -> Z: " << pos[2] << std::endl;
                    angle[1]+=90;
                    angle[2]+=90;
                    arm.sendMoveMulti(angle,joint, 3);
                    int tentativas = 0;
                    while(true){
                        if(vision.getVisualPosition(x,y)){
                            points_x[cont] = x;
                            points_y[cont] = y;
                            angle_1[cont] = i;
                            angle_2[cont] = j;
                            cont ++;
                            break;
                        }else{
                            tentativas++;
                            if(tentativas > 10){
                                break;
                            }
                        }
                        // std::cout << cont << " >> B:" << i << " C:" << j << " -> X:" << (int)x << " Y:" << (int)y << std::endl;
                        //myfile << i << " " << j << " " << x << " " << y << std::endl;
                    }
                }   
            }
            crescente = false;
        }else{
            for(int j=140;j>=70;j-=3){
                // if(j<85){
                //     passointerno = 1;
                // }else
                // if(j>125){
                //     passointerno = 1;
                // }else passointerno=5;
                angle[1] = i-90;
                angle[2] = j-90;
                arm.ForwardK(angle,type,3,pos);
                if(pos[2] >=7.5 ){
                    // std::cout <<  cont << " >> B: " << i << " C: " << j << " -> Z: " << pos[2] << std::endl;
                    angle[1]+=90;
                    angle[2]+=90;
                    arm.sendMoveMulti(angle,joint, 3);
                    int tentativas = 0;
                    while(true){
                        if(vision.getVisualPosition(x,y)){
                            points_x[cont] = x;
                            points_y[cont] = y;
                            angle_1[cont] = i;
                            angle_2[cont] = j;
                            cont ++;
                            break;
                        }else{
                            tentativas++;
                            if(tentativas > 10){
                                break;
                            }
                        }
                        // std::cout << cont << " >> B:" << i << " C:" << j << " -> X:" << (int)x << " Y:" << (int)y << std::endl;
                        //myfile << i << " " << j << " " << x << " " << y << std::endl;
                    }
                }
            }
            crescente = true;
        }
        
    }

    //Finalizing
    cv::String diretorioImag = cv::String("images/coleta1.png");
    std::string diretorioDado = cv::String("/home/willian/Documents/tcc/SOM/data/braco_modular_arco.txt");
    
    std::cout << "Quantidade de pontos coletados: " << cont << std::endl;

    //Salvando arquivos:
    std::cout << "Diretorio de dados: " << diretorioDado << std::endl;
    std::ofstream myfile;
    myfile.open(diretorioDado);
    myfile << cont << " " << "4" << std::endl;
    for(int i=0;i<cont;i++){
        myfile << angle_1[i] << " " << angle_2[i] << " " << points_x[i] << " " << points_y[i] << std::endl;
    }
    myfile.close();

    //Salvando imagem:    
    std::cout << "Diretorio de imagem: " << diretorioImag << std::endl;
    vision.showPoints(points_x,points_y,cont, diretorioImag);

    //Retornando para home:
    std::cout << "Retornando braço para posição inicial..." << std::endl;
    arm.sendHome();

    std::cout << "Coleta Finalizada" << std::endl;

    return 0;//
}