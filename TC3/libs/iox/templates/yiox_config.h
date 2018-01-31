//-----------------------------------------------------------------------------
/*!
   \internal
   \file          yiox_config.h
   \brief         Definitions of YIOX library buffers

   Contains definitions of the YIOX library buffers. The size definitions can be
   changed by the user.
   With this approach the number of YIOX modules that can be used
   (and thus memory consumption of the YIOX) can be configured by the application
   without having to resort to dynamic memory allocation.

   \implementation
   project     YIOX library
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     03.12.2009  STW/A.Stangl
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author                  Description
   17.03.2010        STW/F.Belser            port from ydios
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef H_YDIOS_CONFIG
#define H_YDIOS_CONFIG

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include "yiox.h"   //!< YIOX structure definitions

#ifdef __cplusplus
extern "C" {
#endif

/* -- Defines ------------------------------------------------------------- */
//number of possible YIOX modules; change this if more modules are required.
#define YIOX_NUM_SUPPORTED_MODULES  (6)

#if YIOX_NUM_SUPPORTED_MODULES > 255
   Error
#endif

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */
//buffer for YIOX instances:
extern T_yiox_status gat_yiox_Instances[YIOX_NUM_SUPPORTED_MODULES];
//maximum number of YIOX instances:
extern volatile const uint8 gu8_yiox_NumSupportedInstances;

#ifdef __cplusplus
}
#endif


#endif
