//-----------------------------------------------------------------------------
/*!
   \file       j1939_target.h
   \brief      Target specific header

   Target specific header file for TC3.

   \implementation
   copyright   STW (c) 1999-201x
   license     use only under terms of contract / confidential

   created     16.12.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author           Description
   16.12.2010        STW/M.Greiner    file created
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef _J1939_TARGET_H
#define _J1939_TARGET_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
//TODO_MG #include "stdtypes.h"
#include "stwtypes.h"
#include "stwerrors.h"


/* -- Defines ------------------------------------------------------------- */
#define J1939_CAN_CH_MAX  2 // the maximal number of CAN buses suported by target
#define J1939_CAN_CH_0    0 // first  CAN channel
#define J1939_CAN_CH_1    1 // second CAN channel

//memory specifier
#define J1939_TRG_HUGE


/* -- Types --------------------------------------------------------------- */
typedef struct
{
   uint16 u16_Channel;      // the CAN bus channel number
}T_J1939_bus_parameters;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

/* -- Implementation ------------------------------------------------------ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _J1939_TARGET_H */
