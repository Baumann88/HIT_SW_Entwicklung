//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_os_mutex.h
   \brief      STW RTOS extension: recursive mutex functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     27.11.2008  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_OS_MUTEX_H
#define _X_OS_MUTEX_H

/* -- Includes ------------------------------------------------------------ */

#ifndef _X_OS_H
#ifndef _X_OS_MUTEX_C
 #error do not include this header - use x_os.h instead
#endif
#endif

#include "x_os_types.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// this define disables the suspend feature
// x_os_get_mutex() returns immediately if mutex is not available
#define X_OS_MUTEX_NOWAIT        X_OS_NOWAIT

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_os_mutex.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

//-----------------------------------------------------------------------------
/*!
   \brief    This function initialize a mutex object

   \ingroup  x_os

   \param    opt_Mutex   pointer to mutex object that should be initialized

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mutex object not valid
             C_NOACT     function called from ISR handler

   \created  25.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mutex_init(T_x_os_mutex* const opt_Mutex);

//-----------------------------------------------------------------------------
/*!
   \brief    This function close (invalidate) a mutex object

   \ingroup  x_os

   \param    opt_Mutex   pointer to mutex object that should be closed

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mutex object not valid
             C_WARN      not deleted: task(s) are waiting for this mutex
             C_NOACT     function called from ISR handler

   \created  25.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mutex_close(T_x_os_mutex* const opt_Mutex);

//-----------------------------------------------------------------------------
/*!
   \brief    This function obtain a mutex object, wait if mutex is not available

   \ingroup  x_os

   \param    opt_Mutex      pointer to mutex object
   \param    ou32_TimeOut   timeout value in OS ticks, 0 = no timeout
                            X_OS_MUTEX_NOWAIT = never wait for mutex

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mutex object not valid
             C_BUSY      mutex not available, timeout occurred
             C_OVERFLOW  mutex recursive call overflow
             C_NOACT     function called from ISR handler or inside critical section

   \created  25.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mutex_get(T_x_os_mutex* const opt_Mutex, const uint32 ou32_TimeOut);

//-----------------------------------------------------------------------------
/*!
   \brief    This function release a mutex object

   \ingroup  x_os

   \param    opt_Mutex   pointer to mutex object

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mutex object not valid
             C_NOACT     function not called from mutex owner

   \created  25.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mutex_release(T_x_os_mutex* const opt_Mutex);



#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_OS_MUTEX_H */
