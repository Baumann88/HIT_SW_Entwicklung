//-----------------------------------------------------------------------------
/*!
   \file          DL_LogFile_handler.h
   \brief         Provides utility functions to use the ylogd daemon

   Provides utility functions to use the dbus and ylogd daemon

   \implementation
   copyright   STW (c) 1999-2008
   license     use only under terms of contract / confidential

   created     06.10.11 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   06.10.11          Florian Belser    file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _DL_LOGFILE_HANDLER_H
#define _DL_LOGFILE_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
#include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ylogd_request_data_logger_file (const T_DBUS_Util * const opt_DBusInstance,
                                              const charn * const opcn_DataLoggerName,
                                              charn * const opcn_DataLoggerPath,
                                              const uint16 ou16_BufferSize);

extern sint32 ylogd_delete_log_file(const T_DBUS_Util * const opt_DBusInstance,
                                    const charn * const opcn_DataLoggerName,
                                    const uint8 ou8_DeleteAll);
/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

