/** 
 * File:   CommunicationArduino.h
 * Author: oriva
 * Adaptations: Willian K.S. (27/05/2018)
 *
 * Created on 24 de Outubro de 2014, 16:00
 * Basseado na classe TComm.h de Daniel Filgueiras. 
 */

#ifndef SimpleCommArduino_h
#define	SimpleCommArduino_h

#include <iostream>
#include <exception>
#include "SerialPort.h"


/** SimpleCommArduino
 * @author Orivaldo a partir de códigos de Daniel Gomes
 * @brief Classe para a comunicação entre o arduino e o 
 * computador. A comunicação é realizada a través da porta serial
 */
class SimpleCommArduino{
protected:
    SerialPort sp; ///< Comunicação com a porta serial 
    unsigned char bufIn[256]; ///< Buffer temporário para manter os dados de obtidos da porta serial 
    unsigned char bufOut[256]; ///< Buffer temporário para manter os dados de saída 
    int sizeIn; ///< Quantidade de caracteres obtidos da serial
public:
    SimpleCommArduino();

    ~SimpleCommArduino();

    bool read(std::string &res, int size);
    int write(std::string command); 

    int open(std::string comm_Port);
    int close();
    
    void initComm();

private:

};

SimpleCommArduino::SimpleCommArduino() { 
}

SimpleCommArduino::~SimpleCommArduino() {
    sp.closePort();
}

int SimpleCommArduino::open(std::string comm_Port) {
    int ret = -1;
    try {
        ret = sp.openPort(comm_Port);
        if (ret > 0)
            sp.set(B9600);
        initComm();
        return 0;
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
        return -1;
    }
}

bool SimpleCommArduino::read(std::string &res, int size) {
    if (sp.isOpen()) {
        sizeIn = size;
        int tamBuffer = 25;

        // limpar o buffer 
        for (int i=0; i<tamBuffer; i++) {
           bufIn[i] = 'x'; 
        }

        sp.readPort(bufIn, 25, sizeIn); //Faz a leitura

        //Se houver qualquer coisa na serial ja eh o suficiente pra saber que o arduino respondeu
        if (sizeIn > 0) {
            return true;
        }
    }
    return false;
}

int SimpleCommArduino::write(std::string command) {
    unsigned int size;{
		// usleep(10000);
	}
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


#endif
