//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       Provide data types for transport protocol layer

   Provide common data types of the modules for BroadcastDataTransfer and
   ConnectionModeDataTransfer.

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
#ifndef _J1939_TP_H_                       // Avoid multiple/recursive inclusion
#define _J1939_TP_H_

// -- Includes ----------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif

// -- Defines -----------------------------------------------------------------
// TP link states
#define J1939_TP_CTRL_START_TRANSFER   0      //  trigger the send begin     ready to receive incoming link
#define J1939_TP_CTRL_IN_PROGRESS      1      //  send is active             receiving is active
#define J1939_TP_CTRL_FINISHED         2      //  transmission is finished   data complete received
#define J1939_TP_CTRL_ERROR            3      //  --                         error on receiving (timeout, sequence)
#define J1939_TP_CTRL_READY            4      //  ready to use               --

// -- Types -------------------------------------------------------------------
typedef struct
{
   uint8 u8_LinkState; // the actual state of the connection
   uint16 u16_NrBytes; // the number of received/transmitted bytes (<=MaxBytes)
}
T_J1939_TP_ctrl;

//-----------------------------------------------------------------------------
/*!
   \brief   Callback function is called if a TP message is received

   The application can use such a function for direct geting the incoming
   data stream of a TP connection.

   \param[in]          opv_Inst             pointer to the connection instance (identificate the connection)
   \param[in]          opu8_Data            pointer to buffer with received data
   \param[in]          ou16_Count           the number of received data (0..7)
   \param[in]          ou16_StreamPosition  position of received data in stream (0 - first byte)
   \param[in]          ou16_RemainingBytes  number of following bytes (0 - all data received)

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
typedef void (*PR_J1939_TP_RxCallback)(void * const opv_Inst, const uint8 * const opu8_Data,
                                       const uint16 ou16_Count, const uint16 ou16_StreamPosition,
                                       const uint16 ou16_RemainingBytes);

//-----------------------------------------------------------------------------
/*!
   \brief   Callback function is called before a TP message is send

   The application can use such a function for direct generating the stream of a TP connection.

   \param[in]          opv_Inst             pointer to the connection instance (identificate the connection)
   \param[out]         opu8_Data            pointer to send buffer
   \param[in]          ou16_Count           the number of sending data (0..7)
   \param[in]          ou16_StreamPosition  position of data in stream (0 - first byte)

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
typedef void (*PR_J1939_TP_TxCallback)(void * const opv_Inst, uint8 * const opu8_Data,
                                       const uint16 ou16_Count, const uint16 ou16_StreamPosition);

// -- Global Variables --------------------------------------------------------

// -- Function Prototypes -----------------------------------------------------

// -- Implementation ----------------------------------------------------------

#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
