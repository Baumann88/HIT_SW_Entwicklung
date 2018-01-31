//-----------------------------------------------------------------------------
/*!
   \file        x_os_mutex.hpp
   \brief       CPP namespace extention for x_os_mutex.h

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

#ifndef __X_OS_MUTEX_HPP
#define __X_OS_MUTEX_HPP



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
stw_types::sint16 x_os_mutex_init(T_x_os_mutex* const opt_Mutex);

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
stw_types::sint16 x_os_mutex_close(T_x_os_mutex* const opt_Mutex);

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
stw_types::sint16 x_os_mutex_get(T_x_os_mutex* const opt_Mutex, const stw_types::uint32 ou32_TimeOut);

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
stw_types::sint16 x_os_mutex_release(T_x_os_mutex* const opt_Mutex);



#endif  // __X_OS_MUTEX_HPP
