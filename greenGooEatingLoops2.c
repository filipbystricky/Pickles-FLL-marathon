#include "PickleFLLRobotDriver.c"

task main()
{
	drive(1300, 80);
	//turn(-200, -80);
	drive(1300, 80);
	//alignOnLine();
	drive(-2600, 80);
	//now we just hit the green thing
	drive(200, 50);
	//now we just backed up
	turn(-200, -80);
	drive(-400, 80);
	turn(-200, 80);
	//alignOnLine();
	drive(-400, 80);
	wallFollowLeft(400, -80);
	drive(-400, 80);
	auxDump(50, 300); //I have no idea what the right value here is
	turn(200, 80);
	drive(-400, 80);
	turn(200, 80);
	drive(-400, 80);
	turn(200, 80);
	drive(-2600, 80);
}

