//-----------------------------------------------------------------------------
/*!
   \file          Signal_handler.h
   \brief         Provides utility functions to use ysignald daemon

   Provides utility functions to use the dbus and ysignald daemon

   \implementation
   copyright   STW (c) 1999-20155555
   license     use only under terms of contract / confidential

   created     03.02.15 Andreas Appelt
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   03.02.15          Andreas Appelt    file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _SIGNAL_HANDLER_H
#define _SIGNAL_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
# include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ysignald_internet_con_state (const T_DBUS_Util * const opt_DBusInstance,
                                           const charn * const opcn_SignalArgument);

extern sint32 ysignald_GPS_con_state (const T_DBUS_Util * const opt_DBusInstance,
                                      const charn * const opcn_SignalArgument);

/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

