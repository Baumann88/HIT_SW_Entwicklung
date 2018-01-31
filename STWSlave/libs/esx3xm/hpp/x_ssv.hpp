//-----------------------------------------------------------------------------
/*!
   \file        x_ssv.hpp
   \brief       CPP namespace extention for x_ssv.h

   This header was automatically created. DO NOT EDIT!

   \implementation
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     by hpp_generator.pl
   \endimplementation


   \internal
   \history
   Date(dd.mm.yyyy)  Author                Description
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef __X_SSV_HPP
#define __X_SSV_HPP



/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint16 u16_WDmin;             // user watchdog min time in 0.5 milli seconds
   stw_types::uint16 u16_WDmax;             // user watchdog max time in 0.5 milli seconds
   stw_types::uint8  u8_UEmin;              // voltage UE min value in 0.25V
   stw_types::uint8  u8_UEmax;              // voltage UE max value in 0.25V
   stw_types::uint8  u8_RelOff;             // error reaction: relais off (see also: SSV status error bits)
   stw_types::uint8  u8_Reset;              // error reaction: system reset (see also: SSV status error bits)
} T_x_ssv_config;

typedef struct
{
   stw_types::uint16 u16_Version;           // supervisor version information (format V0.00r0)
   stw_types::uint16 u16_SysError;          // system error flags
   stw_types::uint32 u32_LastReset;         // information about last system reset
} T_x_ssv_status;



/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_ssv_init(const T_x_ssv_config* const opt_SupervisorConfig);    // init system supervisor
stw_types::sint16 x_ssv_get_status(T_x_ssv_status* const opt_SupervisorStatus);    // get system supervisor status
stw_types::sint16 x_ssv_trigger(const stw_types::uint16 ou16_TriggerType);                    // send SSV user WD trigger signal
stw_types::sint16 x_ssv_set_trigger(const stw_types::uint16 ou16_TriggerState);               // set SSV user WD trigger signal low or high
void   x_ssv_reset(void);                                               // system reset


#endif  // __X_SSV_HPP
