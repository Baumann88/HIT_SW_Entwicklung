//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_tim.h
   \brief      user timer functions


   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     05.02.2009  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_TIM_H
#define _X_TIM_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X_TIM_CH_MAX                (1u)        // total number of timer channels

#define X_TIM_PRIO_MAX              (1u)        // total number of different timer priorities
#define X_TIM_PRIO_01               (0u)        // timer priority numbers (lowest)

#define X_TIM_DELAY_MAX             (0xFFFFu)   // max. value for ou32_DelayTime
#define X_TIM_CYCLE_MAX             (0xFFFFu)   // max. value for ou32_CycleTime


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
 
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_tim.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

// callback function prototype
typedef void (*PR_x_tim_TimerCallback)(const uint32 ou32_CallbackParameter, void * const opv_Handle);


/* -- Function Prototypes ------------------------------------------------- */

sint16 x_tim_init(const uint16 ou16_Priority, const uint32 ou32_CallbackParameter,
                 const PR_x_tim_TimerCallback opr_TimerCallback, void** const oppv_Handle);
sint16 x_tim_close(void * const opv_Handle);
sint16 x_tim_set(void * const opv_Handle, const uint32 ou32_DelayTime, const uint32 ou32_CycleTime);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_TIM_H */
