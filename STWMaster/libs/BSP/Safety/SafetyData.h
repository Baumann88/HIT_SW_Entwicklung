#ifndef _SAFETYDATA_H
#define _SAFETYDATA_H
#include "stwtypes.h"

#include "SafetyDriveSysData.h"
#include "SafetyPLCData.h"

#define KeySafetySetRCError                       0x00000001
#define KeySafetyGetRCNoMotion                    0x00000004

#define KeySafetySDOControlWordEnable             0x00000001

//#define KeySafetySetRCDriveSysStop                0x00000080
//#define KeySafetySetRCHubSysStop                  0x00000100
//#define KeySafetySetRCAutoDriveStop               0x00000200

//error code of the note on the bus
extern uint32 *inputErrorRegister[32];
extern uint32 *inputErrorTimeStamp[32][2];

//Date Time
extern uint32 *inputSafetyDateTime1;
extern uint32 *inputSafetyDateTime2;

//system control word
extern uint32 *inputSafetySysControlWord;

//SDO Control word
extern uint32 *outputSafetySDOControlWord;
extern uint32 *outputSafetySDOContent;

//counter of the system error
extern uint8 *outputErrorCount;
#endif
