/* 
 * File:   CommunicationArduino.cpp
 * Author: oriva
 * 
 * Created on 24 de Outubro de 2014, 16:00
 */

#include "SimpleCommArduino.h"
#include <exception>


SimpleCommArduino::SimpleCommArduino(int resetCounterAfterReadFail) {

    deltaT = 1000; //Tempo em microsegunndos 
 
}

SimpleCommArduino::~SimpleCommArduino() {
 
}

bool SimpleCommArduino::readSensor(char sensorID, std::string& content) {
    if (sp.isOpen()) {
        sizeIn = 0;
        using namespace std;
        int t = 0;
        bufOut[0] = '#';// comando de leitura do Sensor 
        sp.writePort(bufOut, 1);
        usleep(deltaT);
        sp.readPort(bufIn, 255, sizeIn);
        std::cout << sizeIn << std::endl; 
        std::cout <<" ("; 
        for (int i = 0; i < sizeIn; i++) {
            std::cout <<bufIn[i]; 
        }
        std::cout  <<") " << std::endl; 
        return true; 
    }
    return false; 
}

int SimpleCommArduino::open() {
    //int ret = sp.openPort("/dev/rfcomm0");
    int ret = -1;
    try {
        ret = sp.openPort("/dev/ttyUSB0");
        if (ret > 0)
            sp.set(B9600);
        usleep(1000);
        initComm();
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    return ret;
}

void SimpleCommArduino::read(std::string &res, int size) {
    //res = "xxx"; // resposta da leitura 
    if (sp.isOpen()) {
        sizeIn = size;
        int t = 0;
        int tamBuffer = 25;
        // limpar o buffer 
        //for (int i=0; i<tamBuffer; i++) {
        //    bufIn[i] = 'x'; 
        //}
        usleep(deltaT);
        sp.readPort(bufIn, 25, sizeIn);
        //std::cout << sizeIn << std::endl; 
        if (sizeIn > 0) {
            //std::cout <<" --- "; 
            for (int i = 0; i < sizeIn && i<size; i++) {
                //std::cout <<bufIn[i]; 
                res[i] = bufIn[i];     
            }
            //std::cout  <<" --- "; 
        }
    }
};

int SimpleCommArduino::write(std::string command) {
    int size;
    for (size=0; size<command.size(); size++)
        bufOut[size] = command[size];
    sp.writePort(bufOut, size);
    return 0; 
}

 
void SimpleCommArduino::initComm() {
    if (sp.isOpen()) {
        sp.readPort(bufIn, 255, sizeIn);
    }
}

int SimpleCommArduino::close() {
    sp.closePort();
    return 0;
}
 

void SimpleCommArduino::setDelay(int t) {
    deltaT = t;
}

