/** 
 * File:   CommunicationArduino.h
 * Author: oriva
 *
 * Created on 24 de Outubro de 2014, 16:00
 * Basseado na classe TComm.h de Daniel Filgueiras. 
 */

#ifndef SimpleCommArduino_H
#define	SimpleCommArduino_H



#include "SerialPort.h"
#include <iostream>


/** SimpleCommArduino
 * @author Orivaldo a partir de códigos de Daniel Gomes
 * @brief Classe para a comunicação entre o arduino e o 
 * computador. A comunicação é realizada a través da porta serial
 */
class SimpleCommArduino {
protected:
    SerialPort sp; ///< Comunicação com a porta serial 
    unsigned char bufIn[256]; ///< Buffer temporário para manter os dados de obtidos da porta serial 
    unsigned char bufOut[256]; ///< Buffer temporário para manter os dados de saída 
    int sizeIn; ///< Quantidade de caracteres obtidos da serial 
    int deltaT; ///< Tempo mínimo de espera entre dois comandos executados sobre a porta serial 
 
public:
    /**
     * Construtor 
     * @param resetCounterAfterReadFail
     */
    SimpleCommArduino( int resetCounterAfterReadFail);

    ~SimpleCommArduino();

    bool readSensor(char sensorID, std::string& content);
    bool read(std::string &res, int size);
    int write(std::string command); 

    int open();
    int close();


    void setTimeOut(int t);
    void setDelay(int t);

    void initComm();

private:

};
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

bool SimpleCommArduino::read(std::string &res, int size) {
    //res = "xxx"; // resposta da leitura 
    if (sp.isOpen()) {
        sizeIn = size;
        int t = 0;
        int tamBuffer = 25;
        // limpar o buffer 
        for (int i=0; i<tamBuffer; i++) {
           bufIn[i] = 'x'; 
        }
        sp.readPort(bufIn, 25, sizeIn);
        //std::cout << sizeIn << std::endl; 
        if (sizeIn > 0) {
            return true;
            //std::cout <<" --- "; 
            for (int i = 0; i < sizeIn && i<size; i++) {
                // std::cout <<bufIn[i]; 
                res[i] = bufIn[i];     
            }
            //std::cout  <<" --- "; 
        }
    }
    return false;
}

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

#endif	/* COMMUNICATIONARDUINO_H */

