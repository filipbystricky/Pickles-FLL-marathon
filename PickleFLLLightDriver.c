#ifndef __LEGOLS_H__
#define __LEGOLS_H__
//Based on Xander Soldaat's Light Sensor Driver
//Unused overloaded functions removed to lower the likelihood
//of crossing the 160 function limit.
//This can calibrate light sensors connected in any manner to the NXT.
#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif
#define PORT1 0
#define PORT2 4
#define PORT3 8
#define PORT4 12

// Globals
//Stores whether or not a sensor has been calibrated
bool calibrated[4]={false,false,false,false};
//Calibration Data
int lows[4]={0,0,0,0};
int highs[4]={1023,1023,1023,1023};
//Calibration Data Files
const string dataFiles[4]={"zero.dat","one.dat","two.dat","three.dat"};

//Set the light sensors to be in active mode

void LSsetActive(tSensors link) {
  SensorType[link] = sensorLightActive;
  SensorMode[link] = modeRaw;
  wait1Msec(5);
  nxtDisplayTextLine(3, "SET ACTIVE %d", SensorType[link]);
}

//Set the light sensors to be in inactive mode

void LSsetInactive(tSensors link) {
  SensorType[link] = sensorLightInactive;
  SensorMode[link] = modeRaw;
  wait1Msec(5);
}

//Return an index to the array of data
int lookUpSensorLINK(tSensors link)
{
  switch (link)
  {
    case S1:
      return PORT1;
      break;
    case S2:
      return PORT2;
      break;
    case S3:
      return PORT3;
      break;
    case S4:
      return PORT4;
      break;
    default:
      nxtDisplayCenteredTextLine(2,"Invalid SensorPort");
      wait1Msec(5000);
      stopAllTasks();
      return -1;
  }
}

void _LSwriteCalVals(int curSensor) {
  TFileHandle hFileHandle;
  TFileIOResult nIoResult;
  short nFileSize = 4;
  //Open the file
  Delete(dataFiles[curSensor],nIoResult);
  OpenWrite(hFileHandle, nIoResult, dataFiles[curSensor], nFileSize);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    eraseDisplay();
    nxtDisplayTextLine(3, "W:can't cal file");
    playSound(soundException);
    while(bSoundActive) ;
    wait1Msec(5000);
    stopAllTasks();
  }

  // Write the low calibration value
  WriteShort(hFileHandle, nIoResult, lows[curSensor]);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "can't write lowval");
    playSound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    stopAllTasks();
  }

  // Write the high calibration value
  WriteShort(hFileHandle, nIoResult, highs[curSensor]);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "can't write highval");
    playSound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    stopAllTasks();
  }

  // Close the file
  Close(hFileHandle, nIoResult);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "Can't close");
    playSound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    stopAllTasks();
  }
}

void _LSreadCalVals(int sensorNum) {
  TFileHandle hFileHandle;
  TFileIOResult nIoResult;
  short nFileSize;

  short lv = 0;
  short hv = 0;

  // Open the data file for reading
  calibrated[sensorNum]=true;
  OpenRead(hFileHandle, nIoResult, dataFiles[sensorNum],nFileSize);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the low calibration value
  ReadShort(hFileHandle, nIoResult, lv);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the high calibration value
  ReadShort(hFileHandle, nIoResult, hv);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Assign values and close file
  lows[sensorNum] = lv;
  highs[sensorNum] = hv;
  Close(hFileHandle, nIoResult);
}
//Check the sensor's function
void _LScheckSensor(tSensors link) {
}
//  if (SensorMode[link] != modeRaw &&
//    ((SensorType[link] != sensorLightActive) ||
//     (SensorType[link] != sensorLightInactive))) {
//       nxtDisplayCenteredTextLine(2,"FOOBAR %d %d %d", SensorType[link], sensorLightActive, sensorLightInactive);
//      wait1Msec(1000);
//      LSsetInactive(link);
//
//    }
//}
//Return the raw value
int LSvalRaw(tSensors link) {
  _LScheckSensor(link);

  return SensorRaw[link];
}

//Return a normalized value
int LSvalNorm(tSensors link) {
  long currval = 0;

  _LScheckSensor(link);
  int curSensor=lookUpSensorLINK(link);
  if (!calibrated[curSensor]) {
    _LSreadCalVals(curSensor);
  }

  currval = LSvalRaw(link);

  if (currval <= lows[curSensor])
    return 0;
  else if (currval >= highs[curSensor])
    return 100;

  return ((currval-lows[curSensor])*100)/(highs[curSensor]-lows[curSensor]);
}

//Calibration
void LScalLow(tSensors link) {
  _LScheckSensor(link);
  int curSensor=lookUpSensorLINK(link);
  lows[curSensor] = SensorRaw[link];
  _LSwriteCalVals(curSensor);
}

void LScalHigh(tSensors link)
{
  _LScheckSensor(link);
  int curSensor=lookUpSensorLINK(link);
  highs[curSensor] = SensorRaw[link];
  _LSwriteCalVals(curSensor);
}
#endif // __LEGOLS_H__
