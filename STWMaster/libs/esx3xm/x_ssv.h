//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_ssv.h
   \brief      supervisor functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     12.08.2008  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_SSV_H
#define _X_SSV_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

//  QAC: allow more than 120 chars for better readability
//PRQA S 2217 ++

// system supervisor (SSV) status: error flag values
#define X_SSV_ERR_UEMAX       (0x00000001u)              // error flag: supply voltage UE to high
#define X_SSV_ERR_UEMIN       (0x00000002u)              // error flag: supply voltage UE to low
#define X_SSV_ERR_USYSMAX     (0x00000004u)              // error flag: system voltage to high
#define X_SSV_ERR_USYSMIN     (0x00000008u)              // error flag: system voltage to low
#define X_SSV_ERR_WD_USER     (0x00000010u)              // error flag: user watchdog error
#define X_SSV_ERR_WD_SYS      (0x00000020u)              // error flag: system watchdog error
#define X_SSV_ERR_HDRST       (0x00000040u)              // error flag: HDRST signal detected (e.g. CPU watchdog)
#define X_SSV_ERR_CONFIG      (0x00000080u)              // error flag: configuration data

// system supervisor (SSV) status: last CPU reset cause
#define X_SSV_CPU_RESET_PWON  (0x00000001u)              // last CPU reset type: power on reset
#define X_SSV_CPU_RESET_SSV   (0x00000002u)              // last CPU reset type: supervisor reset
#define X_SSV_CPU_RESET_SOFT  (0x00000004u)              // last CPU reset type: software reset
#define X_SSV_CPU_RESET_WD    (0x00000008u)              // last CPU reset type: cpu watchdog reset

// system supervisor (SSV) status: SSV error that caused CPU reset
#define X_SSV_CPURST_UEMAX    (X_SSV_ERR_UEMAX << 8)     // CPU reset: supply voltage UE to high
#define X_SSV_CPURST_UEMIN    (X_SSV_ERR_UEMIN << 8)     // CPU reset: supply voltage UE to low
#define X_SSV_CPURST_USYSMAX  (X_SSV_ERR_USYSMAX << 8)   // CPU reset: system voltage to high
#define X_SSV_CPURST_USYSMIN  (X_SSV_ERR_USYSMIN << 8)   // CPU reset: system voltage to low
#define X_SSV_CPURST_WD_USER  (X_SSV_ERR_WD_USER << 8)   // CPU reset: user watchdog error
#define X_SSV_CPURST_WD_SYS   (X_SSV_ERR_WD_SYS << 8)    // CPU reset: system watchdog error
#define X_SSV_CPURST_HDRST    (X_SSV_ERR_HDRST << 8)     // CPU reset: HDRST signal detected (TriCore internal Watchdog)
#define X_SSV_CPURST_CONFIG   (X_SSV_ERR_CONFIG << 8)    // CPU reset: configuration data

// system supervisor (SSV) status: last SSV reset cause
#define X_SSV_RESET_POR       (0x00010000u)              // SSV power on reset
#define X_SSV_RESET_EXTR      (0x00020000u)              // SSV external reset (CPU software reset)
#define X_SSV_RESET_BOR       (0x00040000u)              // SSV brown out reset
#define X_SSV_RESET_WDR       (0x00080000u)              // SSV system watchdog reset
#define X_SSV_RESET_JTR       (0x00100000u)              // JTAG reset
#define X_SSV_RESET_SOFT      (0x00800000u)              // SSV software reset

// trigger system supervisor watchdog:
#define X_SSV_TRIGGER         (0u)                       // toggle SSV watchdog trigger line
#define X_SSV_TRIGGER_AUTO    (1u)                       // toggle SSV WD trigger line and consider min. WD time window
#define X_SSV_SET_TRIGGER_LO  (0u)                       // set SSV watchdog trigger line low
#define X_SSV_SET_TRIGGER_HI  (1u)                       // set SSV watchdog trigger line high

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_ssv.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

typedef struct
{
   uint16 u16_WDmin;             // user watchdog min time in 0.5 milli seconds
   uint16 u16_WDmax;             // user watchdog max time in 0.5 milli seconds
   uint8  u8_UEmin;              // voltage UE min value in 0.25V
   uint8  u8_UEmax;              // voltage UE max value in 0.25V
   uint8  u8_RelOff;             // error reaction: relais off (see also: SSV status error bits)
   uint8  u8_Reset;              // error reaction: system reset (see also: SSV status error bits)
} T_x_ssv_config;

typedef struct
{
   uint16 u16_Version;           // supervisor version information (format V0.00r0)
   uint16 u16_SysError;          // system error flags
   uint32 u32_LastReset;         // information about last system reset
} T_x_ssv_status;



/* -- Function Prototypes ------------------------------------------------- */

sint16 x_ssv_init(const T_x_ssv_config* const opt_SupervisorConfig);    // init system supervisor
sint16 x_ssv_get_status(T_x_ssv_status* const opt_SupervisorStatus);    // get system supervisor status
sint16 x_ssv_trigger(const uint16 ou16_TriggerType);                    // send SSV user WD trigger signal
sint16 x_ssv_set_trigger(const uint16 ou16_TriggerState);               // set SSV user WD trigger signal low or high
void   x_ssv_reset(void);                                               // system reset


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_SSV_H */
