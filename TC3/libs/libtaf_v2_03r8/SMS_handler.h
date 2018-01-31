//-----------------------------------------------------------------------------
/*!
   \file          SMS_handler.h
   \brief         Provides utility functions to use ysmsd daemon

   Provides utility functions to use the dbus and ysmsd daemon

   \implementation
   copyright   STW (c) 1999-2011
   license     use only under terms of contract / confidential

   created     25.07.11 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   25.07.11          Florian Belser    file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _SMS_HANDLER_H
#define _SMS_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
# include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */
#define MAX_SMS_LENGTH        160U
#define MAX_SMS_NUMBER_LENGTH  20U
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ysmsd_send_sms (const T_DBUS_Util * const opt_DBusInstance,
                              const charn * const opcn_PhoneNumber,
                              const charn * const opcn_Message);

extern sint32 ysmsd_send_sms_urgent (const T_DBUS_Util * const opt_DBusInstance,
                                     const charn * const opcn_PhoneNumber,
                                     const charn * const opcn_Message);

extern sint32 ysmsd_request_sms_fetch_urgent (const T_DBUS_Util * const opt_DBusInstance);


/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

