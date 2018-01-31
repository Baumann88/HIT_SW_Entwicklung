//-----------------------------------------------------------------------------
/*!
   \file       col2.h
   \brief      CANopen functions on Layer 2.

   \implementation
   project     project name
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     24.06.2009  STW/A.Stangl
   \endimplementation
*/
//-----------------------------------------------------------------------------
#ifndef _COL2_H
#define _COL2_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include "col2_base.h"
#include "col2_sl.h"
#include "col2_eb10.h"
#include "col2_eb10_sl.h"

/* -- Defines ------------------------------------------------------------- */
#if ((__GNUC__ != 3) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 5))
 #error This Library should only be used with TRICORE GCC Compiler version 3.4.5
#endif


/* -- Types --------------------------------------------------------------- */
typedef struct
{
   uint16 u16_Channel;     //!< can bus channel
   uint16 u16_TxFifo;      //!< 1 + n number of outgoing messages to be buffered
   uint16 u16_RxFifo;      //!< 1 + n number of incomming messages to be buffered
} T_col2_config;


/* -- Global Variables ---------------------------------------------------- */


/* -- Function Prototypes ------------------------------------------------- */
extern sint16 col2_init(const T_col2_config * const opt_Config, const uint16 ou16_SDOTimeoutMS,
                        const uint8 ou8_OwnNodeID, void ** const oppv_BusHandle);


/* -- Implementation ------------------------------------------------------ */


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif

