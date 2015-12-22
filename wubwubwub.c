#pragma config(Sensor, S1,     rightLight,     sensorColorNxtFULL)
#pragma config(Sensor, S2,     leftLight,      sensorColorNxtFULL)
#pragma config(Motor,  motorA,          aux,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          right,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,           tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "PickleFLLRobotDriver.c"

#include "AlignOnLine.c"
task main() {
	drive(-1900, 80);
		motor[aux] = 30;
		wait1Msec(600);
		drive(1500, 80);
		motor[aux] = -40;
		wait1Msec(600);
		motor[aux]=0;
		wait1Msec(400);

	for (int i = 0; i>=0; i++) {
		drive(-1200, 80);
		motor[aux] = 30;
		wait1Msec(600);
		drive(1200, 80);
		motor[aux] = -40;
		wait1Msec(600);
		motor[aux]=0;
		wait1Msec(500);
	}

}
