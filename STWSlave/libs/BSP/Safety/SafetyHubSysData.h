#ifndef _SAFETYHUBSYSDATA_H
#define _SAFETYHUBSYSDATA_H
#include <stwtypes.h>

//====================================================================
//define Constant
//====================================================================
#define PumpeMaxTemperatur                   (85000)
#define MaxXValueCG                          (2610)
#define MinXValueCG                          (200)
#define MaxYValueCG                          (1020)
#define MinYValueCG                          (100)
#define MaxMainDruckValue                    (150000)
#define MaxValveDruckValue                   (110000)
#define MaxPumpeLaufzeit                     (3000)
#define MaxPumpeDrehzahlWarn                 (100)
#define MaxPumpeDrehzahlError                (150)
#define KeySafetySetHubsystemHeben           (0x00000100)
#define KeySafetySetHubsystemSinken          (0x00000200)
#define KeySafetySetHubsystemOnlySinken      (0x00000400)
#define KeySafetySetHubsystemStop            (0x00000800)
#define KeySafetyMotorStatusFehler           (0x02)
#define KeySafetyMotorStatusEnable           (0x01)
#define KeySafetyNodeDisconneted             (0x01)

//====================================================================
//intene parameter
//====================================================================
extern boolean SafteyErrorHubTemperaturHigh;
extern boolean SafteyErrorAchse11lastet;
extern boolean SafteyErrorAchse12lastet;
extern boolean SafteyErrorAchse21lastet;
extern boolean SafteyErrorAchse22lastet;
extern boolean SafteyErrorMainDruckHigh;
extern boolean SafteyErrorPumpeDrehzahlTimeOut;
extern boolean SafteyErrorPumpeDrehzahlOut;
extern boolean SafteyWarnPumpeDrehzahlOut;
extern boolean SafteyErrorPumpeUmrichter;
extern boolean SafteyErrorVentil11TimeOut;
extern boolean SafteyErrorVentil12TimeOut;
extern boolean SafteyErrorVentil21TimeOut;
extern boolean SafteyErrorVentil22TimeOut;
extern boolean SafteyErrorVentil11;
extern boolean SafteyErrorVentil12;
extern boolean SafteyErrorVentil21;
extern boolean SafteyErrorVentil22;
extern boolean SafteyErrorVentil;
extern boolean SafteyErrorPumpeOfflineTimeOut;
extern boolean SafteyErrorPumpeOffline;

//====================================================================
//input parameter
//====================================================================
extern sint32 *inputSafetyHubSystemWeight;
extern sint32 *inputSafetyHubSystemCGValueX;
extern sint32 *inputSafetyHubSystemCGValueY;
extern uint32 *inputSafetyHubSystemHeight11;
extern uint32 *inputSafetyHubSystemHeight12;
extern uint32 *inputSafetyHubSystemHeight21;
extern uint32 *inputSafetyHubSystemHeight22;
extern sint32 *inputSafetyHubSystemPressure11;
extern sint32 *inputSafetyHubSystemPressure12;
extern sint32 *inputSafetyHubSystemPressure21;
extern sint32 *inputSafetyHubSystemPressure22;
extern sint32 *inputSafetyHubSystemPressureMain;
extern sint32 *inputSafetyHubSystemTemperaturMain;
extern uint8 *inputSafetyHubSystemPumpeStatusByte;
extern sint16 *inputSafetyHubSystemPumpeActualSpeed;
extern sint32 *inputSafetyHubSystemSpeedHeight11;
extern sint32 *inputSafetyHubSystemSpeedHeight12;
extern sint32 *inputSafetyHubSystemSpeedHeight21;
extern sint32 *inputSafetyHubSystemSpeedHeight22;
extern uint8 *inputSafetyHubSystemPumpeNodeStatus;

//====================================================================
//out parameter
//====================================================================
extern uint32 *outputSafetyHubSystemControlWord;
extern uint16 *outputSafetyHubSystemAxel11HebenPWM;
extern uint16 *outputSafetyHubSystemAxel11SinkenPWM;
extern uint16 *outputSafetyHubSystemAxel12HebenPWM;
extern uint16 *outputSafetyHubSystemAxel12SinkenPWM;
extern uint16 *outputSafetyHubSystemAxel21HebenPWM;
extern uint16 *outputSafetyHubSystemAxel21SinkenPWM;
extern uint16 *outputSafetyHubSystemAxel22HebenPWM;
extern uint16 *outputSafetyHubSystemAxel22SinkenPWM;
#endif