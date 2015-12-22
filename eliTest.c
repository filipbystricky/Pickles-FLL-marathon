#include "PickleFLLRobotDriver.c"

task main()
{
	initializeRobot();
	nxtDisplayCenteredTextLine(6, "Hello World");
	driveAndAct(10, 50, 1000, 60, 60);
}
