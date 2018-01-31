//-----------------------------------------------------------------------------
/*!
   \internal
   \file          yiox_config.c
   \brief         YIOX configuration file

   The buffers for use by the YIOX library are defined in this module. It will
   be linked with the application.
   Thus it's possible to change the number of supported IOX modules without recompiling
   the YIOX library.

   \implementation
   project     YIOX library
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     03.12.2009  STW/A.Stangl
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author                  Description
   16.03.2010        STW/F.Belser            port YDIOS
   \endhistory
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
#include "yiox_config.h"

/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

//PRQA S 3211 ++ //the variables defined in this module are intended to be used in other modules
                 //otherwise we would not be able to use a centralized configuration file
//PRQA S 3406 ++ //this message is a known bug in QA-C 7.1 if global variables are not initialized

//maximum number of YIOX instances:
volatile const uint8 gu8_yiox_NumSupportedInstances = YIOX_NUM_SUPPORTED_MODULES;

//buffer for YIOX instances:
T_yiox_status gat_yiox_Instances[YIOX_NUM_SUPPORTED_MODULES];

//PRQA S 3211 --
//PRQA S 3406 --

/* -- Module Global Variables --------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------- */

/* -- Implementation ------------------------------------------------------ */
