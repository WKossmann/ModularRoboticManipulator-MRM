/**
 * File: ModularArmComm.h
 * Author: Willian Kossmann
 *  
 * Created on 27 October 2018  
 * 
 * Based on SimpleCommArduino.h class made by 
 * Orivaldo Santana
*/

#ifndef ModularArmComm_h
#define ModularArmComm_h

#include "SimpleCommArduino.h"
#include <iostream>

class ModularArmComm
{
public:
    ModularArmComm();
    ~ModularArmComm();

    int init(std::string _port);

    void sendMsgNoWait(std::string _msg);
    void sendMsg(std::string _msg);
    void sendMoveNoWait(double _value, int _joint);
    void sendMove(double _value, int _joint);
    void sendMoveMultiNoWait(double _value[], int _joint[], int size);
    void sendMoveMulti(double _value[], int _joint[], int size);
    void sendHome();

private:

    SimpleCommArduino arduino;

};

// IMPLEMENTATIONS OF METHODS:

ModularArmComm::ModularArmComm(){}
ModularArmComm::~ModularArmComm(){}

int ModularArmComm::init(std::string _port = "/dev/ttyUSB0"){
    int ret = arduino.open(_port);
    sendHome();
    return ret;
}

void ModularArmComm::sendMsgNoWait(std::string _msg){
    std::string discart;
    arduino.read(discart, 4);

    _msg += ";";
    arduino.write(_msg);
}

void ModularArmComm::sendMsg(std::string _msg){
    std::string discart;
    arduino.read(discart, 4);
    
    _msg += ";";
    arduino.write(_msg);
    while(!arduino.read(discart, 1));
}

void ModularArmComm::sendMoveNoWait(double _value, int _joint){
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

void ModularArmComm::sendMove(double _value, int _joint){
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

void ModularArmComm::sendMoveMultiNoWait(double _value[], int _joint[], int size){
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

void ModularArmComm::sendMoveMulti(double _value[], int _joint[], int size){
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

void ModularArmComm::sendHome(){
    std::string discart;
    arduino.read(discart, 4);

    sendMsg("G28");   
}



#endif
