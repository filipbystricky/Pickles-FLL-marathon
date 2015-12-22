#include "PickleFLLRobotDriver.c"


task main()
{
	drive(-2600, 80);
	turn(400, -80);
	drive(200, 50);
	wallFollowLeft(4000, -80);
//	alignOnLine();
	drive(200, -80);
	auxDump(50, 100);	//power, targ (figure out constant once we try it)
	drive(-2600, 80);
	turn(400, -80);
	drive(300, -80);
	turn(400, -80);
	drive(9000, 80);//haha what is that measure even anyway
	//pick up yellow whatsit
	stopMotors();
}
