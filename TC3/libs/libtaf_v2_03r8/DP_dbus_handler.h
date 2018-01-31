//-----------------------------------------------------------------------------
/*!
   \file          DP_dbus_handler.h
   \brief         Provides utility functions to use the ydatad daemon

   Provides utility functions to use the dbus and ydatad daemon

   \implementation
   copyright   STW (c) 1999-2008
   license     use only under terms of contract / confidential

   created     23.06.10 Sven Dittmer
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   10.08.10          Florian Belser    some small reworks
   23.06.10          Sven Dittmer      file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _DP_DBUS_HANDLER_H
#define _DP_DBUS_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
#include "dbus-utils.h"
/* -- Defines ------------------------------------------------------------- */
/* -- Types --------------------------------------------------------------- */
typedef enum
{
   eUNKNOWN = 0,
   eUINT8,
   eSINT8,
   eUINT16,
   eSINT16,
   eUINT32,
   eSINT32,
   eFLOAT32,
   eAOBYTE,
   eSTRING,
   eNULL
}E_DataType;

typedef struct
{
   charn const * const     pcn_TypeName;
   sint8 const             s8_TypeSize;
   E_DataType const        e_TypeIndex;
} T_DATA_TYPE_TABLE;

/* -- Global Variables ---------------------------------------------------- */
extern T_DATA_TYPE_TABLE gat_data_type_table[11];

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ydatad_create_variable_list(const T_DBUS_Util * const opt_DBusInstance,
                                          const charn * const opcn_Datapool,
                                          const charn * const opcn_List,
                                          const charn * const opcn_Description,
                                          const charn * const opcn_Creator);

extern sint32 ydatad_add_variable_to_list(const T_DBUS_Util * const opt_DBusInstance,
                                          const charn * const opcn_Datapool,
                                          const charn * const opcn_List,
                                          const charn * const opcn_Name,
                                          const charn * const opcn_Type,
                                          const charn * const opcn_Size,
                                          const charn * const opcn_Unit,
                                          const charn * const opcn_Comment);

extern sint32 ydatad_init_variable_list(const T_DBUS_Util * const opt_DBusInstance,
                                        const charn * const opcn_Datapool,
                                        const charn * const opcn_List);

extern sint32 ydatad_delete_variable_list(const T_DBUS_Util * const opt_DBusInstance,
                                          const charn * const opcn_Datapool,
                                          const charn * const opcn_List);

extern sint32 ydatad_get_datapool_base_path(const T_DBUS_Util* const opt_DBusInstance,
                                            charn * const opcn_BasePath,
                                            const sint32 os32_Size);

extern sint32 ydatad_init_datapool(const T_DBUS_Util * const opt_DBusInstance, const charn * const opcn_Datapool);

extern E_DataType ydatad_validate_variable(const charn * const opcn_Type, const charn * const opcn_Size);
/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif


