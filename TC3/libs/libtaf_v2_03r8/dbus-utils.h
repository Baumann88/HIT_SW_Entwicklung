//-----------------------------------------------------------------------------
/*!
   \file          dbus-utils.h
   \brief         Provides utility functions to use the dbus

   Provides utility functions to use the dbus and dbus daemons

   \implementation
   copyright   STW (c) 1999-2008
   license     use only under terms of contract / confidential

   created     12.10.09 Sven Dittmer
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author         	Description
   10.20.2015        STW/A.Appelt      added UserMessageCallback
   28.08.2013        STW/M.Altthaler   added WhoIsThereCallback
   19.08.2013        STW/M.Altthaler   added NetworkResponseTimeIndicator
   06.08.2013			STW/M.Altthaler	added signal GOODBYE check
   12.10.2009        Sven Dittmer   	file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _DBUS_UTILS_H
#define _DBUS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include <dbus/dbus.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stwtypes.h"
#include "stwerrors.h"
/* -- Defines ------------------------------------------------------------- */
// Set or unset the following switch to produce
// debugging messages
// #define LIBTAF_DEBUG_MSGS 1
/* -- Types --------------------------------------------------------------- */

typedef struct
{
   DBusConnection*  pt_dbus_conn;           // DBUS connection instance
   charn            acn_myNameString[128];   // Name of our application,
                                             // Don't use any special characters, white spaces or new lines!
   charn            acn_myVersion[128];      // Additional value (for HELLO) signal (opt.)
   charn            acn_myStatus[128];       // Additional value (for HELLO) signal (opt.)
   charn            acn_myAddInfo[512];      // Additional value (for HELLO) signal (opt.)
   sint32           s32_myTriginterval;       // Interval time that the ysysd expects us to trigger
   charn            acn_myCMDOnWatchdog[2048];  // Bash cmd that should be executed by the ysysd in
                                                // case we do not trigger it in time.
} T_DBUS_Util;

typedef void (* PR_LIBTAF_GET_NETWORK_NOTIFICATION) (const charn * const opcn_InterfaceName,
                                                     const charn * const opcn_InterfaceStatus);
typedef void (* PR_LIBTAF_GET_SMS) (const charn * const opcn_PhoneNumber, const charn * const opcn_Message);
typedef void (* PR_LIBTAF_GET_HELLO) (const charn * const opcn_DaemonName);
typedef void (* PR_LIBTAF_GET_GOODBYE) (const charn * const opcn_DaemonName);
typedef void (* PR_LIBTAF_GET_NRTI) (const charn * const opcn_NetworkTimeIndicator);
typedef void (* PR_LIBTAF_WHOISTHERE_NOTIFICATION) (const charn * const opcn_DaemonName);
typedef void (* PR_LIBTAF_USER_MESSAGE_NOTIFICATION) (DBusMessage * const opt_msg);

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 dbus_get_on_the_bus(T_DBUS_Util * const opt_DBusInstance);

extern sint32 dbus_send_hallo_signal(const T_DBUS_Util * const opt_DBusInstance);

extern sint32 dbus_send_goodbye_signal(const T_DBUS_Util * const opt_DBusInstance);

extern sint32 dbus_who_is_there_signal(const T_DBUS_Util * const opt_DBusInstance);

extern sint32 dbus_call_method(const T_DBUS_Util * const opt_DBusInstance,
                               const charn * const opcn_DBusTarget,
                               const charn * const opcn_MethodName,
                               const charn * const opcn_MethodArgument,
                               charn * const opcn_Answer,
                               const sint32 os32_BufferSize);

extern sint32 dbus_call_signal (const T_DBUS_Util * const opt_DBusInstance,
                                 const charn * const opcn_DBusTarget,
                                 const charn * const opcn_SignalName,
                                 const charn * const opcn_SignalArgument);

extern void dbus_initialize_request_callbacks (const PR_LIBTAF_GET_SMS opr_SMSCallback,
                                               const PR_LIBTAF_GET_HELLO opr_HelloCallback,
                                               const PR_LIBTAF_GET_NETWORK_NOTIFICATION opr_NetworkCallback,
                                               const PR_LIBTAF_GET_GOODBYE opr_GoodbyeCallback,
                                               const PR_LIBTAF_GET_NRTI opr_NetworkResponseTimeIndicator,
                                               const PR_LIBTAF_WHOISTHERE_NOTIFICATION opr_WhoIsThereCallback,
                                               const PR_LIBTAF_USER_MESSAGE_NOTIFICATION opr_UserMessageCallback);

extern sint32 dbus_process_requests(const T_DBUS_Util * const opt_DBusInstance);

/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif


