//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_os_mbox.h
   \brief      STW RTOS extension: mailbox functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     27.11.2008  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_OS_MBOX_H
#define _X_OS_MBOX_H

/* -- Includes ------------------------------------------------------------ */

#ifndef _X_OS_H
#ifndef _X_OS_MBOX_C
 #error do not include this header - use x_os.h instead
#endif
#endif

#include "x_os_types.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// this define disables the suspend feature
// x_os_get_message() returns immediately if message is not available
#define X_OS_MBOX_NOWAIT            X_OS_NOWAIT

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_os_mbox.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

//-----------------------------------------------------------------------------
/*!
   \brief    This function initialize a mailbox object

   \ingroup  x_os

   \param    opt_Mailbox pointer to mailbox object which should be initialized
   \param    opv_Message pointer to initial message data

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mailbox object not valid
             C_NOACT     function called from ISR handler

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mbox_init(T_x_os_mbox* const opt_Mailbox, void* const opv_Message);

//-----------------------------------------------------------------------------
/*!
   \brief    This function close (invalidate) a mailbox object

   \ingroup  x_os

   \param    opt_Mailbox pointer to mailbox object that should be closed

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mailbox object not valid
             C_WARN      not deleted: task(s) are waiting for this mailbox
             C_NOACT     function called from ISR handler

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mbox_close(T_x_os_mbox* const opt_Mailbox);

//-----------------------------------------------------------------------------
/*!
   \brief    This function gets a message, wait if message is not available

   \ingroup  x_os

   \param    opt_Mailbox pointer to mailbox object
   \param    oppv_Message   pointer reference to message data
   \param    ou32_TimeOut   timeout value in OS ticks, 0 = no timeout
                            X_OS_MBOX_NOWAIT = never wait for message

   \return   C_NO_ERR    terminated with no error
             C_CONFIG    pointer to mailbox object or oppv_Message invalid
             C_BUSY      failed to acquire mailbox, timeout occurred
             C_NOACT     function called from ISR handler or inside critical section

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mbox_get_message(T_x_os_mbox* const opt_Mailbox, void** const oppv_Message, const uint32 ou32_TimeOut);

//-----------------------------------------------------------------------------
/*!
   \brief    This function sends a message

   \ingroup  x_os

   \param    opt_Mailbox    pointer to mailbox object
   \param    opv_Message    pointer to message data that should be send
   \param    ou16_Options   send options:
                            X_OS_MBOX_SEND_DEFAULT -> send message to waiting task with highest priority
                            X_OS_MBOX_SEND_BROADCAST -> send message to any waiting task

   \return   C_NO_ERR       terminated with no error
             C_CONFIG       pointer to mailbox object or oppv_Message invalid
             C_OVERFLOW     mailbox overflow, message not delivered

   \created  18.11.2008  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_os_mbox_send_message(T_x_os_mbox* const opt_Mailbox, void* const opv_Message, const uint16 ou16_Options);


#endif  //__cplusplus


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_OS_H */
