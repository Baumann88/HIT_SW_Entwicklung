#ifndef _SAFETY_H
#define _SAFETY_H

#include "stwtypes.h"
#include "x_sys.h"
#include "x_os.h"
#include "DeviceOD.h"
#include "MESConfig.h"
#include "AppConfig.h"

//=================================================================================================
/*!
    Function: Set the error code in error register
    output: None
*/
//=================================================================================================
void SetErrorCode(uint32 code);

//=================================================================================================
/*!
    Function: Set the error in the error counter
    output: None
*/
//=================================================================================================
void setFault(void);

// Safety for Hub System
//====================================================================
/*!
Function: initial Hub HubSys
Output: None
*/
//====================================================================
void InitSafetyHubSys(void);
//====================================================================
/*!
Function: handle of safety hub system
Output: None
*/
//====================================================================
void HandleSafetyHubSys(void);
//====================================================================
/*!
Function: timer of safety drive system
Output: None
*/
//====================================================================
void TimerSafetyHubSys(void);

// Safety for PLC
//====================================================================
/*!
Function: initial of safety plc
Output: None
*/
//====================================================================
void InitSafetyPLC(void);
//====================================================================
/*!
Function: handle of safety plc
Output: None
*/
//====================================================================
void HandleSafetyPLC(void);
//====================================================================
/*!
Function: timer of safety plc
Output: None
*/
//====================================================================
void TimerSafetyPLC(void);

// Safety Normal
//====================================================================
/*!
Function: handle safety normal
Output: None
*/
//====================================================================
void HandleSafetyNormal(void);

#endif
