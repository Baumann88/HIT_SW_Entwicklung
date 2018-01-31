#ifndef _SAFETYDATA_H
#define _SAFETYDATA_H
#include "stwtypes.h"

#include "SafetyHubSysData.h"
#include "SafetyPLCData.h"

#define KeySafetySetRCError                       0x00000001
#define KeySafetyGetRCLaserscannerDeaktiv         0x00000002
#define KeySafetyGetRCNoMotion                    0x00000004
#define KeySafetySetRCLaserscanner1Warn           0x00000008
#define KeySafetySetRCLaserscanner1Stop           0x00000010
#define KeySafetySetRCLaserscanner2Warn           0x00000020
#define KeySafetySetRCLaserscanner2Stop           0x00000040

//#define KeySafetySetRCDriveSysStop                0x00000080
//#define KeySafetySetRCHubSysStop                  0x00000100
//#define KeySafetySetRCAutoDriveStop               0x00000200

//error code of the note on the bus
extern uint32 *inputErrorRegister[32];
extern uint32 *inputErrorTimeStamp[32][2];

//counter of the system error
extern uint16 *inputErrorCount;

//system control word
extern uint32 *inputSafetySysControlWord;

//Date Time
extern uint32 *inputSafetyDateTime1;
extern uint32 *inputSafetyDateTime2;

extern uint16 fault;


#endif
