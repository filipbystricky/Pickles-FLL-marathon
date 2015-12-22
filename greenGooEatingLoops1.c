#include "PickleFLLRobotDriver.c"


void wallFollowLeft(float degree, int power)
{
	nMotorEncoder[left] = 0;	//reset encoder value lefts
	while(abs(nMotorEncoder[left]) < degree)
	{
		motor[left] = power;
		motor[right] = (power*4)/5;
	}
}

void wallFollowRight(float degree, int power)
{
	nMotorEncoder[right] = 0;	//reset encoder value lefts
	while(abs(nMotorEncoder[right]) < degree)
	{
		motor[right] = power;
		motor[left] = (power*4)/5;
	}
}

task main()
{
	drive(-2600, 80);
	turn(400, -80);
	drive(200, 50);
	wallFollowLeft(4000, -80);
//	alignOnLine();
	drive(200, -80);
	auxDump(50, 300);	//power, targ (figure out constant once we try it)
	drive(300, -80);
	stopMotors();
}
