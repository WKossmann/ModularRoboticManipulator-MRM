/**
 * File: ModularArm.h
 * Author: Willian Kossmann
 *  
 * Created on 27 October 2018  
 * 
 * Based on SimpleCommArduino.h class made by Orivaldo Santana
*/

#ifndef ModularArm_h
#define ModularArm_h

#include "include/SimpleCommArduino.h"
#include <iostream>
#include <cmath>

#define J2_A 9.5
#define J2_B 9.5
#define J1_H 7.6
#define NO_WAIT false

class ModularArm
{
public:
    ModularArm();
    ~ModularArm();
    int start(std::string _port);
    //Comunication:
    void sendMsg(std::string _msg, bool _waitFlag);
    void sendMove(double _value, int _joint, bool _waitFlag);
    void sendMoveMulti(double _value[], int _joint[], int size, bool _waitFlag);
    void sendHome();
    void sendHome(int _joint[], int _size);
    //Kinematics functions:
    void multiMatrix(double A[4][4], double B[4][4], double R[4][4]);
    void jointT1FowardK(double rad, double mat[4][4]);
    void jointT2FowardK(double rad, double mat[4][4]);
    void ForwardK(double angles[], int type[], int size, double pos[3]);
private:
    SimpleCommArduino arduino;
};
ModularArm::ModularArm(){}
ModularArm::~ModularArm(){}

int ModularArm::start(std::string _port = "/dev/ttyUSB0"){
    int ret = arduino.open(_port);
    sendHome();
    return ret;
}

void ModularArm::sendMsg(std::string _msg, bool _waitFlag = true){
    std::string discart;
    arduino.read(discart, 4);
    
    _msg += ";";
    arduino.write(_msg);
    if(_waitFlag){
        while(!arduino.read(discart, 1));
    }
}

void ModularArm::sendMove(double _value, int _joint, bool _waitFlag = true){
    std::string discart;
    char joint;
    arduino.read(discart, 4);
    
    std::string msg = "G1 ";
    joint = (char)((int)'A' + _joint);
    msg += joint;
    msg += std::to_string(_value);

    msg += ";";
    arduino.write(msg);
    if(_waitFlag){
        while(!arduino.read(discart, 1));
    }
}

void ModularArm::sendMoveMulti(double _value[], int _joint[], int size, bool _waitFlag = true){
    std::string discart;
    char joint;
    arduino.read(discart, 4);
    
    std::string msg = "G1 ";
    for(int i=0;i<size;i++){
        joint = (char)((int)'A' + _joint[i]);
        msg += joint;
        msg += std::to_string(_value[i]);
        msg += " ";
    }

    msg += ";";
    arduino.write(msg);
    if(_waitFlag){
        while(!arduino.read(discart, 1));
    }
}

void ModularArm::sendHome(){
    std::string discart;
    arduino.read(discart, 4);

    sendMsg("G28");   
}

void ModularArm::sendHome(int _joint[], int size){
    std::string discart;
    char joint;
    arduino.read(discart, 4);

    std::string msg = "G28 ";
    for(int i=0;i<size;i++){
        joint = (char)((int)'A' + _joint[i]);
        msg += joint;
        msg += " ";
    }
    msg += ";";
    arduino.write(msg);
    while(!arduino.read(discart, 1));
}

void ModularArm::multiMatrix(double A[4][4], double B[4][4], double R[4][4]){
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            R[i][j] = 0;
            for(int k = 0; k < 4; ++k)
            {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void ModularArm::jointT1FowardK(double rad, double mat[4][4]){
    //First Collum
    mat[0][0] = cos(rad);
    mat[1][0] = sin(rad);
    mat[2][0] = 0;
    mat[3][0] = 0;
    //Second Collum
    mat[0][1] = -sin(rad);
    mat[1][1] = cos(rad);
    mat[2][1] = 0;
    mat[3][1] = 0;
    //Third Collum
    mat[0][2] = 0;
    mat[1][2] = 0;
    mat[2][2] = 1;
    mat[3][2] = 0;
    //Fourth Collum
    mat[0][3] = 0;
    mat[1][3] = 0;
    mat[2][3] = J1_H;
    mat[3][3] = 1;
}

void ModularArm::jointT2FowardK(double rad, double mat[4][4]){
    //First Collum
    mat[0][0] = sin(rad);
    mat[1][0] = 0;
    mat[2][0] = -cos(rad);
    mat[3][0] = 0;
    //Second Collum
    mat[0][1] = 0;
    mat[1][1] = 1;
    mat[2][1] = -1;
    mat[3][1] = 0;
    //Third Collum
    mat[0][2] = cos(rad);
    mat[1][2] = 0;
    mat[2][2] = sin(rad);
    mat[3][2] = 0;
    //Fourth Collum
    mat[0][3] = J2_B*cos(rad);
    mat[1][3] = 0;
    mat[2][3] = J2_A + J2_B*sin(rad);
    mat[3][3] = 1;
}

void ModularArm::ForwardK(double angles[], int type[], int size, double pos[3]){
    double  T[4][4];
    double  R[4][4];
    double RT[4][4];
    double  I[4][4] = { {1,0,0,0},
                        {0,1,0,0},
                        {0,0,1,0},
                        {0,0,0,1}   };

    for(int i=0;i<size;i++){
        switch(type[i]){
            case 1:
                jointT1FowardK(angles[i]*M_PI/180.0, T);                
            break;
            case 2:
                jointT2FowardK(angles[i]*M_PI/180.0, T);
            break;
            default:
                // return -1;
            break;
        }
        if(i==0){
            multiMatrix(I,T,R);
        }else{
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    RT[i][j] = R[i][j];
                }
            }
            multiMatrix(RT,T,R);
        }
    }

    pos[0] = R[0][3];
    pos[1] = R[1][3];
    pos[2] = R[2][3];
}

#endif
