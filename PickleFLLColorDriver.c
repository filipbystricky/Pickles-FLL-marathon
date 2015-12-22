#ifndef __LEGOCS_H__
#define __LEGOCS_H__
#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif
#define CPORT1 0
#define CPORT2 1
#define CPORT3 2
#define CPORT4 3

// Globals
//Stores whether or not a sensor has been calibrated
bool colorCalibrated[4]={false,false,false,false};
//Calibration Data
int rlows[4]={0,0,0,0};
int rhighs[4]={1023,1023,1023,1023};
int blows[4]={0,0,0,0};
int bhighs[4]={1023,1023,1023,1023};
int glows[4]={0,0,0,0};
int ghighs[4]={1023,1023,1023,1023};
//Calibration Data Files
const string dataFiles[4]={"zeroc.dat","onec.dat","twoc.dat","threec.dat"};

#define BLUE sensorColorNxtBLUE
#define RED sensorColorNxtRED
#define GREEN sensorColorNxtGREEN

void CSsetColor(tSensors link, TSensorTypes color) {
	SensorType[link] = color;
}

//Return an index to the array of data
int colorLookUpSensorLINK(tSensors link)
{
  switch (link)
  {
    case S1:
      return CPORT1;
      break;
    case S2:
      return CPORT2;
      break;
    case S3:
      return CPORT3;
      break;
    case S4:
      return CPORT4;
      break;
    default:
      nxtDisplayCenteredTextLine(2,"Invalid SensorPort");
      wait1Msec(5000);
      stopAllTasks();
      return -1;
  }
}

void _writeCSVal(TFileHandle hFileHandle, int val)
{
	TFileIOResult nIoResult;
	WriteShort(hFileHandle, nIoResult, val);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "can't write val");
    playSound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    stopAllTasks();
  }
}

void _CSwriteCalVals(int curSensor) {
  TFileHandle hFileHandle;
  TFileIOResult nIoResult;
  short nFileSize = 12;
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

   _writeCSVal(hFileHandle, rlows[curSensor]);
   _writeCSVal(hFileHandle, rhighs[curSensor]);
   _writeCSVal(hFileHandle, blows[curSensor]);
   _writeCSVal(hFileHandle, bhighs[curSensor]);
   _writeCSVal(hFileHandle, glows[curSensor]);
   _writeCSVal(hFileHandle, ghighs[curSensor]);

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

void _CSreadCalVals(int sensorNum) {
  TFileHandle hFileHandle;
  TFileIOResult nIoResult;
  short nFileSize;

  short lvr = 0;
  short hvr = 0;

  short lvb = 0;
  short hvb = 0;

  short lvg = 0;
  short hvg = 0;

  // Open the data file for reading
  colorCalibrated[sensorNum]=true;
  OpenRead(hFileHandle, nIoResult, dataFiles[sensorNum],nFileSize);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the low calibration value
  ReadShort(hFileHandle, nIoResult, lvr);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the high calibration value
  ReadShort(hFileHandle, nIoResult, hvr);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  ReadShort(hFileHandle, nIoResult, lvb);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the high calibration value
  ReadShort(hFileHandle, nIoResult, hvb);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  ReadShort(hFileHandle, nIoResult, lvg);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the high calibration value
  ReadShort(hFileHandle, nIoResult, hvg);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }


  // Assign values and close file
  rlows[sensorNum] = lvr;
  rhighs[sensorNum] = hvr;

  blows[sensorNum] = lvb;
  bhighs[sensorNum] = hvb;

  glows[sensorNum] = lvg;
  ghighs[sensorNum] = hvg;
  Close(hFileHandle, nIoResult);
}
//Check the sensor's function
void _CScheckSensor(tSensors link) {
	SensorMode[link] = modeRaw;
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
int CSvalRaw(tSensors link) {
  _CScheckSensor(link);

  return SensorRaw[link];
}

//Return a normalized value
int CSvalNorm(tSensors link) {
  long currval = 0;

  _CScheckSensor(link);
  int curSensor=colorLookUpSensorLINK(link);
  if (!colorCalibrated[curSensor]) {
    _CSreadCalVals(curSensor);
  }

  currval = CSvalRaw(link);

  int low, high;
  switch(SensorType[link]) {
  	case sensorColorNxtRED:
  		low = rlows[curSensor];
  		high = rhighs[curSensor];
  		break;
  	case sensorColorNxtBLUE:
  		low = blows[curSensor];
  		high = bhighs[curSensor];
  		break;
  	case sensorColorNxtGREEN:
  		low = glows[curSensor];
  		high = ghighs[curSensor];
  		break;
  }


  if (currval <= low)
    return 0;
  else if (currval >= high)
    return 100;

  return ((currval-low)*100)/(high-low);
}

//Calibration
void CScalLow(tSensors link) {
  _CScheckSensor(link);
  TSensorTypes color = SensorType[link];
  int curSensor=colorLookUpSensorLINK(link);
  switch(color) {
  	case sensorColorNxtRED:
  		rlows[curSensor] = SensorRaw[link];
  		break;
  	case sensorColorNxtBLUE:
  		blows[curSensor] = SensorRaw[link];
  		break;
  	case sensorColorNxtGREEN:
  		glows[curSensor] = SensorRaw[link];
  		break;
  }

  _CSwriteCalVals(curSensor);
}

void CScalHigh(tSensors link)
{
  _CScheckSensor(link);
  TSensorTypes color = SensorType[link];
  int curSensor=colorLookUpSensorLINK(link);
  switch(color) {
  	case sensorColorNxtRED:
  		rhighs[curSensor] = sensorRaw[link];
  		break;
  	case sensorColorNxtBLUE:
  		bhighs[curSensor] = sensorRaw[link];
  		break;
  	case sensorColorNxtGREEN:
  		ghighs[curSensor] = sensorRaw[link];
  		break;
  }
  _CSwriteCalVals(curSensor);
}
#endif // __LEGOCS_H__
