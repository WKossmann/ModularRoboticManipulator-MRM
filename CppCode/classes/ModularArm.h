/**
 * File: ModularArm.h
 * Author: Willian Kossmann
 *  
 * Created on 27 October 2018  
 * 
 * Based on SimpleCommArduino.h class made by 
 * Orivaldo Santana
*/

#ifndef ModularArm_h
#define ModularArm_h

#include "SimpleCommArduino.h"
#include <iostream>

class ModularArm
{
public:
    ModularArm();
    ~ModularArm();

    int init(std::string _port);

    void sendMsgNoWait(std::string _msg);
    void sendMsg(std::string _msg);
    void sendMoveNoWait(double _value, int _joint);
    void sendMove(double _value, int _joint);
    void sendMoveMultiNoWait(double _value[], int _joint[], int size);
    void sendMoveMulti(double _value[], int _joint[], int size);
    void sendHome();

    void jointT1FowardK(double rad, double mat[4][4]);
    void jointT2FowardK(double rad, double mat[4][4]);

private:

    SimpleCommArduino arduino;

};

// IMPLEMENTATIONS OF METHODS:

ModularArm::ModularArm(){}
ModularArm::~ModularArm(){}

int ModularArm::init(std::string _port = "/dev/ttyUSB0"){
    int ret = arduino.open(_port);
    sendHome();
    return ret;
}

void ModularArm::sendMsgNoWait(std::string _msg){
    std::string discart;
    arduino.read(discart, 4);

    _msg += ";";
    arduino.write(_msg);
}

void ModularArm::sendMsg(std::string _msg){
    std::string discart;
    arduino.read(discart, 4);
    
    _msg += ";";
    arduino.write(_msg);
    while(!arduino.read(discart, 1));
}

void ModularArm::sendMoveNoWait(double _value, int _joint){
    std::string discart;
    char joint;
    arduino.read(discart, 4);

    std::string msg = "G1 ";
    joint = (char)((int)'A' + _joint);
    msg += joint;
    msg += std::to_string(_value);

    msg += ";";
    arduino.write(msg);
}

void ModularArm::sendMove(double _value, int _joint){
    std::string discart;
    char joint;
    arduino.read(discart, 4);
    
    std::string msg = "G1 ";
    joint = (char)((int)'A' + _joint);
    msg += joint;
    msg += std::to_string(_value);

    msg += ";";
    arduino.write(msg);
    while(!arduino.read(discart, 2));
}

void ModularArm::sendMoveMultiNoWait(double _value[], int _joint[], int size){
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
}

void ModularArm::sendMoveMulti(double _value[], int _joint[], int size){
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
    while(!arduino.read(discart, 2));
}

void ModularArm::sendHome(){
    std::string discart;
    arduino.read(discart, 4);

    sendMsg("G28");   
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


#endif
