//-----------------------------------------------------------------------------
/*!
   \file          DL_dbus_handler.h
   \brief         Provides utility functions to use the ylogd daemon

   Provides utility functions to use the dbus and ylogd daemon

   \implementation
   copyright   STW (c) 1999-2008
   license     use only under terms of contract / confidential

   created     11.08.10 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   11.08.10          Florian Belser    file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _DL_DBUS_HANDLER_H
#define _DL_DBUS_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
# include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */
#define MAX_DL_BASEFOLDER_LENGTH      128
#define MAX_DL_METANAME_LENGTH         64
#define MAX_DL_NAME_LENGTH             64
#define MAX_DL_LOGIC_LENGTH             4
#define MAX_DL_CONC_LENGTH              5

#define TIME_TRIGGERED                  1
#define TIME_AND_EVENT_TRIGGERED        2
#define TIME_OR_EVENT_TRIGGERED         3
#define EVENT_TRIGGERED                 4
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ylogd_add_log_variable (const T_DBUS_Util * const opt_DBusInstance,
                                      const charn * const opcn_LogJobName,
                                      const charn * const opcn_DatapoolName,
                                      const charn * const opcn_ListName,
                                      const charn * const opcn_VariableName,
                                      const uint32 ou32_Hysteresis);

extern sint32 ylogd_create_log_job(const T_DBUS_Util * const opt_DBusInstance,
                                   const charn * const opcn_LogJobName,
                                   const uint32 ou32_LogFileFormat,
                                   const uint32 ou32_JobSize,
                                   const uint32 ou32_Timestamp,
                                   const charn * const opcn_Comment,
                                   const uint32 ou32_SampleTime);

extern sint32 ylogd_set_log_mechanism (const T_DBUS_Util * const opt_DBusInstance,
                                       const charn * const opcn_LogJobName,
                                        const uint8 ou8_LogMechanism);

extern sint32 ylogd_set_trigger_time (const T_DBUS_Util * const opt_DBusInstance,
                                      const charn * const opcn_LogJobName,
                                      const uint32 ou32_LoggingInterval);

extern sint32 ylogd_set_master_save_condition (const T_DBUS_Util * const opt_DBusInstance,
                                               const charn * const opcn_LogJobName,
                                               const charn * const opcn_DatapoolName,
                                               const charn * const opcn_ListName,
                                               const charn * const opcn_VariableName,
                                               const charn * const opcn_Logic,
                                               const uint32 ou32_Hysteresis,
                                               const uint32 ou32_Threshold,
                                               const charn * const opcn_Concatenation);

extern sint32 ylogd_set_save_condition (const T_DBUS_Util * const opt_DBusInstance,
                                        const charn * const opcn_LogJobName,
                                        const charn * const opcn_DatapoolName,
                                        const charn * const opcn_ListName,
                                        const charn * const opcn_VariableName,
                                        const charn * const opcn_Logic,
                                        const uint32 ou32_Hysteresis,
                                        const uint32 ou32_Threshold,
                                        const charn * const opcn_Concatenation);

extern sint32 ylogd_activate_log_job (const T_DBUS_Util * const opt_DBusInstance,
                                      const charn * const opcn_LogJobName,
                                      const uint32 ou32_OnOff);

// deprecated, please use ylogd_set_save_condition instead
extern sint32 ylogd_set_event_condition (const T_DBUS_Util * const opt_DBusInstance,
                                         const charn * const opcn_LogJobName,
                                         const charn * const opcn_DatapoolName,
                                         const charn * const opcn_ListName,
                                         const charn * const opcn_VariableName,
                                         const charn * const opcn_Logic,
                                         const uint32 ou32_Hysteresis,
                                         const uint32 ou32_Threshold,
                                         const charn * const opcn_Concatenation);

/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

