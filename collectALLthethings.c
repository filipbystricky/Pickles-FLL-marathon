#pragma config(Sensor, S1,     rightLight,     sensorColorNxtFULL)
#pragma config(Sensor, S2,     leftLight,      sensorColorNxtFULL)
#pragma config(Motor,  motorA,          aux,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          right,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,           tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "PickleFLLRobotDriver.c"

#include "AlignOnLine.c"
task main() {
	//drive(4200, 100);
//drive(4600,100);
drive(2250, 100);
alignOnLineColor(40);
drive(1400, 100);
//drive(4000, 100);
turn(300, 60);
drive(850, 60);
alignOnLineColor(-40);
drive(-480, 60);
turn(-350, 60);
drive(700, 60); //HIt the button
//drive(1800, 100)
//alignOnLine(60);
//drive(2000, 60);
	drive(-600, 60);
	turn(210, 60);
	drive(1100, 70);
	turn(200, 60);
	alignOnLineColor(-40);
	drive(300, 60);
	turn(340, 60);
	drive (-1000, 40);//windshield
	drive (-50, 30);
	drive(1000, 40); 		//this line and line above changed from 600 to 900
	//driveAndAct(60, 0, 0, 0, 10);
	//wait1Msec(100);
	//driveAndAct(40, 0, 0, 0, 10);
	//drive(100, 60);
	turn(-320, 80);
	motor[left] = 100;
	motor[right] = 100;
	wait1Msec(2000);
	stopMotors();/**/ //Aligned to wall
	drive(-200, 60);
	turn(330, 70);
	drive(-600, 80);
	motor[aux] = 30;
	wait1Msec(600);
	motor[aux] = 0;
	//driveAndAct(90, 0, 0, 0, 10);
	drive(575, 60); 	//back up
	turn(-300, 70);
	motor[left] = 100;
	motor[right] = 100;
	wait1Msec(500);
	stopMotors();
	drive(-1000, 100);
	alignOnLineColor(-40);
	drive(100, 50);
	// C is for cookie
	turn(360, 60);
	drive(800, 60);
	motor[left] = 40;
	motor[right] = 40;
	while(SensorValue[leftLight] != 1);
	stopMotors();
	turn(-240, 40);	//trying to turn 90deg towards south wall
	nMotorEncoder[aux] = 0;
	while (nMotorEncoder[aux] > -60) {
		motor[aux] = -30;
	}
	drive(-1100, 75);
	driveAndAct(88, 0, 0, 0, 30);
	drive(150, 40);
	turn(280, 40);
	nMotorEncoder[aux] = 0;
	while (nMotorEncoder[aux] > -20) {
		motor[aux] = -30;
	}
	motor[aux] = 0;
	drive(-250, 75);
	motor[aux] = 30;
	wait1Msec(400);
	motor[aux]= 0;
	drive(400, 40);
	//driveAndAct(88, 0, 0, 0, 30);
	turn(-100, 40);
	/*
	nMotorEncoder[aux] = 0;
	while (nMotorEncoder[aux] > -40) {
		motor[aux] = -30;
	}
	stopMotors();
	drive(-550, 60);


	//driveAndAct(-100, 0, 0, 0, -30);
//	drive(-700, 60);
//	turn(330, 60);
//	drive(700, 60);
 	driveAndAct(88, 0, 0, 0, 30);*/
 	stopMotors();


 	drive(3000, 80);
 	turn(200, 80);
 	drive(2000, 100);
 	/*turn(650, 50);
 	nMotorEncoder[aux] = 0;
	while (nMotorEncoder[aux] > -90) {
		motor[aux] = -30;
	}
	motor[aux] = 0;


 	alignOnLineColor(-40);

 	motor[aux] = 30;
	wait1Msec(400);
	motor[aux]= 0;
	drive(400, 80);
	turn(-200, 60);
	drive(-700, 50);
	turn(400, 60);
	drive(-700, 80);*/


}
