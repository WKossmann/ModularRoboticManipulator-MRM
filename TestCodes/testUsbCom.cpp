#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	//open arduino device file (linux)
    ofstream arduino;
	arduino.open( "/dev/ttyUSB0");

	//write to it
    arduino << "G28;";
    
	arduino.close();

	arduino.open( "/dev/ttyUSB0");

	//write to it
    arduino << "G1 A180;";
    
	arduino.close();

	ifstream leitura;
	leitura.open("/dev/ttyUSB0");

	char x[300];
	leitura >> x;

	cout << x;

	leitura.close();

	return 0;
}