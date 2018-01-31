#ifndef _APPCONFIG_H
#define _APPCONFIG_H

#include "x_sys.h"   // include ESX-3XM system function header
#include "x_lib.h"
#include "x_mpu.h"
#include "x_fl.h"
#include "x_os.h"
#include "math.h"
#include "DeviceOD.h"
#include "CommInterface.h"
#include "SafetyInterface.h"
#include "HubSystemInterface.h"
#include "MultiIOInterface.h"
#include "MESConfig.h"


#define PrioHubSySControl                1
#define PrioHubSysManage                 3

#define PrioSafety                       6
#define PrioIOPort                       4
#define PrioRemoteControl                2
#define PrioRemoteControlDisplay         5

#define Event_HubSysControl              X_OS_EVENT_01
#define Event_RC                         X_OS_EVENT_02



#endif // _APPCONFIG_H
