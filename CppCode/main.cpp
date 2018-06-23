#include <iostream>
#include "classes/ModularArm.h"

using namespace std;

int main(int argc, char* argv[])
{
	ModularArm arm;	
	arm.start(); // Start serial comunication and reset stepper positions by sending the arm to home FOTO 9
	// arm.sendMove(90,0);

	// arm.sendMove(180,0); // Move the '0' joint to angle of 180.0 degree FOTO 10 (90)
	
	// double val[2] = {90.0,130.0};
	// int ind[2] = {1,2};
	// arm.sendMoveMulti(val, ind, 2); // Move two joints at the same time (works for how many joints u want) FOTO 11
	
	// int ind2[1] = {0};
	// arm.sendHome(ind2,1); // Send a raw msg to the arm (only do that if u know what u doing) FOTO 12
	// arm.sendMove(90,0);

	// arm.sendMsg("G1 A180", NO_WAIT); // All methods above have the NoWait similar (it doesn't wait until the movement is complete) FOTO 13

	double angle[3] = {45, 0, 0};
	int type[3] = {1,2,2};
	double pos[3];

	arm.ForwardK(angle,type,3,pos);

	cout << "X: " << pos[0] << endl;
	cout << "Y: " << pos[1] << endl;
	cout << "Z: " << pos[2] << endl;
	
	return 0;
}
