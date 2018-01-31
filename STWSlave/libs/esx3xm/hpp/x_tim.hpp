//-----------------------------------------------------------------------------
/*!
   \file        x_tim.hpp
   \brief       CPP namespace extention for x_tim.h

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

#ifndef __X_TIM_HPP
#define __X_TIM_HPP



/* -- Types --------------------------------------------------------------- */

// callback function prototype
typedef void (*PR_x_tim_TimerCallback)(const stw_types::uint32 ou32_CallbackParameter, void * const opv_Handle);


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_tim_init(const stw_types::uint16 ou16_Priority, const stw_types::uint32 ou32_CallbackParameter,
                             const PR_x_tim_TimerCallback opr_TimerCallback, void** const oppv_Handle);
stw_types::sint16 x_tim_close(void * const opv_Handle);
stw_types::sint16 x_tim_set(void * const opv_Handle, const stw_types::uint32 ou32_DelayTime, const stw_types::uint32 ou32_CycleTime);


#endif  // __X_TIM_HPP
