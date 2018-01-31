//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       Handle DM3 datas

   Process DM3 sending and receiving.

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     14.07.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   14.07.2010         STW/M.Greiner    file created
   \endhistory
*/
//-----------------------------------------------------------------------------


#ifndef _J1939_DM3_H_                     // Avoid multiple/recursive inclusion
#define _J1939_DM3_H_


// -- Includes ----------------------------------------------------------------


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_DM3_PGN        (uint32)0xFECCU          // PGN for DM3


// -- Types -------------------------------------------------------------------


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern void J1939_dm3_tx_send_clear(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                                    const uint8 ou8_DstAddress);


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
