//-----------------------------------------------------------------------------
/*!
   \internal
   \file          col2_config.c
   \brief         COL2 configuration file

   The buffers for use by the COL2 library are defined in this module. It will
   be linked with the application.
   Thus it's possible to change the number of supported CAN interfaces without recompiling
   the COL2 library.

   \implementation
   project     kefex application
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     06.11.2009  STW/A.Stangl
   \endimplementation
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
#include "col2_base.h"

/* -- Defines ------------------------------------------------------------- */
//number of possible COL2 instances; change this if COL2 must be instanced more ofter by the application.
#define COL2_NUM_SUPPORTED_CAN_BUSSES  4

#if COL2_NUM_SUPPORTED_CAN_BUSSES > 255
   Error
#endif

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

//PRQA S 3211 ++ //the variables defined in this module are intended to be used in other modules
                 //otherwise we would not be able to use a centralized configuration file
//PRQA S 3406 ++ //this message is a known bug in QA-C 7.1 if global variables are not initialized

//maximum number of COL2 instances:
volatile const uint8 gu8_col2_NumSupportedBusses = COL2_NUM_SUPPORTED_CAN_BUSSES;

//buffer for col2 instances:
T_col2_network gat_col2_Networks[COL2_NUM_SUPPORTED_CAN_BUSSES];

//PRQA S 3211 --
//PRQA S 3406 --

/* -- Module Global Variables --------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------- */

/* -- Implementation ------------------------------------------------------ */
