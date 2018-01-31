//-----------------------------------------------------------------------------
/*!
   \file        x_os_signal.hpp
   \brief       CPP namespace extention for x_os_signal.h

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

#ifndef __X_OS_SIGNAL_HPP
#define __X_OS_SIGNAL_HPP



/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

//-----------------------------------------------------------------------------
/*!
   \brief    This function initialize a signal object

   \ingroup  x_os

   \param    opt_Signal    pointer to signal object that should be initialized
   \param    ou32_Signals  initial signal state

   \return   C_NO_ERR      terminated with no error
             C_CONFIG      pointer to signal object not valid
             C_NOACT       function called from ISR handler

   \created  27.11.2008  Herb

*/
//-----------------------------------------------------------------------------
stw_types::sint16 x_os_signal_init(T_x_os_signal* const opt_Signal, const stw_types::uint32 ou32_Signals);

//-----------------------------------------------------------------------------
/*!
   \brief    This function close (invalidate) a signal object

   \ingroup  x_os

   \param    opt_Signal    pointer to signal object that should be closed

   \return   C_NO_ERR      terminated with no error
             C_CONFIG      pointer to signal object not valid
             C_WARN        not deleted: task(s) are waiting for this signal
             C_NOACT       function called from ISR handler

   \created  27.11.2008  Herb

*/
//-----------------------------------------------------------------------------
stw_types::sint16 x_os_signal_close(T_x_os_signal* const opt_Signal);

//-----------------------------------------------------------------------------
/*!
   \brief    This function check signals, wait for signals if not valid

   \ingroup  x_os

   \param    opt_Signal        pointer to signal object
   \param    ou32_SignalMask   defines a signal pattern waiting for
   \param    ou16_Mode         X_OS_SIGNAL_MODE_ALL: all bits from ou32_SignalMask must be set \n
                               X_OS_SIGNAL_MODE_ANY: any bit from ou32_SignalMask must be set
                               X_OS_SIGNAL_MODE_RESET: reset all signals used by the calling task
   \param    opu32_Signals     returns signals that made this task ready (set NULL if not needed)
   \param    ou32_TimeOut      timeout value in OS ticks, 0 = no timeout, wait for ever
                               X_OS_SIGNAL_NOWAIT = do not suspend, return always immediately

   \return   C_NO_ERR      terminated with no error
             C_CONFIG      pointer to signal object or ou16_Mode not valid
             C_BUSY        failed to receive signal, timeout occurred
             C_NOACT       function called from ISR handler or inside critical section

   \created  27.11.2008  Herb

*/
//-----------------------------------------------------------------------------
stw_types::sint16 x_os_signal_wait_for(T_x_os_signal* const opt_Signal, const stw_types::uint32 ou32_SignalMask, const stw_types::uint16 ou16_Mode,
                                       stw_types::uint32* const opu32_Signals, const stw_types::uint32 ou32_TimeOut);

//-----------------------------------------------------------------------------
/*!
   \brief    This function send (modify) signals inside a signal object

   \ingroup  x_os

   \param    opt_Signal       pointer to signal object
   \param    ou32_Signals     the signal bits to be set/reset
   \param    ou32_SignalMask  masks valid ou32_Signals bit positions

   \return   C_NO_ERR      terminated with no error
             C_CONFIG      pointer to signal object not valid

   \created  27.11.2008  Herb

*/
//-----------------------------------------------------------------------------
stw_types::sint16 x_os_signal_send(T_x_os_signal* const opt_Signal, const stw_types::uint32 ou32_Signals, const stw_types::uint32 ou32_SignalMask);



#endif  // __X_OS_SIGNAL_HPP
