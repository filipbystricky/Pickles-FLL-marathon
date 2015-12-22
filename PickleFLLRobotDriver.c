#pragma systemFile

/*  This file handles all of the movement operations.  */
void pause()
{
#ifdef PAUSE
	while (nNxtButtonPressed!=3){};
#endif
}

typedef struct
{
	long target, absdifference;
	int power, direction;
	bool divZero;
	float percentComplete;
}myMotor;

#define motorLeft 0
#define motorRight 1
#define motorAux 2

#define left motorA
#define right motorB
#define aux motorC

#define kP (float)0.1
#define kI (float)0
#define kD (float)0

#define threshold 30


bool initializeRobot()
{

	return true;
}
float tan(float theta)
{
	return sinDegrees(theta)/cosDegrees(theta);
}

//Reset all of the encoders.
void reset()
{
	nMotorEncoder[left]=0;
	nMotorEncoder[right]=0;
	return;
}

// This function returns true when all of the wheels have arrived at
//their final encoder value for a specific move
bool bothArrived(long first, long second)
{
	if (abs(first)<threshold&&abs(second)<threshold)
		return true;
	return false;
}

bool auxArrived(long target)
{
	return (abs(target)<threshold);
}

//Given encoder values, find which motor has the farthest distance left
//to turn.
int greatest(long leftEncoder, long rightEncoder) {
	if ((rightEncoder>leftEncoder)) {
		return motorRight;
	}
	else  {
		return motorLeft;
	}
}
int least(long leftEncoder, long rightEncoder) {
	if ((leftEncoder<rightEncoder)) {
		return motorLeft;
	}
	else  {
		return motorRight;
	}
}


//Calculate the power of a motor.  It should be proportional to how far
//it has left to go.
int calcPower(long top, long bottom, int basePower, int direction) {
	return (((float)top*basePower*direction)/(float)bottom);
}
int calcBetterPower(long curDist, long greatestDist,long leastDist, int basePower, int direction) {
	leastDist=(leastDist>2000)?(leastDist-1000):(leastDist/2);
	return ((float)(curDist-leastDist)*basePower*direction)/(float)(greatestDist-leastDist);
}

//Look up the comparison betweeb motors and array indices.
int lookUpComparison(int theMotor)
{
	switch(theMotor)
	{
	case motorLeft:
		return left;
		break;
	case motorRight:
		return right;
		break;
	case motorAux:
		return aux;
		break;
	}
	return -1;
}

void stopMotors() // Stops all motors
{
	motor[right]=0;
	motor[left]=0;
	return;
}

myMotor motors[2];

float atan2(long y,long nx)
{
	return 2*atan(y/(sqrt(nx*nx+y*y)+nx));
}
float absFloat(float input)
{
	return(input>0)?input:-input;
}

//calc the power cap for ramping
int powerCap(int absDif, int encoder)
{
	int rampDown=30+(absDif/10);
	int rampUp=30+abs(encoder)/10;
	return (rampDown>rampUp)?rampUp:rampDown;
}
void moveTestBetter(int power)  //Move the robot an arbitrary distance.  Encoder targets are supplied by the functions that call this one.
{
	reset();
	wait1Msec(50);
	//Initialize
	for (int cnt=0; cnt<2; cnt++)
	{
		motors[cnt].absdifference=abs(motors[cnt].target-nMotorEncoder[lookUpComparison(cnt)]);
		motors[cnt].divZero=false;
		motors[cnt].percentComplete=0.0;
	}
	//Go until the robot has arrived.
	while (!bothArrived(motors[motorRight].absdifference,motors[motorLeft].absdifference))
	{
		clearTimer(T4);
		//Find which motor has the longest distance left to go.
		int greatestValue=greatest(abs(motors[motorLeft].absdifference), abs(motors[motorRight].absdifference));
		int leastValue=least(abs(motors[motorLeft].absdifference), abs(motors[motorRight].absdifference));
		nxtDisplayCenteredTextLine(6, "%d,%d,%d", greatestValue, motors[greatestValue].absdifference, motors[greatestValue].target);
		for (int cnt=0; cnt<2; cnt++)
		{
			motors[cnt].absdifference=abs(motors[cnt].target-nMotorEncoder[lookUpComparison(cnt)]);
			motors[cnt].direction=( motors[cnt].target<nMotorEncoder[lookUpComparison(cnt)])?-1:1;
			motors[cnt].power=calcBetterPower(abs(motors[cnt].absdifference), abs(motors[greatestValue].absdifference), abs(motors[leastValue].absdifference), abs(power), motors[cnt].direction);

			nxtDisplayCenteredTextLine(cnt, "%d,%d,%d", nMotorEncoder[lookUpComparison(cnt)], motors[cnt].absdifference, motors[cnt].target);

			if (motors[cnt].target==0)
			{
				motors[cnt].divZero=true;
			}
			else
			{
				motors[cnt].divZero=false;
				motors[cnt].percentComplete=absFloat(nMotorEncoder[lookUpComparison(cnt)]/(float)motors[cnt].target);
			}

		}
		//Two options-if scale down power cap, then scale down everything proportinally
		//or do it individually.  I'm doing it individually above, but that can change.
		//Or do proportional to how far left + constant*dif from average percent complete
		float averagePercent=0;
		float num=0;
		for (int cnt=0; cnt<2; cnt++)
		{
			if (motors[cnt].divZero==false)
			{
				averagePercent=averagePercent+motors[cnt].percentComplete;
				num=num+1.0;
			}
		}
		averagePercent=averagePercent/(float)num;

		for (int cnt=0; cnt<2; cnt++)
		{
			//we're doing it individually here
			float difference=nMotorEncoder[lookUpComparison(cnt)]-averagePercent*motors[cnt].target;
			int powerAdjust=difference/10;
			//Deactivating powerAdjust-it does not work properly yet
			powerAdjust=0;
			if (motors[cnt].power<0) powerAdjust=powerAdjust*-1;
			motors[cnt].power=motors[cnt].power+powerAdjust;
			if (abs(motors[cnt].power)>powerCap(motors[cnt].absdifference, nMotorEncoder[lookUpComparison(cnt)])) motors[cnt].power=powerCap(motors[cnt].absdifference, nMotorEncoder[lookUpComparison(cnt)])*((motors[cnt].power>0)?1:-1);
			motor[lookUpComparison(cnt)]=motors[cnt].power;
			nxtDisplayCenteredTextLine(cnt+2, "%d", motors[cnt].power);
		}
	}
	stopMotors();
	return;
}

//turn on motors
void turnOnMotors(int pL, int pR)
{
	motor[right]=pR;
	motor[left]=pL;
}

void drive(float y, int motorpower)
{
	motors[motorLeft].target=y;
	motors[motorRight].target=y;
	moveTestBetter(motorpower);
}

void driveAndDump(float distance, float aux, int distmotorpower, int auxmotorpower)
{
	motors[motorLeft].target=distance;
	motors[motorRight].target=distance;
	motors[motorAux].target = aux;
	moveTestBetter(distmotorpower);
}

void turn(float y, int motorPower)
{
	motors[motorLeft].target = y;
	motors[motorRight].target = -y;
	moveTestBetter(motorPower);
}

void auxDump(int motorPower, int amt)
{
	nMotorEncoder[aux] = 0;
	while(nMotorEncoder[aux] < amt)
	{
		motor[aux] = motorPower;
	}
}

/*void moveTest(int power)  //Move the robot an arbitrary distance.  Encoder targets are supplied by the functions that call this one.
{
reset();
wait1Msec(50);
//Initialize
for (int cnt=0; cnt<4; cnt++)
{
motors[cnt].absdifference=abs(motors[cnt].target-nMotorEncoder[lookUpComparison(cnt)]);
motors[cnt].divZero=false;
motors[cnt].percentComplete=0.0;
}
//Go until the robot has arrived.
while (!(motors[mfront].absdifference,motors[mright].absdifference,motors[mleft].absdifference,motors[mback].absdifference))
{
ClearTimer(T4);
//Find which motor has the longest distance left to go.
int greatestValue=greatest(abs(motors[mfront].absdifference),abs(motors[mleft].absdifference), abs(motors[mback].absdifference), abs(motors[mright].absdifference));
nxtDisplayCenteredTextLine(6, "%d,%d,%d", greatestValue, motors[greatestValue].absdifference, motors[greatestValue].target);
for (int cnt=0; cnt<4; cnt++)
{
motors[cnt].absdifference=abs(motors[cnt].target-nMotorEncoder[lookUpComparison(cnt)]);
motors[cnt].direction=( motors[cnt].target<nMotorEncoder[lookUpComparison(cnt)])?-1:1;
motors[cnt].power=calcPower(abs(motors[cnt].absdifference), abs(motors[greatestValue].absdifference),abs(power), motors[cnt].direction);
nxtDisplayCenteredTextLine(cnt, "%d,%d,%d", nMotorEncoder[lookUpComparison(cnt)], motors[cnt].absdifference, motors[cnt].target);

if (motors[cnt].target==0)
{
motors[cnt].divZero=true;
}
else
{
motors[cnt].divZero=false;
motors[cnt].percentComplete=absFloat(nMotorEncoder[lookUpComparison(cnt)]/(float)motors[cnt].target);
}

}
//Two options-if scale down power cap, then scale down everything proportinally
//or do it individually.  I'm doing it individually above, but that can change.
//Or do proportional to how far left + constant*dif from average percent complete
float averagePercent=0;
float num=0;
for (int cnt=0; cnt<4; cnt++)
{
if (motors[cnt].divZero==false)
{
averagePercent=averagePercent+motors[cnt].percentComplete;
num=num+1.0;
}
}
averagePercent=averagePercent/(float)num;

for (int cnt=0; cnt<4; cnt++)
{
//we're doing it individually here
float difference=nMotorEncoder[lookUpComparison(cnt)]-averagePercent*motors[cnt].target;
int powerAdjust=difference/10;
//Deactivating powerAdjust-it does not work properly yet
powerAdjust=0;
if (motors[cnt].power<0) powerAdjust=powerAdjust*-1;
motors[cnt].power=motors[cnt].power+powerAdjust;
if (abs(motors[cnt].power)>powerCap(motors[cnt].absdifference, nMotorEncoder[lookUpComparison(cnt)])) motors[cnt].power=powerCap(motors[cnt].absdifference, nMotorEncoder[lookUpComparison(cnt)])*((motors[cnt].power>0)?1:-1);
motor[lookUpComparison(cnt)]=motors[cnt].power;
}
updateStaggeredPowers();
}
stopMotors();
return;
}*/

//Read/write side data.  Used for telling teleop which side it is on.
/*void writeSide(short isLeft)
{
TFileHandle hFileHandle;
TFileIOResult nIoResult;
short nFileSize = sizeof(isLeft);
Delete(SIDEDATADAT, nIoResult);
OpenWrite(hFileHandle, nIoResult, SIDEDATADAT, nFileSize);
WriteShort(hFileHandle, nIoResult, isLeft);
Close(hFileHandle, nIoResult);
}
short readSide()
{
TFileHandle hFileHandle;
TFileIOResult nIoResult;
short tempVal=0;
short nFileSize = sizeof(tempVal);
OpenRead(hFileHandle, nIoResult, SIDEDATADAT, nFileSize);
ReadShort(hFileHandle, nIoResult, tempVal);
Close(hFileHandle, nIoResult);
return tempVal;
}
*/
//These are various reusable ways
//of setting targets for the motors and thus moving in
//reusable patterns.

/*void weirdDrive(float x, float y, int motorpower)
{
motors[mfront].target=x;
motors[mback].target=x;
motors[mleft].target=y;
motors[mright].target=y+000;
moveTest(motorpower);
}
void rotateAroundFront()
{
motors[mfront].target=0;
motors[mback].target=-3000;
motors[mright].target=-1500;
motors[mleft].target=1500;
moveTest(70);
}
void turn(float turnStuff, int power)
{
motors[mfront].target=turnStuff;
motors[mright].target=-turnStuff;
motors[mback].target=-turnStuff;
motors[mleft].target=turnStuff;
moveTestBetter(power);
}*/
