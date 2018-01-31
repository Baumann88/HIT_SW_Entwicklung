//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_os.h
   \brief      STW RTOS for TriCore systems

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     30.11.2004  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_OS_H
#define _X_OS_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_os_types.h"

// include also header for optional OS modules:
#include "x_os_mbox.h"
#include "x_os_mutex.h"
#include "x_os_sema.h"
#include "x_os_signal.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// memory types for task stack allocation:
#define X_OS_HEAP_DEFAULT        ((uint16)gu32_MemClassDefault)   // big but slow external heap memory
#define X_OS_HEAP_FAST           ((uint16)gu32_MemClassSysIntern) // fast but small onchip heap memory


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_os.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

typedef struct
{
   uint16         u16_Priority;        // task priority [0..X_OS_MAX_TASK_PRIO]
   PR_x_os_task   pr_Task;             // task function pointer
   void*          pv_Parameter;        // parameter passed to task function
   uint32         u32_TimeDelay;       // delay time in task ticks before 1st call (0 = suspend task)
   uint32         u32_TimeInterval;    // intervall time after 1st task call
   uint32         u32_StackSize;       // task stack size in byte
   uint32         u32_Permissions;     // task data access permission
} T_x_os_task_config;

/* -- Global Variables ---------------------------------------------------- */
/* These MemClass indexes are defined in the Linker Script */
extern const uint32 gu32_MemClassDefault;
extern const uint32 gu32_MemClassSysIntern;

/* -- Function Prototypes ------------------------------------------------- */

sint16 x_os_init(const uint32 ou32_MemClass);
sint16 x_os_start(const uint32 ou32_TimerTick_us);
sint16 x_os_install_task(const uint16 ou16_Priority, const uint32 ou32_TimeInterval,
                        const uint32 ou32_TimeDelay, const PR_x_os_task opr_Task, const uint32 ou32_StackSize);
sint16 x_os_set_task_timer(const uint32 ou32_TimeInterval, const uint32 ou32_TimeDelay);
void x_os_wait_for_events(void);
void x_os_wait_period(void);
void x_os_sleep(const uint32 ou32_TimeDelay);
uint32 x_os_enter_critical(void);
void x_os_leave_critical(const uint32 ou32_PreviousState);
void x_os_set_event_mask(const uint32 ou32_NewEventMask);
void x_os_get_event_mask(uint32* const opu32_EventMask);
void x_os_set_events(const uint32 ou32_NewEvents);
uint32 x_os_get_events(void);
sint16 x_os_check_task_stack(uint32* const opu32_UnusedStackSize);
sint16 x_os_get_status(T_x_os_status * const opt_Status);


// x_os_ext functions
sint16 x_os_install_task_ext(const T_x_os_task_config * const opt_TaskConfig, void ** oppv_Handle);
sint16 x_os_set_task_timer_ext(void * const opv_Handle, const uint32 ou32_TimeInterval, const uint32 ou32_TimeDelay);
sint16 x_os_check_task_stack_ext(void * const opv_Handle, uint32* const opu32_UnusedStackSize);

sint16 x_os_suspend_task(void * const opv_Handle);
sint16 x_os_resume_task(void * const opv_Handle);
sint16 x_os_delete_task(void * const opv_Handle);


#endif  //__cplusplus


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_OS_H */
