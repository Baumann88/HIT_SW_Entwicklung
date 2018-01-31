#ifndef _TRACKING_H
#define _TRACKING_H

#include "stwtypes.h"
#include "MESConfig.h"
#include "AppConfig.h"
#include "DeviceOD.h"

//=================================================================================================
/*!
    Function: get the measurement value for auto drive
    output: None
*/
//=================================================================================================
void GetMeasurementAutoDrive(void);

//=================================================================================================
/*!
    Function: Controller for auto drive
    output: None
*/
//=================================================================================================
void AutoDriveController(void);
//=================================================================================================
/*!
    Function: reset Controller for auto drive
    output: None
*/
//=================================================================================================
void AutoDriveResetController(void);

#endif
