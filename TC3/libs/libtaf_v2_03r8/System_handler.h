//-----------------------------------------------------------------------------
/*!
   \file          System_handler.h
   \brief         Provides utility functions to use the system daemon

   Provides utility functions to use the system daemon

   \implementation
   copyright   STW (c) 1999-2010
   license     use only under terms of contract / confidential

   created     06.08.10 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author           Description
   06.08.10          Florian Belser   file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _SYSTEM_HANDLER_H
#define _SYSTEM_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "dbus-utils.h"

/* -- Defines ------------------------------------------------------------- */
#define IGN_OFF 0
#define IGN_ON 1

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ysysd_register_watch_dog(const T_DBUS_Util * const opt_DBusInstance);
extern sint32 ysysd_trigger_watch_dog(const T_DBUS_Util * const opt_DBusInstance);
extern sint32 ysysd_cancel_watch_dog(const T_DBUS_Util * const opt_DBusInstance);
extern sint32 ysysd_get_ignition_status(const T_DBUS_Util * const opt_DBusInstance);
extern sint32 ysysd_request_stay_alive(const T_DBUS_Util * const opt_DBusInstance, const uint32 ou32_DurationSec);

/* -- Implementation ------------------------------------------------------ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* end of SYSTEM_HANDLER_H */
