#ifndef _SAFETYPLCDATA_H
#define _SAFETYPLCDATA_H
#include <stwtypes.h>

//====================================================================
//define Constant
//====================================================================
#define KeySafetySetRCLaserscanner1Slow      (0x00000400)
#define KeySafetySetRCLaserscanner2Slow      (0x00000800)
#define KeySafetySetRCLaserscanner1Warn      (0x00000008)
#define KeySafetySetRCLaserscanner2Warn      (0x00000020)
#define KeySafetySetRCLaserscanner1Stop      (0x00000010)
#define KeySafetySetRCLaserscanner2Stop      (0x00000040)
#define KeySafetyGetRCLaserscanner1Deaktiv   (0x00000002)
#define KeySafetyGetRCLaserscanner2Deaktiv   (0x00001000)
#define KeySafetySetRCDriveSysStop           (0x00000080)
#define KeySafetySetRCHubSysStop             (0x00000100)
#define KeySafetySetRCAutoDriveStop          (0x00000200)
#define KeySafetySetRCNotAusStatus           (0x00002000)
#define KeySafetySetRCLadeStatus             (0x00004000)
#define KeySafetySetRCSysSperrn              (0x00008000)
#define KeySafetyGetSlaveMESStatusOnlySinken (0x02)
#define KeySafetyGetSlaveMESStatusHubStopReq (0x08)
#define KeySafetyGetCANBus1Error             (0x01)
#define KeySafetyGetCANBus2Error             (0x02)
#define KeySafetyGetCANBus3Error             (0x04)
#define KeySafetyGetCANBus4Error             (0x08)
#define CPUMaxTemperatur                     (100000)
#define CPUMaxVoltage                        (28000)
#define CPUMinVoltage                        (12000)
#define CPUMaxVoltageExt                     (15000)
#define CPUMinVoltageExt                     (5000)
#define CPUMaxCurrent                        (10000)
#define CPUMinCurrent                        (10)

//====================================================================
//intene parameter
//====================================================================
extern boolean SafetyErrorNoVersorgung;
extern boolean SafetyErrorMESTimeOut;
extern boolean SafetyErrorLS1Warn1;
extern boolean SafetyErrorLS1Warn2;
extern boolean SafetyErrorLS1Abschalten;
extern boolean SafetyErrorLS2Warn1;
extern boolean SafetyErrorLS2Warn2;
extern boolean SafetyErrorLS2Abschalten;
extern boolean SafetyErrorLS1Quit;
extern boolean SafetyErrorLS2Quit;
extern boolean SafetyErrorNotAusEckVorne;
extern boolean SafetyErrorNotAusEckHinten;
extern boolean SafetyErrorNotAusFunke;
extern boolean SafetyErrorNotAusSchutzAus;
extern boolean SafetyErrorLadenZustand;
extern boolean SafetyErrorHubSystemOnlySinken;
extern boolean SafetyErrorHubSystemStopReq;
extern boolean SafetyErrorCPUTemperatur;
extern boolean SafetyErrorCPUVoltageUb;
extern boolean SafetyErrorCPUVoltageUc;
extern boolean SafetyErrorCPUVoltageUext;
extern boolean SafetyErrorCPUCurrentUb;
extern boolean SafetyErrorCANBus1;
extern boolean SafetyErrorCANBus2;
extern boolean SafetyErrorCANBus3;
extern boolean SafetyErrorCANBus4;
extern boolean SafetyErrorCANBus;
extern boolean SafetyErrorRCOfflineTimeOut;
extern boolean SafetyErrorRCOffline;

//====================================================================
//input parameter
//====================================================================
extern uint16 *inputSafetyIONotAusFunkeKanal1;
extern uint16 *inputSafetyIONotAusFunkeKanal2;
extern uint16 *inputSafetyIONotAusEckVorneKanal1;
extern uint16 *inputSafetyIONotAusEckVorneKanal2;
extern uint16 *inputSafetyIONotAusEckHintenKanal1;
extern uint16 *inputSafetyIONotAusEckHintenKanal2;
extern uint16 *inputSafetyIOLS1Warnfeld1;
extern uint16 *inputSafetyIOLS2Warnfeld1;
extern uint16 *inputSafetyIOLS1AbschaltFeldKanal1;
extern uint16 *inputSafetyIOLS1AbschaltFeldKanal2;
extern uint16 *inputSafetyIOLS2AbschaltFeldKanal1;
extern uint16 *inputSafetyIOLS2AbschaltFeldKanal2;
extern uint16 *inputSafetyIOLS1Warnfeld2;
extern uint16 *inputSafetyIOLS2Warnfeld2;
extern uint32 *inputSafetyIOLS1Quittierung;
extern uint32 *inputSafetyIOLS2Quittierung;
extern uint16 *inputSafetyIONotAusSchutz;
extern uint16 *inputSafetyIOLadeStecker;
extern uint32 *inputSafetySafetySysControlWord;
extern uint8 *inputSafetyGetSlaveMESStatus;
extern uint32 *inputSafetyGetCPUTemperatur;
extern uint32 *inputSafetyGetCPUVoltageUb;
extern uint32 *inputSafetyGetCPUVoltageUc;
extern uint32 *inputSafetyGetCPUVoltageUext;
extern uint32 *inputSafetyGetCPUCurrentUb;
extern uint8 *inputSafetyGetCANBusStatus;
extern uint8 *inputSafetyRCNodeStatus;

//====================================================================
//out parameter
//====================================================================
extern uint32 *outputSafetyIOLeistungSchutz1;
extern uint32 *outputSafetyIOLeistungSchutz2;
extern uint32 *outputSafetyIOMESAus;
extern uint32 *outputSafetyIOQuittierungLS1;
extern uint32 *outputSafetyIOQuittierungLS2;
extern uint32 *outputSafetyIOMotorSafetyStop;
extern uint32 *outputSafetyIO15minAus;
#endif