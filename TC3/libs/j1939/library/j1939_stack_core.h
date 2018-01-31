//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 stack core module

   Read the received messages and dispatch it on the other modules.

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


#ifndef _J1939_STACK_CORE_H_               // Avoid multiple/recursive inclusion
#define _J1939_STACK_CORE_H_


// -- Includes ----------------------------------------------------------------
#include "j1939_protocol_core.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------


// -- Types -------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*!
   \brief   Callback function is called if a PDU is received and not registered

   The application can use such a function for get PGs which are not
   contained in data pool.

   \param[in]          ou16_Channel         on which bus is received the request
   \param[in]          opt_PduFields        pointer to structure with PDU elements
   \param[in]          ou8_Dlc              size of the PDU data
   \param[in]          opu8_Data            pointer to PDU data buffer

   \return
   -

   \created     27.05.2010  STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author           Description
   27.05.2010          STW/M.Greiner    function created
   \endhistory
*/
//-----------------------------------------------------------------------------
typedef void(*PR_J1939_ReceivedPDU)(const uint16 ou16_Channel, const T_J1939_PDU_fields * const opt_PduFields,
                                    const uint8 ou8_Dlc, const uint8 * const opu8_Data);

//-----------------------------------------------------------------------------
/*!
   \brief   Callback function is called if a request message is received

   The application can use such a function for geting all incoming requests

   \param[in]          ou16_Channel         on which bus is received the request
   \param[in]          ou8_SrcAddress       node address of the request sender
   \param[in]          ou8_DstAddress       receiver node address
   \param[in]          ou32_RequestedPgn    the requested PGN

   \return
   -

   \created     27.05.2010  STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author           Description
   27.05.2010          STW/M.Greiner    function created
   \endhistory
*/
//-----------------------------------------------------------------------------
typedef void (*PR_J1939_RequestReceived)(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                                         const uint8 ou8_DstAddress, const uint32 ou32_RequestedPgn);

//-----------------------------------------------------------------------------
/*!
   \brief   Callback function is called if a ACK / NACK message is received

   The application can use such a function for geting all incoming ACK / NACK

   \param[in]          ou16_Channel     on which bus is received the message
   \param[in]          ou8_SrcAddress   node address of the ACK / NACK source
   \param[in]          ou8_DstAddress   node address of the ACK / NACK destination
   \param[in]          opt_Ack          the decoded ACK / NACK message

   \return
   -

   \created     13.08.2010  STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author           Description
   13.08.2010          STW/M.Greiner    function created
   \endhistory
*/
//-----------------------------------------------------------------------------
typedef void(*PR_J1939_ReceivedAck)(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                                    const uint8 ou8_DstAddress,
                                    const T_J1939_acknowledgment * const opt_Ack);


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
