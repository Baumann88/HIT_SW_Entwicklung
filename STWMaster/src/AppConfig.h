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
#include "DriveInterface.h"
#include "RemoteControlInterface.h"
#include "SafetyInterface.h"
#include "MultiIOInterface.h"
#include "Tracking.h"
#include "MESConfig.h"




#define PrioDrvieSysControl              1
#define PrioDriveSysManage               3

#define PrioTrackingControl              2

#define PrioRemoteControl                4
#define PrioSafety                       6
#define PrioIOPort                       5
#define PrioRemoteControlDisplay         8
#define PrioTrackingManage               7

#define Event_DriveSysControl            X_OS_EVENT_01
#define Event_AutoDriveControl           X_OS_EVENT_02
#define Event_RC                         X_OS_EVENT_03



#endif // _APPCONFIG_H
