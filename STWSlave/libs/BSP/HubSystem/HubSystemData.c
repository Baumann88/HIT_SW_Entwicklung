#include "HubSystemData.h"

//toggle Bit
uint8 HubSystemToggleBit[2];
uint16 HubSystemToggleCounter;

//sampling time
float32 Ts_Hub;

//system tick
uint16 HubSysTick;

//work mode of the hub system up, down or stop
uint8 HubMode;

//set the height of the hydraulic axle
float32 Axel11HubSetHeight;
float32 Axel12HubSetHeight;
float32 Axel21HubSetHeight;
float32 Axel22HubSetHeight;

float32 Axel11HubSpeed;
float32 Axel12HubSpeed;
float32 Axel21HubSpeed;
float32 Axel22HubSpeed;

//Parameter for Hub sensor
float32 HubSersor11FactA;
float32 HubSersor11FactB;

float32 HubSersor12FactA;
float32 HubSersor12FactB;

float32 HubSersor21FactA;
float32 HubSersor21FactB;

float32 HubSersor22FactA;
float32 HubSersor22FactB;

float32 HubVirtualHeight;

TypeHubControllerDaten ControllerDatenAxel11={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0,0};
TypeHubControllerDaten ControllerDatenAxel12={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0,0};
TypeHubControllerDaten ControllerDatenAxel21={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0,0};
TypeHubControllerDaten ControllerDatenAxel22={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0,0};

//============================================================
//Input Parameter
//============================================================
//control word of the hub system
//bit 0-1: test mode (1) / normal mode (0) | bit 2: hydraulic motor en/disable
//Byte 1: which axel is choice in test mode
uint32 *inputHubSystemControlWord;

//control word of the safety
uint32 *inputHubSystemGetSafetyControlWord;

//sampling time
uint16 *inputHubSysSamplingTime;

//status of the hydraulic motor
uint8 *inputHydraulicMotorStatusByte;

//actual speed of the hydraulic motor
sint16 *inputHydraulicMotorActualSpeed;

//NMT status of the hydraulic inverter
uint8 *inputHydraulicInverterNMTStatus;

//node status of the hydraulic inverter
uint8 *inputHydraulicInverterNodeStatus;

//temperature of the hydraulic pipe
uint16 *inputHydraulicTemperature; //AI13 Mainboard

//default hydraulic motor rpm
sint16 *inputDefaultHydraulicMotorRPM;

//default maximal height
uint32 *inputMaxHeight;

//default minimal height
uint32 *inputMinHeight;

//height sensor
uint16 *inputHeightSensor11;
uint16 *inputHeightSensor12;
uint16 *inputHeightSensor21;
uint16 *inputHeightSensor22;

//parameter for height sensor
sint32 *inputHeightSensor11FactA;
sint32 *inputHeightSensor11FactB;
sint32 *inputHeightSensor11FactC;
sint32 *inputHeightSensor11FactD;
sint32 *inputHeightSensor12FactA;
sint32 *inputHeightSensor12FactB;
sint32 *inputHeightSensor12FactC;
sint32 *inputHeightSensor12FactD;
sint32 *inputHeightSensor21FactA;
sint32 *inputHeightSensor21FactB;
sint32 *inputHeightSensor21FactC;
sint32 *inputHeightSensor21FactD;
sint32 *inputHeightSensor22FactA;
sint32 *inputHeightSensor22FactB;
sint32 *inputHeightSensor22FactC;
sint32 *inputHeightSensor22FactD;

//Sensor Value of for pressure
uint16 *inputPressureSensorValueAxel11; //AI9 Mainboard
uint16 *inputPressureSensorValueAxel12; //AI10 Mainboard
uint16 *inputPressureSensorValueAxel21; //AI11 Mainboard
uint16 *inputPressureSensorValueAxel22; //AI12 Mainboard
uint16 *inputPressureSensorValueMain;  //AI8 Mainboard

//Controller Parameter of Axel11
sint32 *inputAxel11ControlKp;
sint32 *inputAxel11ControlKi;

//Controller Parameter of Axel12
sint32 *inputAxel12ControlKp;
sint32 *inputAxel12ControlKi;

//Controller Parameter of Axel21
sint32 *inputAxel21ControlKp;
sint32 *inputAxel21ControlKi;

//Controller Parameter of Axel22
sint32 *inputAxel22ControlKp;
sint32 *inputAxel22ControlKi;

//============================================================
//Output Parameter
//============================================================
//control word of the hydraulic motor
uint16 *outputHydraulicMotorControlWord;

//set the speed of the hydraulic motor
sint16 *outputSetHydraulicMotorSpeed;

//NMT message for all node byte0: 0x01 send the actual NMT; 0x00 not send | byte 1 NMT message
uint16 *outputHydraulicInverterNMT;

//set Bypass valve
uint32 *outputSetBypassValve;  //Pin Out24 Slot0

//height of the hydraulic axle
uint32 *outputAxel11HubActualHeight;
uint32 *outputAxel12HubActualHeight;
uint32 *outputAxel21HubActualHeight;
uint32 *outputAxel22HubActualHeight;

//speed of the hub axle
sint32 *outputSpeedHubAxel11;
sint32 *outputSpeedHubAxel12;
sint32 *outputSpeedHubAxel21;
sint32 *outputSpeedHubAxel22;


//Value of pressure
sint32 *outputPressureAxel11;
sint32 *outputPressureAxel12;
sint32 *outputPressureAxel21;
sint32 *outputPressureAxel22;
sint32 *outputPressureMain;

//Value of CG Position
sint32 *outputHubCGPosL;
sint32 *outputHubCGPosB;

//Value of the Weight
sint32 *outputHubWeight;

//Value of the Height
uint8 *outputHubHeight;

//Status of the Hub system
uint8 *outputHubStatus;

//Value of temperature
sint32 *outputMainTemperature;

//Set value of Valve for raise axle
uint32 *outputSetPWMValveHubRaiseAxel11; //Pin Out00 Mainboard
uint32 *outputSetPWMValveHubRaiseAxel12; //Pin Out02 Mainboard
uint32 *outputSetPWMValveHubRaiseAxel21; //Pin Out04 Mainboard
uint32 *outputSetPWMValveHubRaiseAxel22; //Pin Out06 Mainboard

//Set value of Valve for sink axle
uint32 *outputSetPWMValveHubSinkAxel11;  //Pin Out01 Mainboard
uint32 *outputSetPWMValveHubSinkAxel12;  //Pin Out03 Mainboard
uint32 *outputSetPWMValveHubSinkAxel21;  //Pin Out05 Mainboard
uint32 *outputSetPWMValveHubSinkAxel22;  //Pin Out07 Mainboard
