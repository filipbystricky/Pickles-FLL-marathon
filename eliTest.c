#include "PickleFLLRobotDriver.c"

task main()
{
	initializeRobot();
	nxtDisplayCenteredTextLine(6, "Hello World");
	while(true){
		motor[left] = 100;
	}
}
