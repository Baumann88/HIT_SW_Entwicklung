//-----------------------------------------------------------------------------
/*!
   \file          Server_handler.h
   \brief         Provides utility functions to use yserverd daemon

   \implementation
   copyright   STW (c) 1999-2012
   license     use only under terms of contract / confidential

   created     02.01.12 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   02.01.12          Florian Belser    file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _SERVER_HANDLER_H
#define _SERVER_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
# include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 yserverd_request_nextjob (const T_DBUS_Util * const opt_DBusInstance);

/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

