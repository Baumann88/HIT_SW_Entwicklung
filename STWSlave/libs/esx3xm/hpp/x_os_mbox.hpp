//-----------------------------------------------------------------------------
/*!
   \file        x_os_mbox.hpp
   \brief       CPP namespace extention for x_os_mbox.h

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

#ifndef __X_OS_MBOX_HPP
#define __X_OS_MBOX_HPP



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
stw_types::sint16 x_os_mbox_init(T_x_os_mbox* const opt_Mailbox, void* const opv_Message);

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
stw_types::sint16 x_os_mbox_close(T_x_os_mbox* const opt_Mailbox);

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
stw_types::sint16 x_os_mbox_get_message(T_x_os_mbox* const opt_Mailbox, void** const oppv_Message, const stw_types::uint32 ou32_TimeOut);

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
stw_types::sint16 x_os_mbox_send_message(T_x_os_mbox* const opt_Mailbox, void* const opv_Message, const stw_types::uint16 ou16_Options);


#endif  // __X_OS_MBOX_HPP
