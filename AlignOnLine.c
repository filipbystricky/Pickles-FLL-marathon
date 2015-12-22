#include "PickleFLLLightDriver.c"

#define blackThreshold 10

void alignOnLine(int power) {
	motor[left]=power;
	motor[right]=power;
	int leftCount = 0;
	int rightCount = 0;
	bool leftFound = false;
	bool rightFound = false;
	while(1)
	{
		//nxtDisplayCenteredTextLine(0, "%d %d", CSvalNorm(leftLight), CSvalRaw(leftLight));
		//nxtDisplayCenteredTextLine(1, "%d %d", CSvalNorm(rightLight), CSvalRaw(rightLight));

		if (LSvalNorm(leftLight) < blackThreshold)
		{
			motor[left] = 0;
			leftFound = true;
			motor[right] = (rightFound?0:power/2);
		}
		if (LSvalNorm(rightLight) < blackThreshold)
		{
			motor[right] = 0;
			rightFound = true;
			motor[left]= (leftFound?0:power/2);
		}
		if (rightFound && leftFound) {
		//			nxtDisplayCenteredTextLine(0, "%d %d", CSvalNorm(leftLight), CSvalRaw(leftLight));
		//nxtDisplayCenteredTextLine(1, "%d %d", CSvalNorm(rightLight), CSvalRaw(rightLight));

			//while(1);
			return;
		}

	}
}
