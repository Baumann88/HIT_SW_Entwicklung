#ifndef _HUBSYSTEMDATA_H
#define _HUBSYSTEMDATA_H
#include "stwtypes.h"

#define KeyHubSystemNormalMode                    0x00000000
#define KeyHubSystemEnable                        0x00000004
#define KeyHubSystemIsStop                        0x00000008
#define KeyHubSystemTestMode                      0x00000010
#define KeyHubSystemHeben                         0x00000100
#define KeyHubSystemSinken                        0x00000200

#define KeyHubSystemGetSafetyOnlySinken           0x00000400
#define KeyHubSystemGetSafetyStop                 0x00000800

#define KeyHubToMasterIsStop                      0x01
#define KeyHubToMasterOnlySinken                  0x02
#define KeyHubToMasterSetHeightNoAdd              0x04
#define KeyHubToMasterStopReq                     0x08

#define KeyHubModeStop                            0x00
#define KeyHubModeHeben                           0x01
#define KeyHubModeSinken                          0x02


#define KeyPumpeCtrlWordSafeStop                  0x40

typedef struct{
    //Parameter in PI-Controller
    float32 ek;
    float32 yk;
    float32 yk_1;
    float32 ek_1;
    float32 kp;
    float32 ki;
    uint32 PWM1;
    uint32 PWM2;
}TypeHubControllerDaten;

extern TypeHubControllerDaten ControllerDatenAxel11;
extern TypeHubControllerDaten ControllerDatenAxel12;
extern TypeHubControllerDaten ControllerDatenAxel21;
extern TypeHubControllerDaten ControllerDatenAxel22;

//toggle Bit
extern uint8 HubSystemToggleBit[2];
extern uint16 HubSystemToggleCounter;

//sampling time
extern float32 Ts_Hub;

//system tick
extern uint16 HubSysTick;

//work mode of the hub system up, down or stop
extern uint8 HubMode;

//set the height of the hydraulic axle
extern float32 Axel11HubSetHeight;
extern float32 Axel12HubSetHeight;
extern float32 Axel21HubSetHeight;
extern float32 Axel22HubSetHeight;

extern float32 Axel11HubSpeed;
extern float32 Axel12HubSpeed;
extern float32 Axel21HubSpeed;
extern float32 Axel22HubSpeed;

//Parameter for Hub sensor
extern float32 HubSersor11FactA;
extern float32 HubSersor11FactB;

extern float32 HubSersor12FactA;
extern float32 HubSersor12FactB;

extern float32 HubSersor21FactA;
extern float32 HubSersor21FactB;

extern float32 HubSersor22FactA;
extern float32 HubSersor22FactB;

extern float32 HubVirtualHeight;

//============================================================
//Input Parameter
//============================================================
//control word of the hub system
//bit 0-1: test mode (1) / normal mode (0) | bit 2: hydraulic motor en/disable
//Byte 1: which axel is choice in test mode
//Byte 2-3: value of height to be set (in percent)
extern uint32 *inputHubSystemControlWord;

//control word of the safety
extern uint32 *inputHubSystemGetSafetyControlWord;

//sampling time
extern uint16 *inputHubSysSamplingTime;

//status of the hydraulic motor
extern uint8 *inputHydraulicMotorStatusByte;

//actual speed of the hydraulic motor
extern sint16 *inputHydraulicMotorActualSpeed;

//NMT status of the hydraulic inverter
extern uint8 *inputHydraulicInverterNMTStatus;

//node status of the hydraulic inverter
extern uint8 *inputHydraulicInverterNodeStatus;

//temperature of the hydraulic pipe
extern uint16 *inputHydraulicTemperature; //AI13 Mainboard

//default hydraulic motor rpm
extern sint16 *inputDefaultHydraulicMotorRPM;

//default maximal height
extern uint32 *inputMaxHeight;

//default minimal height
extern uint32 *inputMinHeight;

//height sensor
extern uint16 *inputHeightSensor11;
extern uint16 *inputHeightSensor12;
extern uint16 *inputHeightSensor21;
extern uint16 *inputHeightSensor22;

//parameter for height sensor
extern sint32 *inputHeightSensor11FactA;
extern sint32 *inputHeightSensor11FactB;
extern sint32 *inputHeightSensor11FactC;
extern sint32 *inputHeightSensor11FactD;
extern sint32 *inputHeightSensor12FactA;
extern sint32 *inputHeightSensor12FactB;
extern sint32 *inputHeightSensor12FactC;
extern sint32 *inputHeightSensor12FactD;
extern sint32 *inputHeightSensor21FactA;
extern sint32 *inputHeightSensor21FactB;
extern sint32 *inputHeightSensor21FactC;
extern sint32 *inputHeightSensor21FactD;
extern sint32 *inputHeightSensor22FactA;
extern sint32 *inputHeightSensor22FactB;
extern sint32 *inputHeightSensor22FactC;
extern sint32 *inputHeightSensor22FactD;

//Sensor Value of for pressure
extern uint16 *inputPressureSensorValueAxel11; //AI9 Mainboard
extern uint16 *inputPressureSensorValueAxel12; //AI10 Mainboard
extern uint16 *inputPressureSensorValueAxel21; //AI11 Mainboard
extern uint16 *inputPressureSensorValueAxel22; //AI12 Mainboard
extern uint16 *inputPressureSensorValueMain;  //AI8 Mainboard

//Controller Parameter of Axel11
extern sint32 *inputAxel11ControlKp;
extern sint32 *inputAxel11ControlKi;

//Controller Parameter of Axel12
extern sint32 *inputAxel12ControlKp;
extern sint32 *inputAxel12ControlKi;

//Controller Parameter of Axel21
extern sint32 *inputAxel21ControlKp;
extern sint32 *inputAxel21ControlKi;

//Controller Parameter of Axel22
extern sint32 *inputAxel22ControlKp;
extern sint32 *inputAxel22ControlKi;


//============================================================
//Output Parameter
//============================================================
//control word of the hydraulic motor
extern uint16 *outputHydraulicMotorControlWord;

//set the speed of the hydraulic motor
extern sint16 *outputSetHydraulicMotorSpeed;

//NMT message for all node byte0: 0x01 send the actual NMT; 0x00 not send | byte 1 NMT message
extern uint16 *outputHydraulicInverterNMT;

//set Bypass valve
extern uint32 *outputSetBypassValve;  //Pin Out24 Slot0

//height of the hydraulic axle
extern uint32 *outputAxel11HubActualHeight;
extern uint32 *outputAxel12HubActualHeight;
extern uint32 *outputAxel21HubActualHeight;
extern uint32 *outputAxel22HubActualHeight;

//speed of the hub axle
extern sint32 *outputSpeedHubAxel11;
extern sint32 *outputSpeedHubAxel12;
extern sint32 *outputSpeedHubAxel21;
extern sint32 *outputSpeedHubAxel22;

//Value of pressure
extern sint32 *outputPressureAxel11;
extern sint32 *outputPressureAxel12;
extern sint32 *outputPressureAxel21;
extern sint32 *outputPressureAxel22;
extern sint32 *outputPressureMain;

//Value of CG Position
extern sint32 *outputHubCGPosL;
extern sint32 *outputHubCGPosB;

//Value of the Weight
extern sint32 *outputHubWeight;

//Value of the Height
extern uint8 *outputHubHeight;

//Status of the Hub system
extern uint8 *outputHubStatus;

//Value of temperature
extern sint32 *outputMainTemperature;

//Set value of Valve for raise axle
extern uint32 *outputSetPWMValveHubRaiseAxel11; //Pin Out00 Mainboard
extern uint32 *outputSetPWMValveHubRaiseAxel12; //Pin Out02 Mainboard
extern uint32 *outputSetPWMValveHubRaiseAxel21; //Pin Out04 Mainboard
extern uint32 *outputSetPWMValveHubRaiseAxel22; //Pin Out06 Mainboard

//Set value of Valve for sink axle
extern uint32 *outputSetPWMValveHubSinkAxel11;  //Pin Out01 Mainboard
extern uint32 *outputSetPWMValveHubSinkAxel12;  //Pin Out03 Mainboard
extern uint32 *outputSetPWMValveHubSinkAxel21;  //Pin Out05 Mainboard
extern uint32 *outputSetPWMValveHubSinkAxel22;  //Pin Out07 Mainboard

#endif
