#include <SafetyHubSysData.h>

//====================================================================
//intene parameter
//====================================================================
boolean SafteyErrorHubTemperaturHigh;
boolean SafteyErrorAchse11lastet;
boolean SafteyErrorAchse12lastet;
boolean SafteyErrorAchse21lastet;
boolean SafteyErrorAchse22lastet;
boolean SafteyErrorMainDruckHigh;
boolean SafteyErrorPumpeDrehzahlTimeOut;
boolean SafteyErrorPumpeDrehzahlOut;
boolean SafteyWarnPumpeDrehzahlOut;
boolean SafteyErrorPumpeUmrichter;
boolean SafteyErrorVentil11TimeOut;
boolean SafteyErrorVentil12TimeOut;
boolean SafteyErrorVentil21TimeOut;
boolean SafteyErrorVentil22TimeOut;
boolean SafteyErrorVentil11;
boolean SafteyErrorVentil12;
boolean SafteyErrorVentil21;
boolean SafteyErrorVentil22;
boolean SafteyErrorVentil;
boolean SafteyErrorPumpeOfflineTimeOut;
boolean SafteyErrorPumpeOffline;

//====================================================================
//input parameter
//====================================================================
sint32 *inputSafetyHubSystemWeight;
sint32 *inputSafetyHubSystemCGValueX;
sint32 *inputSafetyHubSystemCGValueY;
uint32 *inputSafetyHubSystemHeight11;
uint32 *inputSafetyHubSystemHeight12;
uint32 *inputSafetyHubSystemHeight21;
uint32 *inputSafetyHubSystemHeight22;
sint32 *inputSafetyHubSystemPressure11;
sint32 *inputSafetyHubSystemPressure12;
sint32 *inputSafetyHubSystemPressure21;
sint32 *inputSafetyHubSystemPressure22;
sint32 *inputSafetyHubSystemPressureMain;
sint32 *inputSafetyHubSystemTemperaturMain;
uint8 *inputSafetyHubSystemPumpeStatusByte;
sint16 *inputSafetyHubSystemPumpeActualSpeed;
sint32 *inputSafetyHubSystemSpeedHeight11;
sint32 *inputSafetyHubSystemSpeedHeight12;
sint32 *inputSafetyHubSystemSpeedHeight21;
sint32 *inputSafetyHubSystemSpeedHeight22;
uint8 *inputSafetyHubSystemPumpeNodeStatus;

//====================================================================
//out parameter
//====================================================================
uint32 *outputSafetyHubSystemControlWord;
uint16 *outputSafetyHubSystemAxel11HebenPWM;
uint16 *outputSafetyHubSystemAxel11SinkenPWM;
uint16 *outputSafetyHubSystemAxel12HebenPWM;
uint16 *outputSafetyHubSystemAxel12SinkenPWM;
uint16 *outputSafetyHubSystemAxel21HebenPWM;
uint16 *outputSafetyHubSystemAxel21SinkenPWM;
uint16 *outputSafetyHubSystemAxel22HebenPWM;
uint16 *outputSafetyHubSystemAxel22SinkenPWM;
