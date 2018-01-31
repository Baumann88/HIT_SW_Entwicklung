#include "SafetyData.h"

//error code of the note on the bus
uint32 *inputErrorRegister[32];
uint32 *inputErrorTimeStamp[32][2];

//system control word
uint32 *inputSafetySysControlWord;

//counter of the system error
uint16 *inputErrorCount;

//Date Time
uint32 *inputSafetyDateTime1;
uint32 *inputSafetyDateTime2;

uint16 fault;









