#pragma config(Sensor, S1,     leftLight,      sensorLightActive)
#pragma config(Sensor, S2,     rightLight,     sensorLightActive)
#pragma config(Motor,  motorA,          motorAux,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorRight,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          motorLeft,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "PickleFLLRobotDriver.c"



task main()
{
	drive(-2600, 80);
	turn(-400, 80);
	drive(600, 50);
	wallFollowRight(4500, -80);
	drive(1500, 80);
	auxDump(50, 75);
	drive(2200, 80);
	turn(-400, 80);
	drive(600, 50);
	drive(-2000, 80);
//	drive(-1000, 80);
	/*
	turn(400, -80);
	drive(300, -80);
	turn(400, -80);*/
	stopMotors();
}