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
    Function: Set the error in the error counter
    output: None
*/
//=================================================================================================
void setFault(void);

//=================================================================================================
/*!
    Function: Set the error code in error register
    output: None
*/
//=================================================================================================
void SetErrorCode(uint32 code);

// Safety for Drive System
//====================================================================
/*!
Function: initial Satety DriveSys
Output: None
*/
//====================================================================
void InitSafetyDriveSys(void);
//====================================================================
/*!
Function: handle of safety drive system
Output: None
*/
//====================================================================
void HandleSafetyDriveSys(void);
//====================================================================
/*!
Function: timer of safety drive system
Output: None
*/
//====================================================================
void TimerSafetyDriveSys(void);


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

//====================================================================
/*!
Function: HandleSafetyNormal
Output: None
*/
//====================================================================
void HandleSafetyNormal(void);

#endif
