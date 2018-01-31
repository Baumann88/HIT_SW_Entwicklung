//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x05_in.h
   \brief      input functions

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

#ifndef _X05_IN_H
#define _X05_IN_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_in.h"


#ifdef __cplusplus
extern "C" {
#endif

/* -- Defines ------------------------------------------------------------- */
#define X05_IN_CH_MAX                 (4u)
#define X05_IN_01                     (0u)
#define X05_IN_02                     (1u)
#define X05_IN_03                     (2u)
#define X05_IN_04                     (3u)

#define X05_IN_TYPE_DIGITAL           (0x0000u)          // input is digital type
#define X05_IN_TYPE_EVENT_RISING      (0x0001u)          // input is EVENT type (rising edge)
#define X05_IN_TYPE_EVENT_FALLING     (0x0002u)          // input is EVENT type (falling edge)
#define X05_IN_TYPE_EVENT_BOTH        (0x0003u)          // input is EVENT type (both edges)
#define X05_IN_TYPE_VOLTAGE_40V       (0x0070u)         // input is voltage type (40V range)

#define X05_IN_CIRCUIT_ACTIVE_HIGH    (0x0000u)          // input is active high
#define X05_IN_CIRCUIT_ACTIVE_LOW     (0x0001u)          // input is active low
#define X05_IN_CIRCUIT_PULL_UP        (0x0002u)          // use pull up circuit
#define X05_IN_CIRCUIT_NO_PULL_UP     (0x0000u)          // use no pull up circuit
#define X05_IN_CIRCUIT_PULL_DOWN      (0x0004u)          // use pull down circuit
#define X05_IN_CIRCUIT_NO_PULL_DOWN   (0x0000u)          // use no pull down circuit



/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x05_in.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x05_in_EventCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Slot, const uint16 ou16_Channel);
typedef T_x_in_status  T_x05_in_status;


/* -- Function Prototypes ------------------------------------------------- */
sint16 x05_in_init(const uint16 ou16_Slot, const uint16 ou16_Channel,
                   const uint16 ou16_Type, const uint16 ou16_FilterConfig,
                   const uint16 ou16_InputCircuit, const uint32 ou32_CallbackParameter,
                   const PR_x05_in_EventCallback opr_EventCallback);
sint16 x05_in_get_value(const uint16 ou16_Slot, const uint16 ou16_Channel, sint32 * const ops32_Value);
sint16 x05_in_get_raw_value(const uint16 ou16_Slot, const uint16 ou16_Channel, sint32 * const ops32_Value);
sint16 x05_in_get_status(const uint16 ou16_Slot, const uint16 ou16_Channel, T_x05_in_status* const opt_Status);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
