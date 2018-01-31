#include <TrackingData.h>

TypeAutoDriveControllerDaten AutoDriveControllerDaten={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};

sint16 AutoDriveStopPos[NumOfPosBand]={1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
//sint16 AutoDriveAktivBand=-1;

//Sampling time of the auto drive
float32 AutoDriveTs;

//state of the auto drive
uint8 AutoDriveState;

//Input Parameter of the auto drive
uint32 *inputAutoDriveControlWord;

//Input from safety block
uint32 *inputAutoDriveGetSafetyControlWord;

sint32 *inputAutoDriveReferenzSpeed;

sint32 *inputAutoDriveControlKp1;
sint32 *inputAutoDriveControlKp2;
sint32 *inputAutoDriveControlKi1;
sint32 *inputAutoDriveControlKi2;

uint8 *inputAutoDriveYp11;
uint8 *inputAutoDriveYp12;
uint8 *inputAutoDriveYp13;
uint8 *inputAutoDriveYp14;
uint8 *inputAutoDriveYp21;
uint8 *inputAutoDriveYp22;
uint8 *inputAutoDriveYp23;
uint8 *inputAutoDriveYp24;

uint8 *inputAutoDriveXp11;
uint8 *inputAutoDriveXp12;
uint8 *inputAutoDriveXp13;
uint8 *inputAutoDriveXp14;
uint8 *inputAutoDriveXp21;
uint8 *inputAutoDriveXp22;
uint8 *inputAutoDriveXp23;
uint8 *inputAutoDriveXp24;

uint8 *inputAutoDriveAG11;
uint8 *inputAutoDriveAG12;
uint8 *inputAutoDriveAG21;
uint8 *inputAutoDriveAG22;

uint8 *inputAutoDriveST11;
uint8 *inputAutoDriveST12;
uint8 *inputAutoDriveST21;
uint8 *inputAutoDriveST22;

uint8 *inputKamera1NodeStatus;
uint8 *inputKamera2NodeStatus;

//state of the auto drive
uint8 *outputAutoDriveState;

//number of the akt. band
sint8 *outputNumOfBand;

//Output Parameter of the auto drive
sint16 *outputAutoDriveY1Value;
sint16 *outputAutoDriveY2Value;

sint16 *outputAutoDriveX1Value;
sint16 *outputAutoDriveX2Value;

sint16 *outputAutoDriveAG1Value;
sint16 *outputAutoDriveAG2Value;

//Output to slave
sint8 *outputAutoDriveToSlaveY1Value;
sint8 *outputAutoDriveToSlaveY2Value;

uint16 *outputAutoDriveToSlaveXValue;

uint8 *outputAutoDriveToSlaveState;

//set speed of the drive module for 2 dimensional steering
float32 *outputAutoDriveSetSpeedX;
float32 *outputAutoDriveSetSpeedY;
float32 *outputAutoDriveSetOmegaZ;

//SDO Control word
uint32 *outputAutoDriveInitSDOControlWord;
uint32 *outputAutoDriveInitSDOContent;

uint32 *outputAutoDriveCameraControlWord;

//NMT of Camera
uint16 *outputKamera1NMT;
uint16 *outputKamera2NMT;

//Hupe for finish
uint32 *outputIOPortFinishHupe;
