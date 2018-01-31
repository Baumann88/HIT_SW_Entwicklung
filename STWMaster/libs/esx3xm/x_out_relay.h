//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_out.h
   \brief      output functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     07.04.2011  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_OUT_RELAY_H
#define _X_OUT_RELAY_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_out.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X_OUT_RELAY_CH_MAX          (1u)                    // relay define: max. number of power relay channels
#define X_OUT_RELAY_01              (0u)                    // relay define: main power relay 1

// defines for relay states                                       // Cause for deactivation:
#define X_OUT_RELAY_STATE_OVERCURRENT              (0x0001u)      // power supply over current
#define X_OUT_RELAY_STATE_OVERVOLTAGE              (0x0002u)      // power supply over voltage
#define X_OUT_RELAY_STATE_GND_ERROR                (0x0004u)      // power supply GND offset to high (reserved)
#define X_OUT_RELAY_STATE_SSV_ERROR                (0x0008u)      // SSV error
#define X_OUT_RELAY_STATE_EB_WD_ERROR              (0x0010u)      // expansion board FPGA watchdog (reserved)
#define X_OUT_RELAY_STATE_EB_HW_ERROR              (0x0020u)      // expansion board hardware

#define X_OUT_RELAY_EVENT_RECOVERY                 (0x0000u)      // relay has recovered
#define X_OUT_RELAY_EVENT_OVERCURRENT              (0x0001u)      // power supply over current
#define X_OUT_RELAY_EVENT_OVERVOLTAGE              (0x0002u)      // power supply over voltage
#define X_OUT_RELAY_EVENT_GND_ERROR                (0x0004u)      // power supply GND offset to high (reserved)
#define X_OUT_RELAY_EVENT_SSV_ERROR                (0x0008u)      // SSV error
#define X_OUT_RELAY_EVENT_EB_WD_ERROR              (0x0010u)      // expansion board FPGA watchdog (reserved)
#define X_OUT_RELAY_EVENT_EB_HW_ERROR              (0x0020u)      // expansion board hardware


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_out_relay.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

typedef struct
{
   uint8  u8_OnOff;              // last output state set by software
   sint32 s32_VoltageUb;         // unit mV (filtered, scaled ADC value)
   sint32 s32_VoltageUc;         // unit mV (filtered, scaled ADC value)
   sint32 s32_CurrentI;          // unit uA (filtered, scaled ADC value)
   uint16 u16_RelayState;        // relay error states (or'ed X_OUT_RELAY_STATE_...; 0 = no error currently pending)
   uint16 u16_ErrorFlags;        // relay error flags (sticky relay error states)
} T_x_out_relay_status;


typedef void (*PR_x_out_ErrorRelayCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Channel,
                                            const uint16 ou16_Event);

typedef struct
{
   uint32                        u32_CallbackParameter;
   PR_x_out_ErrorRelayCallback   pr_ErrorCallback;
} T_x_out_relay_config;


/* -- Function Prototypes ------------------------------------------------- */

sint16 x_out_relay_init(const uint16 ou16_Channel, const T_x_out_relay_config * const opt_Config);
sint16 x_out_relay_set(const uint16 ou16_Channel, const uint8 ou8_OnOff);
sint16 x_out_relay_set_all(const uint8 ou8_OnOff);
sint16 x_out_relay_get_status(const uint16 ou16_Channel, T_x_out_relay_status * const opt_Status);
sint16 x_out_relay_reset_error(const uint16 ou16_Channel);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_OUT_H */
