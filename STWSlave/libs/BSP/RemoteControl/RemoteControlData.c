#include "RemoteControlData.h"


//============================================================
//Normal Parameter
//============================================================
//Request Key of the RC System
uint16 RCReqWord;

//Actual time for the RC System
uint32 RCActualTime;

//actual page for display
uint16 akt_page;


//============================================================
//Input Parameter
//============================================================
//control word from the safety system
uint32 *inputRCGetSafetyControlWord;
uint32 *inputRCGetSafetyMasterControlWord;
uint32 *inputRCGetHubSystemControlWord;

uint8 *inputRemoteControlToggle;
uint32 *inputRemoteControlDigitalIn;

//get actual height of the Hub System
uint32 *inputRCGetHubWerk11Height;
uint32 *inputRCGetHubWerk12Height;
uint32 *inputRCGetHubWerk21Height;
uint32 *inputRCGetHubWerk22Height;

//get actual Pressure of the Hub System
sint32 *inputRCGetHubWerk11Pressure;
sint32 *inputRCGetHubWerk12Pressure;
sint32 *inputRCGetHubWerk21Pressure;
sint32 *inputRCGetHubWerk22Pressure;

//Angle of drive system to slave
sint8 *inputRCFromMasterDriveSysAngle11;
sint8 *inputRCFromMasterDriveSysAngle12;
sint8 *inputRCFromMasterDriveSysAngle21;
sint8 *inputRCFromMasterDriveSysAngle22;

//status of the MES to slave
uint8 *inputRCFromMasterStatusMES;
uint8 *inputRCFromMasterStatusExtMES;
uint8 *inputRCFromMasterPageState;
uint8 *inputRCFromMasterStatusAutoDrive;
uint8 *inputRCFromMasterSteeringMode;
sint8 *inputRCFromMasterSpeedMES;
uint8 *inputRCFromMasterAutoDriveState;

//value of the Camera
sint8 *inputRCFromMasterY1Value;
sint8 *inputRCFromMasterY2Value;
uint16 *inputRCFromMasterXValue;

//get Number of Error from the Safety System
uint8 *inputRCGetErrorNum;

//get Number of Error from the Safety System of SlaveCPU
uint8 *inputRCGetMasterCPUErrorNum;

//get Error code from the Safety System
uint32 *inputRCGetErrorCode[8];

//get Error code from the Safety System of SlaveCPU
uint32 *inputRCGetErrorCodeMasterCPU[8];

//============================================================
//Output Parameter
//============================================================
//String for display
uint32 *outputRemoteControlString0;
uint32 *outputRemoteControlString1;
uint32 *outputRemoteControlString2;
uint32 *outputRemoteControlString3;
