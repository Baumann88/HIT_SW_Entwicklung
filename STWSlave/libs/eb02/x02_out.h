//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x02_out.h
   \brief      output functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     23.04.2007  Baldauf
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X02_OUT_H
#define _X02_OUT_H

/* -- Includes ------------------------------------------------------------ */
#include "x_stdtypes.h"
#include "x_out.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X02_ON                         (1)
#define X02_OFF                        (0)

#define X02_OUT_CH_MAX                 (1u)           // number of expansion board eb02 outputs
#define X02_OUT_01                     (0)            // fixed output channel number
#define X02_OUT_CHANNEL                (0)            // fixed output channel number

#define X02_OUT_TYPE_DIGITAL           (0u)           // output is of digital type

#define X02_OUT_STATE_NO_ERROR         (0u)           // output state: ok
#define X02_OUT_STATE_OVERCURRENT      (1u)           // output state: over current error flag

#define X02_OUT_EVENT_OVERCURRENT      (0u)           // output signals overcurrent error
#define X02_OUT_EVENT_RECOVERY         (1u)           // output signals "ready to recover"


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x02_out.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x02_out_ErrorCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Slot, const uint16 ou16_Channel, const uint16 ou16_Event);
typedef T_x_out_status T_x02_out_status;


/* -- Function Prototypes ------------------------------------------------- */
sint16 x02_out_init(const uint16 ou16_Slot, const uint16 ou16_Channel,
                    const uint16 ou16_Type, const sint32 os32_MaxValue,
                    const uint32 ou32_CallbackParameter,
                    const PR_x02_out_ErrorCallback opr_ErrorCallback);

sint16 x02_out_set_value(const uint16 ou16_Slot, const uint16 ou16_Channel, const sint32 os32_Value);
sint16 x02_out_reset_error(const uint16 ou16_Slot, const uint16 ou16_Channel);
sint16 x02_out_get_status(const uint16 ou16_Slot, const uint16 ou16_Channel, T_x02_out_status * const opt_Status );


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
