//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       Handle Transport Protocol Broadcast Data Transfers

   Process all broadcast transport layer protocol messages for receiving and
   sending data links.

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     01.06.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   01.06.2010         STW/M.Greiner    file created
   \endhistory
*/
//------------------------------------------------------------------------------

#ifndef _J1939_TP_BDT_H_                   // Avoid multiple/recursive inclusion
#define _J1939_TP_BDT_H_

// -- Includes ----------------------------------------------------------------
#include "j1939_target.h"
#include "j1939_tp.h"

#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif

// -- Defines -----------------------------------------------------------------

// -- Types -------------------------------------------------------------------
typedef struct
{
   uint32 u32_Timeout;                                  // receiving timeout
   uint8  u8_NextSequence;                              // next received packet sequence number
}
T_J1939_TP_BDT_rx_state_machine;                        // state machine datas

typedef struct
{
   uint32 u32_TimeToSend;                               // time to send the next message
   uint8  u8_NextSequence;                              // next transmited packet sequence number
   uint8  u8_NrPackets;                                 // total number of DT packets in the stream
}
T_J1939_TP_BDT_tx_state_machine;                        // state machine datas

typedef struct
{
   // *************** configuration ***************
   // link identification
   uint16                      u16_Channel;             // the bus number
   uint8                       u8_SrcNodeAddr;          // the node address of the transmitter node (peer)
   uint32                      u32_Pgn;                 // the PGN of the received PG data stream
   // relevant if use buffer for received data
   uint8 J1939_TRG_HUGE      * pu8_DataBuffer;          // pointer to receive buffer (NULL - disable buffer)
   uint16                      u16_MaxSize;             // maximal size of the receiving data (receive buffer size)
   // relevant if use receiving callback function
   PR_J1939_TP_RxCallback      pr_Callback;             // if != NULL then call this function after each receiving data

   // ****************** runtime ******************
   // control structure
   T_J1939_TP_ctrl                 t_Ctrl;              // connection state and connection control infos (API)
   // stack internal data of the processing state machine
   T_J1939_TP_BDT_rx_state_machine t_State;
   // application buffer
   uint8                       au8_AppBuffer[8];        // application can use this buffer for own purposes
}
T_J1939_TP_BDT_rx_def;                                  // management structure of a entry in the BAM Rx definition array

typedef struct
{
   // *************** configuration ***************
   // link identification
   uint16                      u16_Channel;             // the bus number
   uint8                       u8_SrcNodeAddr;          // the node address of the transmitter node (local node)
   uint32                      u32_Pgn;                 // the PGN of the transmitted PG data stream
   // relevant if use buffer for transmit data
   uint8 J1939_TRG_HUGE      * pu8_DataBuffer;          // pointer to sending buffer (NULL - data not in buffer)
   uint16                      u16_MaxSize;             // maximal size of the sending data (send buffer size)
   // relevant if use transmit callback function
   PR_J1939_TP_TxCallback      pr_Callback;             // if != NULL then call this function before each message send

   // ****************** runtime ******************
   // control structure
   T_J1939_TP_ctrl                 t_Ctrl;              // connection state and connection control infos (API)
   // stack internal data of the processing state machine
   T_J1939_TP_BDT_tx_state_machine t_State;
   // application buffer
   uint8                       au8_AppBuffer[8];        // application can use this buffer for own purposes
}
T_J1939_TP_BDT_tx_def;                                  // management structure of a entry in the BAM Tx definition array

// -- Global Variables --------------------------------------------------------

// -- Function Prototypes -----------------------------------------------------

// -- Implementation ----------------------------------------------------------

#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
