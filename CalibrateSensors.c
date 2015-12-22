#include "PickleFLLLightDriver.c"
#include "PickleFLLColorDriver.c"

void calibrateLightSensor(tSensors link) {
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "LOW VAL: %d", LSvalRaw(link);
	}
	LScalLow(link);
	wait1Msec(1000);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "HIGH VAL: %d", LSvalRaw(link);
	}
	LScalHigh(link);
	wait1Msec(1000);
}

void calibrateColorSensor(tSensors link)
{
	CSsetColor(link, RED);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "LOW VAL: %d", CSvalRaw(link));
	}
	CScalLow(link);
	while (nNxtButtonPressed == 3);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "HIGH VAL: %d", CSvalRaw(link));
	}
	CScalHigh(link);
	while (nNxtButtonPressed == 3);

	CSsetColor(link, BLUE);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "LOW VAL: %d", CSvalRaw(link));
	}
	CScalLow(link);
	while (nNxtButtonPressed == 3);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "HIGH VAL: %d", CSvalRaw(link));
	}
	CScalHigh(link);
	while (nNxtButtonPressed == 3);

	CSsetColor(link, GREEN);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "LOW VAL: %d", CSvalRaw(link));
	}
	CScalLow(link);
	while (nNxtButtonPressed == 3);
	while (nNxtButtonPressed != 3) {
		nxtDisplayCenteredTextLine(2, "HIGH VAL: %d", CSvalRaw(link));
	}
	CScalHigh(link);
	while (nNxtButtonPressed == 3);
}
