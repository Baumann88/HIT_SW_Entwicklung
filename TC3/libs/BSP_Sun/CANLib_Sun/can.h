//-----------------------------------------------------------------------------
/*!
   \file       can.h
   \brief      can header

   \implementation
   project     tc3 training
   copyright   STW (c) 1999-2012
   license     use only under terms of contract / confidential

   created     21.02.2012  STW/F.Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author           Description
   21.02.2012        Florian Belser   file created
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef _STW_CAN_H_
#define _STW_CAN_H_
/* -- Defines ------------------------------------------------------------- */
//"At time of writing, these constants are not defined in the headers"
#ifndef PF_CAN
  #define PF_CAN 29
#endif

#ifndef AF_CAN
  #define AF_CAN PF_CAN
#endif

/* -- Includes ------------------------------------------------------------ */
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>
#include <net/if.h>
#include <errno.h>
#include "stwtypes.h"
#include "stwerrors.h"


/* -- Types --------------------------------------------------------------- */
typedef struct
{
   uint32 u32_Id; // CAN identifier 11/29bit
   uint8  u8_Xtd; // u8_XTD == TRUE: 29bit ID, u8_XTD == FALSE: 11bit ID
} T_can_id;

typedef struct
{
   T_can_id t_Id;   // CAN message ID
   uint8 u8_Dlc;      // Data Length Code (0..8)
   uint8 au8_Data[8]; // message data bytes
   uint32 u32_time;   // timestamp of reception in milliseconds (system time), not used for TX messages
} T_can_msg;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 gs32_CAN_CloseBus(sint16 * const ops16_Socket);
extern sint32 gs32_CAN_SendMsg(const sint16 * const ops16_Socket, const T_can_msg * const opt_Message);
extern sint32 gs32_CAN_RecvMsg(const sint16 * const ops16_Socket, T_can_msg * const opt_Message);
extern sint32 gs32_CAN_InitBus (sint16 * const ops16_Socket, const uint8 ou8_Bus);
/* -- Implementation ------------------------------------------------------ */

#endif
