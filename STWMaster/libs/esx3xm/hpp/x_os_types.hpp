//-----------------------------------------------------------------------------
/*!
   \file        x_os_types.hpp
   \brief       CPP namespace extention for x_os_types.h

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

#ifndef __X_OS_TYPES_HPP
#define __X_OS_TYPES_HPP




//-----------------------------------------------------------------------------
/*!
   \brief   Signature of a task function that can be installed into the task system.

   RTOS user tasks can be used to implement parallel multi tasking. There are two possible structures for a user task.

   \par Standart RTOS task
   This is reccomended for new applications. The basic characteristic is the endless loop. As the task is started only
   once the overhead of the functions prolog and epilog can be neglected. \n
   All local variables keeps their value as the scope of the task is never left. The task can be suspended at any
   position.

   \code
   void rtos_task(void * const opv_TaskParameter)
   {
      // place for local variable declarations - as we never leave the task function  all
      // local variables behave like static variables

      // do task initialization stuff here...

      while (TRUE) // this is the endless loop
      {
         // do the job...

         // suspend task ... with one of the available function (x_os_sleep, x_os_wait_period, x_os_wait_for_events)
         x_os_sleep(1000);
      }
   }
   \endcode


   \par Classic timer task
   This task structure is for compatibility only. The basic characteristic is that this function has no endless loop
   and returns at the end of the function. \n
   When the function returns the task is suspended implicit by x_os_wait_for_events. If the task shall be resumed, the
   function is started again from the beginning. \n
   Thus the functions prolog and epilog is executed every time. Furthermore local variables can not be used to store
   information that must be present for several task calls as the scope of the task is left every time. If such
   variables are needed anyway they must be declared as static.

   \code
   void timer_task(void * const opv_TaskParameter)
   {
      // place for local variable declarations - if a variable should hold the value
      // from the last task call it must be declared static
      static uint32 u32_FirstRun = TRUE;

      if (u32_FirstRun == TRUE)
      {
         u32_FirstRun = FALSE;

         // do task initialization stuff here...
      }
      else
      {
         // do the job...
      }

      // leave the task function and dispatch to next task ready to run
   }
   \endcode


   \note
   There is no way to set the value of opv_TaskParameter. It's value is always NULL.

   \param[in]        opv_TaskParameter          parameter passed to the task function.

   \return
   void
*/
//-----------------------------------------------------------------------------
typedef void (*PR_x_os_task)(void * const opv_TaskParameter);


typedef struct                // event control data structure
{
   stw_types::uint16   u16_EventType;    // event type
   stw_types::uint16   u16_Count;        // semaphore counter
   void*    pv_Message;       // message pointer
   stw_types::uint32   au32_WaitingTask[X_OS_TASK_FLAGREG_NUM];  // waiting task
} T_x_os_event_type;


typedef struct
{
   stw_types::uint16 u16_State;                   // state of task system (see defines X_OS_NOT_INIT; X_OS_INIT; X_OS_RUNNING)
   stw_types::uint16 u16_TaskCount;               // number of installed tasks
   stw_types::uint32 u32_MemClass;                // see parameter ou32_MemClass of function x_os_init
   stw_types::uint32 u32_TimerTickUs;             // scheduler tick in micro sec, range 200..1000000
} T_x_os_status;


typedef T_x_os_event_type  T_x_os_mbox;      // messagebox object type
typedef T_x_os_event_type  T_x_os_mutex;     // mutex object type
typedef T_x_os_event_type  T_x_os_sema;      // semaphore object type
typedef T_x_os_event_type  T_x_os_signal;    // signal object type


#endif  // __X_OS_TYPES_HPP
