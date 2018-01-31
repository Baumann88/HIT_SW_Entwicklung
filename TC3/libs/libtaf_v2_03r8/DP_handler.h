//-----------------------------------------------------------------------------
/*!
   \file          DP_handler.h
   \brief         Provides utility functions to use a data pool

   Provides utility functions to use a data pool

   \implementation
   copyright   STW (c) 1999-2008
   license     use only under terms of contract / confidential

   created     30.06.10 Sven Dittmer
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   10.08.10          Florian Belser    some small reworks
   30.06.10          Sven Dittmer      file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _DP_HANDLER_H
#define _DP_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
/* -- Includes ------------------------------------------------------------ */
#include <dirent.h>
#include "dbus-utils.h"
#include "DP_dbus_handler.h"
/* -- Defines ------------------------------------------------------------- */
#define LIST_FILE_NAME ".dpl"

#define MAX_DP_STRING_LENGTH          512
#define MAX_DP_BASEFOLDER_LENGHT      128
#define MAX_DP_NAME_LENGTH             64
#define MAX_DP_METANAME_LENGTH         64
#define MAX_DP_TYPENAME_LENGTH         10
#define MAX_DP_SIZE_LENGTH             10

/* -- Types --------------------------------------------------------------- */
typedef struct
{
   charn      acn_VarName[MAX_DP_NAME_LENGTH]; // Variable name, max size of 32
   charn      acn_Type[MAX_DP_TYPENAME_LENGTH]; // Type of variable: max size of 10
                                              // "UINT8"
                                              // "SINT8"
                                              // "UINT16"
                                              // "SINT16"
                                              // "UINT32"
                                              // "SINT32"
                                              // "FLOAT32"
                                              // "AOBYTE"
                                              // "STRING"
   E_DataType e_TypeIndex;
   sint32     s32_Size; // Size of the variable
   charn      acn_Unit[MAX_DP_METANAME_LENGTH]; // Unit of the variable, max size of 64
   charn      acn_Comment[MAX_DP_METANAME_LENGTH]; // Comment of the variable, max size of 64
   void*      pv_SHM_Address;
   sint32     s32_Address_Offset;
} T_DATA_VARIABLE_INFO;

typedef struct
{
   charn                    acn_ListName[MAX_DP_NAME_LENGTH]; // Name of the list, max size 32
   charn                    acn_Description[MAX_DP_METANAME_LENGTH]; // Description of list, max size of 64
   charn                    acn_CreatingPRGM[MAX_DP_METANAME_LENGTH]; // Creator or program name, max size of 64
   sint32                   s32_NbOfVars; // Number of variables in the list (T_DATA_VARIABLE_INFO)
   sint32                   s32_SHM_ID;
   sint32                   s32_Sem_ID;
   void*                    pv_SHM_Address;
   T_DATA_VARIABLE_INFO*    pt_Vars;
} T_DATA_LIST_INFO;

typedef struct
{
   charn                   acn_DatapoolName[MAX_DP_NAME_LENGTH]; // Data pool name, max size 32
   sint32                  s32_NbOfLists; // Number of data pool lists (T_DATA_LIST_INFO)
   T_DATA_LIST_INFO*       pt_lists;
} T_DATA_DATAPOOL_INFO;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ydatad_get_datapool_info (const sint32 os32_DatapoolIndex, T_DATA_DATAPOOL_INFO ** oppt_Datapool);
extern sint32 ydatad_get_number_of_loaded_datapools (void);
extern sint32 ydatad_load_datapool_names(const charn * const opcn_Path);
extern sint32 ydatad_load_datapool(const sint32 os32_DatapoolIndex, const charn * const opcn_Path);
extern sint32 ydatad_get_datapool_index(const charn * const opcn_DatapoolName);
extern sint32 ydatad_get_list_index(const sint32 os32_DatapoolIndex, const charn * const opcn_VariableListName);
extern sint32 ydatad_get_variable_index(const sint32 os32_DatapoolIndex, const sint32 os32_VariableListIndex,
                                        const charn * const opcn_VariableName);
extern sint32 ydatad_set_variable(const sint32 os32_DatapoolIndex, const sint32 os32_VariableListIndex,
                                  const sint32 os32_VariableIndex, const void * const opv_Buffer,
                                  const uint32 ou32_NumberOfBytesToWrite);
extern sint32 ydatad_get_variable(const sint32 os32_DatapoolIndex, const sint32 os32_VariableListIndex,
                                  const sint32 os32_VariableIndex, void * const opv_Buffer,
                                  const uint32 ou32_SizeOfBuffer);
extern sint32 ydatad_get_variable_info (const sint32 os32_DatapoolIndex, const sint32 os32_VariableListIndex,
                                        const sint32 os32_VariableIndex,
                                        T_DATA_VARIABLE_INFO * const opt_DataVariableInfo);
/* -- Implementation ------------------------------------------------------ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif




