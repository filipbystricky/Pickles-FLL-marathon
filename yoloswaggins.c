#include "PickleFLLRobotDriver.c"

task main()
{
	initializeRobot();
	displayTextLine(6, "hello world");
	drive(1000, 50);
}
