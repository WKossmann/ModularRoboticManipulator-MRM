#include <iostream>
#include "serial/SimpleCommArduino.h"

using namespace std;

int main(int argc, char* argv[])
{
	string comando;
	string cmd = "G28;";
	string cmd2 = "G1 A90;";
	string resposta;
	bool chegou = false;
	SimpleCommArduino arduino;
	arduino.open("/dev/ttyUSB0");

	arduino.write(cmd);
	arduino.read(resposta, 3);
	while(!arduino.read(resposta, 1)){
		usleep(10000);
	}
	cout << "FIM"<< endl;
	arduino.write(cmd2);
	arduino.read(resposta, 3);
	while(!arduino.read(resposta, 1)){
		usleep(10000);
	}
	arduino.close();
	cout << "FIM"<< endl;



	return 0;
}
