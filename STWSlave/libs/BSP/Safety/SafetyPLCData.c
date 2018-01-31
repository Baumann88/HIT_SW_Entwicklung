#include <SafetyPLCData.h>

//====================================================================
//intene parameter
//====================================================================
boolean SafteySetLampe;
boolean SafetyErrorCPUTemperatur;
boolean SafetyErrorCPUVoltageUb;
boolean SafetyErrorCPUVoltageUc;
boolean SafetyErrorCPUVoltageUext;
boolean SafetyErrorCPUCurrentUb;
boolean SafetyErrorCANBus1;
boolean SafetyErrorCANBus2;
boolean SafetyErrorCANBus;

//====================================================================
//input parameter
//====================================================================
uint32 *inputSafetySafetySysControlWord;
uint32 *inputSafetyGetCPUTemperatur;
uint32 *inputSafetyGetCPUVoltageUb;
uint32 *inputSafetyGetCPUVoltageUc;
uint32 *inputSafetyGetCPUVoltageUext;
uint32 *inputSafetyGetCPUCurrentUb;
uint8 *inputSafetyGetCANBusStatus;

//====================================================================
//out parameter
//====================================================================
uint32 *outputSafetyIOLampe3;
uint32 *outputSafetyIOLampe4;
