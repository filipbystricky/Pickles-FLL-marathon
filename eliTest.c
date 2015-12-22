#include "PickleFLLRobotDriver.c"

task main()
{
	initializeRobot();
	nxtDisplayCenteredTextLine(6, "Hello World");
	drive(1000, 30);
}
