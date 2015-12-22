#include "PickleFLLRobotDriver.c"

task main()
{
	while (initializeRobot()){
		displayTextLine(6, "hello world");
	}
}
