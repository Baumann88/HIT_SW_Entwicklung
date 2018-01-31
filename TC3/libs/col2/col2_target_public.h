//-----------------------------------------------------------------------------
/*!
   \file       col2_target_public.h
   \brief      Target specific public functions and definitions used by COL2

   Here for target TC3

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     24.06.2009  STW/A.Stangl
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   11.03.2010        STW/F.Belser  addaption to TC3
   24.06.2009        STW/A.Stangl  created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _COL2_TARGET_PUBLIC_H
#define _COL2_TARGET_PUBLIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h" //STW variable type definitions

/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */


typedef struct
{
   uint8 u8_Channel;          //!< can bus channel
} T_col2_bus_parameters;

//!< data for internal use, not to be used by application:
typedef struct
{
   sint16 s16_RxTxSocket;    // handle to the rx/tx socket
} T_col2_target_instance_data;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
