#include <SafetyPLCData.h>

//====================================================================
//intene parameter
//====================================================================
boolean SafetyErrorNoVersorgung;
boolean SafetyErrorMESTimeOut;
boolean SafetyErrorLS1Warn1;
boolean SafetyErrorLS1Warn2;
boolean SafetyErrorLS1Abschalten;
boolean SafetyErrorLS2Warn1;
boolean SafetyErrorLS2Warn2;
boolean SafetyErrorLS2Abschalten;
boolean SafetyErrorLS1Quit;
boolean SafetyErrorLS2Quit;
boolean SafetyErrorNotAusEckVorne;
boolean SafetyErrorNotAusEckHinten;
boolean SafetyErrorNotAusFunke;
boolean SafetyErrorNotAusSchutzAus;
boolean SafetyErrorLadenZustand;
boolean SafetyErrorHubSystemOnlySinken;
boolean SafetyErrorHubSystemStopReq;
boolean SafetyErrorCPUTemperatur;
boolean SafetyErrorCPUVoltageUb;
boolean SafetyErrorCPUVoltageUc;
boolean SafetyErrorCPUVoltageUext;
boolean SafetyErrorCPUCurrentUb;
boolean SafetyErrorCANBus1;
boolean SafetyErrorCANBus2;
boolean SafetyErrorCANBus3;
boolean SafetyErrorCANBus4;
boolean SafetyErrorCANBus;
boolean SafetyErrorRCOfflineTimeOut;
boolean SafetyErrorRCOffline;

//====================================================================
//input parameter
//====================================================================
uint16 *inputSafetyIONotAusFunkeKanal1;
uint16 *inputSafetyIONotAusFunkeKanal2;
uint16 *inputSafetyIONotAusEckVorneKanal1;
uint16 *inputSafetyIONotAusEckVorneKanal2;
uint16 *inputSafetyIONotAusEckHintenKanal1;
uint16 *inputSafetyIONotAusEckHintenKanal2;
uint16 *inputSafetyIOLS1Warnfeld1;
uint16 *inputSafetyIOLS2Warnfeld1;
uint16 *inputSafetyIOLS1AbschaltFeldKanal1;
uint16 *inputSafetyIOLS1AbschaltFeldKanal2;
uint16 *inputSafetyIOLS2AbschaltFeldKanal1;
uint16 *inputSafetyIOLS2AbschaltFeldKanal2;
uint16 *inputSafetyIOLS1Warnfeld2;
uint16 *inputSafetyIOLS2Warnfeld2;
uint32 *inputSafetyIOLS1Quittierung;
uint32 *inputSafetyIOLS2Quittierung;
uint16 *inputSafetyIONotAusSchutz;
uint16 *inputSafetyIOLadeStecker;
uint32 *inputSafetySafetySysControlWord;
uint8 *inputSafetyGetSlaveMESStatus;
uint32 *inputSafetyGetCPUTemperatur;
uint32 *inputSafetyGetCPUVoltageUb;
uint32 *inputSafetyGetCPUVoltageUc;
uint32 *inputSafetyGetCPUVoltageUext;
uint32 *inputSafetyGetCPUCurrentUb;
uint8 *inputSafetyGetCANBusStatus;
uint8 *inputSafetyRCNodeStatus;

//====================================================================
//out parameter
//====================================================================
uint32 *outputSafetyIOLeistungSchutz1;
uint32 *outputSafetyIOLeistungSchutz2;
uint32 *outputSafetyIOMESAus;
uint32 *outputSafetyIOQuittierungLS1;
uint32 *outputSafetyIOQuittierungLS2;
uint32 *outputSafetyIOMotorSafetyStop;
uint32 *outputSafetyIO15minAus;
