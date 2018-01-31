//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_os_types.h
   \brief      generic x_os types used in all software layers

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     30.11.2004  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------
/*!
   \addtogroup     x_os
   \{
*/
//-----------------------------------------------------------------------------

#ifndef _X_OS_TYPES_H
#define _X_OS_TYPES_H

/* -- Includes ------------------------------------------------------------ */

#include "stwtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// OS init states
#define X_OS_NOT_INIT               (0)               // OS is not initialized
#define X_OS_INIT                   (1)               // OS is initialized but not started
#define X_OS_RUNNING                (2)               // OS is initialized and running


#define X_OS_TASK_FLAGREG_NUM       (4)               // number of task flag registers
#define X_OS_TASK_FLAGREG_SIZE      (32)              // size of task flag register
#define X_OS_MAX_TASK               (X_OS_TASK_FLAGREG_NUM*X_OS_TASK_FLAGREG_SIZE)  // max. number of tasks
#define X_OS_MAX_TASK_PRIO          (X_OS_MAX_TASK-1) // max. task priority

#define X_OS_NOWAIT                 (0xFFFFFFFFu)

// send options for x_os_mbox_send_message:
#define X_OS_MBOX_SEND_DEFAULT      (0)   // message received by waiting task with highest priority
#define X_OS_MBOX_SEND_BROADCAST    (1)   // send message broadcast to any waiting task

// mode options for x_os_wait_for_signal:
// X_OS_SIGNAL_MODE_RESET may be ORed with the other settings
#define X_OS_SIGNAL_MODE_ANY        (0)   // signal mode: any signal bits must be set
#define X_OS_SIGNAL_MODE_ALL        (1)   // signal mode: all signal bits must be set
#define X_OS_SIGNAL_MODE_RESET      (2)   // signal mode: reset all signals used by the calling task

// event bits are bit coded
#define X_OS_EVENT_01               (0x00000001u)
#define X_OS_EVENT_02               (0x00000002u)
#define X_OS_EVENT_03               (0x00000004u)
#define X_OS_EVENT_04               (0x00000008u)
#define X_OS_EVENT_05               (0x00000010u)
#define X_OS_EVENT_06               (0x00000020u)
#define X_OS_EVENT_07               (0x00000040u)
#define X_OS_EVENT_08               (0x00000080u)
#define X_OS_EVENT_09               (0x00000100u)
#define X_OS_EVENT_10               (0x00000200u)
#define X_OS_EVENT_11               (0x00000400u)
#define X_OS_EVENT_12               (0x00000800u)
#define X_OS_EVENT_13               (0x00001000u)
#define X_OS_EVENT_14               (0x00002000u)
#define X_OS_EVENT_15               (0x00004000u)
#define X_OS_EVENT_16               (0x00008000u)
#define X_OS_EVENT_17               (0x00010000u)
#define X_OS_EVENT_18               (0x00020000u)
#define X_OS_EVENT_19               (0x00040000u)
#define X_OS_EVENT_20               (0x00080000u)
#define X_OS_EVENT_21               (0x00100000u)
#define X_OS_EVENT_22               (0x00200000u)
#define X_OS_EVENT_23               (0x00400000u)
#define X_OS_EVENT_24               (0x00800000u)
#define X_OS_EVENT_25               (0x01000000u)
#define X_OS_EVENT_26               (0x02000000u)
#define X_OS_EVENT_27               (0x04000000u)
#define X_OS_EVENT_28               (0x08000000u)
#define X_OS_EVENT_29               (0x10000000u)
#define X_OS_EVENT_30               (0x20000000u)
#define X_OS_EVENT_31               (0x40000000u)
#define X_OS_EVENT_32               (0x80000000u)


/* -- Types --------------------------------------------------------------- */

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_os_types.hpp"
}
#else



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
   uint16   u16_EventType;    // event type
   uint16   u16_Count;        // semaphore counter
   void*    pv_Message;       // message pointer
   uint32   au32_WaitingTask[X_OS_TASK_FLAGREG_NUM];  // waiting task
} T_x_os_event_type;


typedef struct
{
   uint16 u16_State;                   // state of task system (see defines X_OS_NOT_INIT; X_OS_INIT; X_OS_RUNNING)
   uint16 u16_TaskCount;               // number of installed tasks
   uint32 u32_MemClass;                // see parameter ou32_MemClass of function x_os_init
   uint32 u32_TimerTickUs;             // scheduler tick in micro sec, range 200..1000000
} T_x_os_status;


typedef T_x_os_event_type  T_x_os_mbox;      // messagebox object type
typedef T_x_os_event_type  T_x_os_mutex;     // mutex object type
typedef T_x_os_event_type  T_x_os_sema;      // semaphore object type
typedef T_x_os_event_type  T_x_os_signal;    // signal object type


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_OS_TYPES_H */

/*! \} */
