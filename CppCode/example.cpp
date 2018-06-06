#include <iostream>
#include "classes/ModularArm.h"

using namespace std;

int main(int argc, char* argv[])
{
	ModularArm arm;

	

	// double angle[3] = {45,0,0};
	// int type[3] = {1,2,2};
	// double pos[3] = {0,0,0};

	
	// arm.ForwardK(angle,type,3,pos);

	// cout << "X: " << pos[0] << endl;
	// cout << "Y: " << pos[1] << endl;
	// cout << "Z: " << pos[2] << endl;
	
	double val[3] = {90.0,130.0};
	int ind[3] = {1,2};
	
	arm.start(); // Start serial comunication and reset stepper positions by sending the arm to home
	arm.sendMove(180,0); // Move the '0' joint to angle of 180.0 degree
	arm.sendMoveMulti(val, ind, 2); // Move two joints at the same time (works for how many joints u want)
	arm.sendMsg("G28"); // Send a raw msg to the arm (only do that if u know what u doing)
	arm.sendMsgNoWait("G1 A90"); // All methods above have the NoWait similar (it doesn't wait until the movement is complete)

	return 0;
}
