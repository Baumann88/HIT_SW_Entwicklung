#ifndef _EEP_MANAGE_H
#define _EEP_MANAGE_H

#include "stwtypes.h"
#include "x_sys.h"

sint16 EEPDataStore(uint32 Value, uint16 NByte, uint32 EEPAddr);
sint16 EEPDataLoad(uint32 *Value, uint16 NByte, uint32 EEPAddr);
#endif
