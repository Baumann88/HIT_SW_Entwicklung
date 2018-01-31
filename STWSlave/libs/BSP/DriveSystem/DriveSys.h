#ifndef _DRIVESYS_H
#define _DRIVESYS_H

#include "stwtypes.h"
#include "MESConfig.h"
#include "AppConfig.h"
#include "DeviceOD.h"

//=================================================================================================
/*!
    Function: this is a task for control of the Drive system
    output: None
*/
//=================================================================================================
void Task_DriveSysControl(void* argv);

//=================================================================================================
/*!
    Function: this is a automat of the Drive system
    output: None
*/
//=================================================================================================
void Task_DriveSysManage(void* argv);

#endif // _DRIVESYS_H

