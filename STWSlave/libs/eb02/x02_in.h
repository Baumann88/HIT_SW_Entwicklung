//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x02_in.h
   \brief      digital input functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     23.04.2007  Baldauf
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X02_IN_H
#define _X02_IN_H

/* -- Includes ------------------------------------------------------------ */
#include "x_stdtypes.h"
#include "x_in.h"

#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X02_IN_CH_MAX                  (12u)             // number of expansion board eb02 outputs
#define X02_IN_01                      (0u)              // input channel numbers
#define X02_IN_02                      (1u)
#define X02_IN_03                      (2u)
#define X02_IN_04                      (3u)
#define X02_IN_05                      (4u)
#define X02_IN_06                      (5u)
#define X02_IN_07                      (6u)
#define X02_IN_08                      (7u)
#define X02_IN_09                      (8u)
#define X02_IN_10                      (9u)
#define X02_IN_11                      (10u)
#define X02_IN_12                      (11u)

#define X02_IN_TYPE_DIGITAL            (0x0000u)         // input is digital type
#define X02_IN_TYPE_EVENT_RISING       (0x0001u)         // input is EVENT type (rising edge)
#define X02_IN_TYPE_EVENT_FALLING      (0x0002u)         // input is EVENT type (falling edge)
#define X02_IN_TYPE_EVENT_BOTH         (0x0003u)         // input is EVENT type (both edges)
#define X02_IN_TYPE_VOLTAGE_40V        (0x0070u)         // input is voltage type (40V range)

#define X02_IN_TYPE_INCREMENTAL       (0x0100u)           // input is incremental type
#define X02_IN_TYPE_FREQUENCY         (0x0400u)

#define X02_IN_CIRCUIT_ACTIVE_HIGH     (0x0000u)         // input is active high
#define X02_IN_CIRCUIT_ACTIVE_LOW      (0x0001u)         // input is active low
#define X02_IN_CIRCUIT_PULL_UP         (0x0002u)         // use pull up circuit
#define X02_IN_CIRCUIT_PULL_DOWN       (0x0004u)         // use pull down circuit

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x02_in.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x02_in_EventCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Slot, const uint16 ou16_Channel);

typedef T_x_in_status  T_x02_in_status;

/* -- Function Prototypes ------------------------------------------------- */
sint16 x02_in_init (const uint16 ou16_Slot, const uint16 ou16_Channel,
                    const uint16 ou16_Type, const uint16 ou16_FilterConfig,
                          uint16 ou16_InputCircuit, const uint32 ou32_CallbackParameter,
                    const PR_x02_in_EventCallback opr_EventCallback);
sint16 x02_in_get_value(const uint16 ou16_Slot, const uint16 ou16_Channel,
                        sint32 * const ops32_Value);
sint16 x02_in_get_raw_value(const uint16 ou16_Slot, const uint16 ou16_Channel,
                            sint32 * const ops32_Value);
sint16 x02_in_get_status(const uint16 ou16_Slot, const uint16 ou16_Channel, T_x02_in_status * const opt_Status);
sint16 x02_in_set_threshold(const uint16 ou16_Slot, const uint16 ou16_Channel,
                            const sint32 os32_OnValue, const sint32 os32_OffValue);
sint16 x02_in_set_counter(const uint16 ou16_Slot, const uint16 ou16_Channel, const sint32 os32_Value);
sint16 x02_in_get_counter(const uint16 ou16_Slot, const uint16 ou16_Channel, sint32 * const ops32_Value);

// deprecated api functions - may no longer be supported in further releases
sint32 x02_in_reset_inc(const uint32 ou32_Slot, const uint32 ou32_Channel) __attribute__ ((deprecated));
sint32 x02_in_set_inc_threshold(const uint32 ou32_Slot, const uint32 ou32_Channel,
                                const uint32 ou32_ThresholdHigh, const uint32 ou32_ThresholdLow) __attribute__ ((deprecated));


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
