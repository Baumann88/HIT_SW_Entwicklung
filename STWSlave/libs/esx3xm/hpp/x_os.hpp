//-----------------------------------------------------------------------------
/*!
   \file        x_os.hpp
   \brief       CPP namespace extention for x_os.h

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

#ifndef __X_OS_HPP
#define __X_OS_HPP



/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint16         u16_Priority;        // task priority [0..X_OS_MAX_TASK_PRIO]
   PR_x_os_task   pr_Task;             // task function pointer
   void*          pv_Parameter;        // parameter passed to task function
   stw_types::uint32         u32_TimeDelay;       // delay time in task ticks before 1st call (0 = suspend task)
   stw_types::uint32         u32_TimeInterval;    // intervall time after 1st task call
   stw_types::uint32         u32_StackSize;       // task stack size in byte
   stw_types::uint32         u32_Permissions;     // task data access permission
} T_x_os_task_config;

/* -- Global Variables ---------------------------------------------------- */
/* These MemClass indexes are defined in the Linker Script */
extern const stw_types::uint32 gu32_MemClassDefault;
extern const stw_types::uint32 gu32_MemClassSysIntern;

/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_os_init(const stw_types::uint32 ou32_MemClass);
stw_types::sint16 x_os_start(const stw_types::uint32 ou32_TimerTick_us);
stw_types::sint16 x_os_install_task(const stw_types::uint16 ou16_Priority, const stw_types::uint32 ou32_TimeInterval,
                                    const stw_types::uint32 ou32_TimeDelay, const PR_x_os_task opr_Task, const stw_types::uint32 ou32_StackSize);
stw_types::sint16 x_os_set_task_timer(const stw_types::uint32 ou32_TimeInterval, const stw_types::uint32 ou32_TimeDelay);
void x_os_wait_for_events(void);
void x_os_wait_period(void);
void x_os_sleep(const stw_types::uint32 ou32_TimeDelay);
stw_types::uint32 x_os_enter_critical(void);
void x_os_leave_critical(const stw_types::uint32 ou32_PreviousState);
void x_os_set_event_mask(const stw_types::uint32 ou32_NewEventMask);
void x_os_get_event_mask(stw_types::uint32* const opu32_EventMask);
void x_os_set_events(const stw_types::uint32 ou32_NewEvents);
stw_types::uint32 x_os_get_events(void);
stw_types::sint16 x_os_check_task_stack(stw_types::uint32* const opu32_UnusedStackSize);
stw_types::sint16 x_os_get_status(T_x_os_status * const opt_Status);


// x_os_ext functions
stw_types::sint16 x_os_install_task_ext(const T_x_os_task_config * const opt_TaskConfig, void ** oppv_Handle);
stw_types::sint16 x_os_set_task_timer_ext(void * const opv_Handle, const stw_types::uint32 ou32_TimeInterval, const stw_types::uint32 ou32_TimeDelay);
stw_types::sint16 x_os_check_task_stack_ext(void * const opv_Handle, stw_types::uint32* const opu32_UnusedStackSize);

stw_types::sint16 x_os_suspend_task(void * const opv_Handle);
stw_types::sint16 x_os_resume_task(void * const opv_Handle);
stw_types::sint16 x_os_delete_task(void * const opv_Handle);


#endif  // __X_OS_HPP
