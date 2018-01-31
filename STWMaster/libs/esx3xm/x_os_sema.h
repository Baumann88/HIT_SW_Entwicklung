//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_os_sema.h
   \brief      STW RTOS extension: counting semaphore functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     27.11.2008  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_OS_SEMA_H
#define _X_OS_SEMA_H

/* -- Includes ------------------------------------------------------------ */

#ifndef _X_OS_H
#ifndef _X_OS_SEMA_C
 #error do not include this header - use x_os.h instead
#endif
#endif

#include "x_os_types.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// this define disables the suspend feature
// x_os_get_semaphore() returns immediately if semaphore is not available
#define X_OS_SEMAPHORE_NOWAIT    X_OS_NOWAIT

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_os_sema.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

//-----------------------------------------------------------------------------
/*!
   \brief    This function initialize a counting semaphore object.

   \ingroup  x_os

   \param    opt_Semaphore  pointer to semaphore object that should be initialized
   \param    ou16_Count     ou16_Count > 0 means the semaphore/resource is available \n
                            binary semaphore should be initialized with ou16_Count = 1

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to semaphore object not valid
             C_NOACT     function called from ISR handler

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_sema_init(T_x_os_sema* const opt_Semaphore, const uint16 ou16_Count);

//-----------------------------------------------------------------------------
/*!
   \brief    close (invalidate) a counting semaphore object.

   \ingroup  x_os

   \param    opt_Semaphore  pointer to semaphore object that should be closed

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to semaphore object not valid
             C_WARN      not deleted: task(s) are waiting for this semaphore
             C_NOACT     function called from ISR handler

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_sema_close(T_x_os_sema* const opt_Semaphore);

//-----------------------------------------------------------------------------
/*!
   \brief    obtain semaphore object, wait if semaphore is not available.

   \ingroup  x_os

   \param    opt_Semaphore     pointer to semaphore object
   \param    ou32_Timeout      timeout value in OS ticks, 0 = no timeout (wait forever)
             X_OS_SEMAPHORE_NOWAIT = never wait for semaphore

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to semaphore object not valid
             C_BUSY      failed to acquire semaphore, timeout occurred
             C_NOACT     function called from ISR handler or inside critical section

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_sema_get(T_x_os_sema* const opt_Semaphore, const uint32 ou32_Timeout);

//-----------------------------------------------------------------------------
/*!
   \brief    release semaphore object.

   \ingroup  x_os

   \param    opt_Semaphore  pointer to semaphore object

   \return   C_NO_ERR       terminated with no error
             C_CONFIG       pointer to semaphore object not valid
             C_OVERFLOW     semaphore release counter overflow

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_sema_release(T_x_os_sema* const opt_Semaphore);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_OS_SEMA_H */
