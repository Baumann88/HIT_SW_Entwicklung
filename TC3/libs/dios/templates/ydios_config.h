//-----------------------------------------------------------------------------
/*!
   \internal
   \file          ydios_config.h
   \brief         Definitions of YDIOS library buffers

   Contains definitions of the YDIOS library buffers. The size definitions can be
   changed by the user.
   With this approach the number of YDIOS modules that can be used
   (and thus memory consumption of the YDIOS) can be configured by the application
   without having to resort to dynamic memory allocation.

   \implementation
   project     YDIOS library
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     03.12.2009  STW/A.Stangl
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   03.12.2009        STW/A.Stangl  created
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef H_YDIOS_CONFIG
#define H_YDIOS_CONFIG

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include "ydios.h"   //!< YDIOS structure definitions

#ifdef __cplusplus
extern "C" {
#endif

/* -- Defines ------------------------------------------------------------- */
//number of possible YDIOS modules; change this if more modules are required.
#define YDIOS_NUM_SUPPORTED_MODULES  (10)

#if YDIOS_NUM_SUPPORTED_MODULES > 255
   Error
#endif

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */
//buffer for YDIOS instances:
extern T_ydios_status gat_ydios_Instances[YDIOS_NUM_SUPPORTED_MODULES];
//maximum number of YDIOS instances:
extern volatile const uint8 gu8_ydios_NumSupportedInstances;

#ifdef __cplusplus
}
#endif


#endif
