//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 protocol core module

   Provide the protocol base functionality.

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     19.05.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   19.05.2010         STW/M.Greiner    file created
   \endhistory
*/
//------------------------------------------------------------------------------


#ifndef _J1939_PROTOCOL_CORE_H_            // Avoid multiple/recursive inclusion
#define _J1939_PROTOCOL_CORE_H_


// -- Includes ----------------------------------------------------------------
#include "stwtypes.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_BROADCAST_ADDR    0xFF               // broadcast address

#define J1939_TYPE_PDU1         1                  // PDU format
#define J1939_TYPE_PDU2         2

#define J1939_PRIO_LOW          6                  // 110
#define J1939_PRIO_HIGH         3                  // 011

// ACK types
#define J1939_ACK               1
#define J1939_NACK              2

// -- Types -------------------------------------------------------------------
typedef struct
{
   uint8    u8_ResBit;                             // reserved bit
   uint8    u8_DataPage;                           // data page bit
   uint8    u8_PduFormat;                          // pdu format field
   uint8    u8_PduType;                            // PDU1 if "u8_pdu_format < 240"
   uint8    u8_DstAddr;                            // destination address (only for PDU1)
   uint8    u8_GroupExtn;                          // group extension (only for PDU2)
}
T_J1939_PGN;

typedef struct
{
   uint8         u8_Priority;                      // PDU priority (3 Bit)
   uint32        u32_Pgn;                          // PDU Parameter Group Number (24 Bit)
   uint8         u8_SourceAddr;                    // PDU source address
   T_J1939_PGN   t_Pgn;                            // PGN fields
}
T_J1939_PDU_fields;

typedef struct
{
   uint8 u8_AckType;                               // message type
   uint8 u8_GroupFunctionValue;                    // optional (0xFF if not used)
   uint32 u32_Pgn;                                 // the PGN to which refer the message
}
T_J1939_acknowledgment;                            // acknowledgment message


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern void J1939_send_pdu(const uint16 ou16_Channel, const T_J1939_PDU_fields * const opt_PduFields,
                           const uint8 ou8_Dlc, const uint8 * const opu8_Data);
extern void J1939_send_request(const uint16 ou16_Channel, const uint32 ou32_Pgn,
                               const uint8 ou8_SrcAddress, const uint8 ou8_DstAddress);
extern void J1939_send_acknowledg(const uint16 ou16_Channel, const uint8 ou8_SrcAddress, const uint8 ou8_DstAddress,
                                  const T_J1939_acknowledgment * const opt_Ack);


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
