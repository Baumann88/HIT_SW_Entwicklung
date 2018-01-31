#ifndef _HUBSYSTEM_H
#define _HUBSYSTEM_H
#include "stwtypes.h"
#include "DeviceOD.h"
#include "AppConfig.h"
#include "MESConfig.h"

//=================================================================================================
/*!
    Function: start the Inverter of Hub system
    output: None
*/
//=================================================================================================
void StartHubInverter(void);

//=================================================================================================
/*!
    Function: stop the Inverter of Hub system
    output: None
*/
//=================================================================================================
void StopHubInverter(void);

//=================================================================================================
/*!
    Function: this is a task for control of the Hub system
    output: None
*/
//=================================================================================================
void Task_HubSysControl(void* argv);

#endif
