#include "PickleFLLRobotDriver.c"

task main()
{
	initializeRobot();
	nxtDisplayCenteredTextLine(6, "Hello World");
	while(true){
		motors[aux].power=60;
	}
	driveAndAct(10, 20, 1000, 60, 60);
}
