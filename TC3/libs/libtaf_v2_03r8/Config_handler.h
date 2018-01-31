//-----------------------------------------------------------------------------
/*!
   \file          Config_handler.h
   \brief         Provides utility functions to use yconfigd daemon

   \implementation
   copyright   STW (c) 1999-2012
   license     use only under terms of contract / confidential

   created     11.01.12 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   11.01.12          Florian Belser    file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _CONFIG_HANDLER_H
#define _CONFIG_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
# include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 yconfigd_read_value (const T_DBUS_Util * const opt_DBusInstance,
                                   const charn * const opcn_Command,
                                   const sint32 os32_ResponseTimeout,
                                   charn * const opcn_Value,
                                   const uint32 ou32_BufferSize,
                                   uint32 * const opu32_Length);

extern sint32 yconfigd_set_value (const T_DBUS_Util * const opt_DBusInstance,
                                  const charn * const opcn_Command,
                                  const charn * const opcn_Value,
                                  const sint32 os32_ResponseTimeout,
                                  charn * const opcn_ReturnValue,
                                  const uint32 ou32_BufferSize);

extern sint32 yconfigd_set_value_without_reply (const T_DBUS_Util * const opt_DBusInstance,
                                                const charn * const opcn_Command,
                                                const charn * const opcn_Value);

extern sint32 yconfigd_reset (const T_DBUS_Util * const opt_DBusInstance);

extern sint32 yconfigd_delete_line (const T_DBUS_Util * const opt_DBusInstance,
                                    const charn * const opcn_FilePseudonym,
                                    const charn * const opcn_DeleteTag,
                                    const sint32 os32_ResponseTimeout,
                                    charn * const opcn_Value,
                                    const uint32 ou32_BufferSize);

extern sint32 yconfigd_delete_line_without_reply (const T_DBUS_Util * const opt_DBusInstance,
                                                  const charn * const opcn_FilePseudonym,
                                                  const charn * const opcn_DeleteTag);

extern sint32 yconfigd_add_line (const T_DBUS_Util * const opt_DBusInstance,
                                 const charn * const opcn_FilePseudonym,
                                 const charn * const opcn_LineToAdd,
                                 const sint32 os32_ResponseTimeout,
                                 charn * const opcn_Value,
                                 const uint32 ou32_BufferSize);

extern sint32 yconfigd_add_line_without_reply (const T_DBUS_Util * const opt_DBusInstance,
                                               const charn * const opcn_FilePseudonym,
                                               const charn * const opcn_LineToAdd);

/* -Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

