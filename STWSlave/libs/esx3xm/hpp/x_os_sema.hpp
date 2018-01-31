//-----------------------------------------------------------------------------
/*!
   \file        x_os_sema.hpp
   \brief       CPP namespace extention for x_os_sema.h

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

#ifndef __X_OS_SEMA_HPP
#define __X_OS_SEMA_HPP



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
stw_types::sint16 x_os_sema_init(T_x_os_sema* const opt_Semaphore, const stw_types::uint16 ou16_Count);

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
stw_types::sint16 x_os_sema_close(T_x_os_sema* const opt_Semaphore);

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
stw_types::sint16 x_os_sema_get(T_x_os_sema* const opt_Semaphore, const stw_types::uint32 ou32_Timeout);

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
stw_types::sint16 x_os_sema_release(T_x_os_sema* const opt_Semaphore);


#endif  // __X_OS_SEMA_HPP
