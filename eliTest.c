#include "PickleFLLRobotDriver.c"

task main()
{
	initializeRobot();
	nxtDisplayCenteredTextLine(6, "Hello World");
	//turnRightWheel(800, 40);
	//drive(500, 60);
	driveAndAct(600, 1500, 30, 60, 60);
}
