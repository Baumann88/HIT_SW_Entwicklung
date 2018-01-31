//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x05_out.h
   \brief      output functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     23.01.2008  STW/GW
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   ***   add your log here (above the last entry)   ***
   19.02.2010        STW/GW         new implementation for eb05 \n
   23.01.2008        STW/GW         initial implementation \n
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef _X05_OUT_H
#define _X05_OUT_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_out.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X05_ON                         (1)
#define X05_OFF                        (0)

#define X05_OUT_CH_MAX                 (8u)              // number of expansion board eb05 outputs
#define X05_OUT_01                     (0u)              // channel numbers group 1
#define X05_OUT_02                     (1u)
#define X05_OUT_03                     (2u)
#define X05_OUT_04                     (3u)
#define X05_OUT_05                     (4u)              // channel numbers group 2
#define X05_OUT_06                     (5u)
#define X05_OUT_07                     (6u)
#define X05_OUT_08                     (7u)
#define X05_OUT_ALL                    (0xFFFFu)         // used by error callback on GND error

#define X05_OUT_TYPE_DIGITAL           (0u)              // output is of digital type
#define X05_OUT_TYPE_PWM               (1u)              // output is of PWM type
#define X05_OUT_TYPE_CONTROL_CURRENT   (2u)              // output is of type current control

#define X05_OUT_STATE_OVERCURRENT      (0x0001u)         // output state: over current error flag
#define X05_OUT_STATE_GROUND_ERROR     (0x0002u)         // loss of ground detected
#define X05_OUT_STATE_DIGITAL_FB       (0x0100u)         // output state: digital feedback signal

#define X05_OUT_EVENT_OVERCURRENT      (0u)              // output signals overcurrent error
#define X05_OUT_EVENT_RECOVERY         (1u)              // output signals "ready to recover"
#define X05_OUT_EVENT_GND_ERROR        (2u)              // output signals "loss of ground"

#define X05_OUT_MAX_PWM_FREQ           (1000000u)        // max allowed pwm frequency in mHz
#define X05_OUT_MIN_PWM_FREQ           (5000u)           // min allowed pwm frequency in mHz

#define X05_OUT_RELAY_01               (0u)



/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x05_out.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x05_out_ErrorCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Slot, const uint16 ou16_Channel, const uint16 ou16_Event);
typedef T_x_out_status           T_x05_out_status;
typedef T_x_out_pid_parameters T_x05_out_pid_parameters;

/* -- Function Prototypes ------------------------------------------------- */
sint16 x05_out_set_relay(const uint16 ou16_Slot, const uint16 ou16_Channel, const uint8 ou8_OnOff);
sint16 x05_out_init(const uint16 ou16_Slot, const uint16 ou16_Channel, const uint16 ou16_Type,
                    const sint32 os32_MaxValue, const uint32 ou32_CallbackParameter,
                    const PR_x05_out_ErrorCallback opr_ErrorCallback);
sint16 x05_out_set_control_parameters(const uint16 ou16_Slot, const uint16 ou16_Channel,
                                      const T_x05_out_pid_parameters* const opt_Parameters);
sint16 x05_out_get_control_parameters(const uint16 ou16_Slot, const uint16 ou16_Channel,
                                      T_x05_out_pid_parameters* const opt_Parameters);
sint16 x05_out_set_value(const uint16 ou16_Slot, const uint16 ou16_Channel, const sint32 os32_Value);
sint16 x05_out_set_frequency(const uint16 ou16_Slot, const uint16 ou16_Channel, const uint32 ou32_Frequency);
sint16 x05_out_get_status(const uint16 ou16_Slot, const uint16 ou16_Channel, T_x05_out_status* const opt_Status );
sint16 x05_out_get_current(const uint16 ou16_Slot, const uint16 ou16_Channel, sint32* const ops32_Current );
sint16 x05_out_get_voltage(const uint16 ou16_Slot, const uint16 ou16_Channel, sint32* const ops32_Voltage );
sint16 x05_out_init_gnd_error(const uint16 ou16_Slot, const uint32 ou32_CallbackParameter,
                              const PR_x05_out_ErrorCallback opr_ErrorCallback);
sint16 x05_out_reset_gnd_error(const uint16 ou16_Slot);
sint16 x05_out_reset_oc_error(const uint16 ou16_Slot, const uint16 ou16_Channel);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
