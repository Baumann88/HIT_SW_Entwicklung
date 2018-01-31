#include "RemoteControlData.h"


//============================================================
//Normal Parameter
//============================================================
//state of the RC System
uint8 State;

//Actual time for the RC System
uint32 RCActualTime;

//Request Key of the RC System
uint16 RCReqWord;

//actual page for display
uint16 akt_page;

//============================================================
//Input Parameter
//============================================================

//control word from the slave safety system
uint32 *inputRCGetSlaveSafetyControlWord;

//input value of the remote controller
uint8 *inputRemoteControlXVar;
uint8 *inputRemoteControlY1Var;
uint8 *inputRemoteControlY2Var;
uint8 *inputRemoteControlZVar;
uint8 *inputRemoteControlSpeedPoti;
uint8 *inputRemoteControlToggle;
uint32 *inputRemoteControlDigitalIn;

//Joystick parameter
sint32 *inputRCJoystickXFactA;
sint32 *inputRCJoystickXFactB;
sint32 *inputRCJoystickXFactC;
sint32 *inputRCJoystickXFactD;


//input for Auto/Hand mode
uint16 *inputIOPortHand;
uint16 *inputIOPortAutomatik;

//get actual angle of the drive module
sint32 *inputRCGetDriveModule11Angle;
sint32 *inputRCGetDriveModule12Angle;
sint32 *inputRCGetDriveModule21Angle;
sint32 *inputRCGetDriveModule22Angle;

//get actual y value of the auto drive
sint16 *inputRCGetAutoDriveY1Value;
sint16 *inputRCGetAutoDriveY2Value;

sint16 *inputRCGetAutoDriveXValue;

//actual height of hub system
uint8 *inputHubsystemHeight;

//actual status of hub system
uint8 *inputHubsystemStatus;


//============================================================
//Output Parameter
//============================================================
//control word to the drive system
uint32 *outputRCSetDriveSysControlWord;

//control word to the hub system
uint32 *outputRCSetHubSysControlWord;

//control word to the safety system
uint32 *outputRCSetSafetyControlWord;

//control word to the auto drive system
uint32 *outputRCSetAutoDriveControlWord;

//set speed of the drive module for 1 dimensional steering
float32 *outputRCSetDriveSysSpeed;
float32 *outputRCSetDriveSysAngle;

//output value of the remote controller
uint32 *outputIOPortHupe;

//output value of Lamp
uint32 *outputIOPortLampe11;
uint32 *outputIOPortLampe12;
uint32 *outputIOPortLampe21;
uint32 *outputIOPortLampe22;

//Angle of drive system to slave
sint8 *outputRCToSlaveDriveSysAngle11;
sint8 *outputRCToSlaveDriveSysAngle12;
sint8 *outputRCToSlaveDriveSysAngle21;
sint8 *outputRCToSlaveDriveSysAngle22;

//status of the MES to slave
uint8 *outputRCToSlaveStatusMES;
uint8 *outputRCToSlaveStatusExtMES;
uint8 *outputRCToSlavePageState;
uint8 *outputRCToSlaveStatusAuto;
uint8 *outputRCToSlaveSteeringMode;

//NMT value for remote control
uint16 *outputRemoteControlNMT;
