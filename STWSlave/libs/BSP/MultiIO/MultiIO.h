#ifndef _MULTIIO_H
#define _MULTIIO_H

#include "stwtypes.h"
#include "DeviceOD.h"
#include "AppConfig.h"
#include "x_in.h"
#include "x_out.h"
#include "x_sys.h"
#include "x_eb.h"
#include "x05_sys.h"
#include "x05_in.h"
#include "x05_out.h"

#define NumOfInput                  19
#define NumOfOutput                 16

#define InputCfgNoCfg               0x0000
#define InputCfgDigital             0x0001
#define InputCfgVoltage5V           0x0002
#define InputCfgVoltage10V          0x0003
#define InputCfgVoltage40V          0x0004
#define InputCfgCurrent             0x0005
#define InputCfgEventRising         0x0006
#define InputCfgEventFalling        0x0007
#define InputCfgEventBoth           0x0008
#define InputCfgFrequez             0x0009
#define InputCfgIncremental         0x000a

#define OutputCfgNoCfg              0x0000
#define OutputCfgDigital            0x0001
#define OutputCfgPWM                0x0002
#define OutputCfgCurrent            0x0003

extern uint16 inputConfig[NumOfInput][2];
extern sint32 inputFilterCfg[15];
extern uint16 outputConfig[NumOfOutput][2];

void MultiIOInit(void);
void MultiIOTask(void);



#endif // _MULTIINPUT_H
