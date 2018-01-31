//-----------------------------------------------------------------------------
/*!
   \file          Network_handler.h
   \brief         Provides utility functions to use ynetworkd daemon

   Provides utility functions to use the dbus and ynetworkd daemon

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
#ifndef _NETWORK_HANDLER_H
#define _NETWORK_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
# include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */
#define MIN_NETWORK_CON_INTERFACE 13U // Minimum the size of string "NotConnected"
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ynetworkd_get_connected_interface (const T_DBUS_Util * const opt_DBusInstance,
                                                 charn * const opcn_ConnectedInterface,
                                                 const uint8 ou8_BufferSize);
extern sint32 ynetworkd_start_connection (const T_DBUS_Util * const opt_DBusInstance, const uint32 ou32_ConTime);
extern sint32 ynetworkd_stop_connection (const T_DBUS_Util * const opt_DBusInstance);


/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

