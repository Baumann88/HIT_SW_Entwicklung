//-----------------------------------------------------------------------------
/*!
   \file          MEET_handler.h
   \brief         Provides utility functions to use the ymeetd daemon

   Provides utility functions to use the meet daemon

   \implementation
   copyright   STW (c) 1999-2010
   license     use only under terms of contract / confidential

   created     14.07.11 Sven Dittmer
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author           Description
   14.07.11          Sven Dittmer     file created (based on GPS_handler -> F.Belser)
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _MEET_HANDLER_H
#define _MEET_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "dbus-utils.h"

/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ymeetd_register(const T_DBUS_Util * const opt_DBusInstance, const charn * const opcn_Name,
                              const charn * const opcn_Port, const charn * const opcn_Software,
                              const charn * const opcn_Version, const charn * const opcn_Protocol);
extern sint32 ymeetd_delete(const T_DBUS_Util * const opt_DBusInstance);

/* -- Implementation ------------------------------------------------------ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* end of _MEET_handler_H */
