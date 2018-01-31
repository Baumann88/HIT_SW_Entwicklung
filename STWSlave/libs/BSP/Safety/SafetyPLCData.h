#ifndef _SAFETYPLCDATA_H
#define _SAFETYPLCDATA_H
#include <stwtypes.h>

//====================================================================
//define Constant
//====================================================================
#define KeyCtrlWordSetLampe                  (0x00000010)
#define CPUMaxTemperatur                     (100000)
#define CPUMaxVoltage                        (30000)
#define CPUMinVoltage                        (12000)
#define CPUMaxVoltageExt                     (11000)
#define CPUMinVoltageExt                     (3000)
#define CPUMaxCurrent                        (1000000)
#define CPUMinCurrent                        (10)
#define KeySafetyGetCANBus1Error             (0x01)
#define KeySafetyGetCANBus2Error             (0x02)

//====================================================================
//intene parameter
//====================================================================
extern boolean SafteySetLampe;
extern boolean SafetyErrorCPUTemperatur;
extern boolean SafetyErrorCPUVoltageUb;
extern boolean SafetyErrorCPUVoltageUc;
extern boolean SafetyErrorCPUVoltageUext;
extern boolean SafetyErrorCPUCurrentUb;
extern boolean SafetyErrorCANBus1;
extern boolean SafetyErrorCANBus2;
extern boolean SafetyErrorCANBus;

//====================================================================
//input parameter
//====================================================================
extern uint32 *inputSafetySafetySysControlWord;
extern uint32 *inputSafetyGetCPUTemperatur;
extern uint32 *inputSafetyGetCPUVoltageUb;
extern uint32 *inputSafetyGetCPUVoltageUc;
extern uint32 *inputSafetyGetCPUVoltageUext;
extern uint32 *inputSafetyGetCPUCurrentUb;
extern uint8 *inputSafetyGetCANBusStatus;

//====================================================================
//out parameter
//====================================================================
extern uint32 *outputSafetyIOLampe3;
extern uint32 *outputSafetyIOLampe4;
#endif