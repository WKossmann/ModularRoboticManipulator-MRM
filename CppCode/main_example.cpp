#include <iostream>
#include "serial/ModularArmComm.h"


int main(int argc, char* argv[])
{
	double val[2] = {90.0,130.0};
	int ind[2] = {0,1};

	ModularArmComm arm;
	arm.init(); // Start serial comunication and reset stepper positions by sending the arm to home
	arm.sendMove(180,0); // Move the '0' joint to angle of 180.0 degree
	arm.sendMoveMulti(val, ind, 2); // Move two joints at the same time 
	arm.sendMsg("G28"); // Send a raw msg to the arm (only do that if u know what u doing)
	arm.sendMsgNoWait("G1 A90"); // All methods above have the NoWait similar (it doesn't wait until the movement is complete)

	return 0;
}
