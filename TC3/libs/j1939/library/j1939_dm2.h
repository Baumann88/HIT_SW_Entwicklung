//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       Handle DM2 datas

   Process DM2 sending and receiving.

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


#ifndef _J1939_DM2_H_                     // Avoid multiple/recursive inclusion
#define _J1939_DM2_H_


// -- Includes ----------------------------------------------------------------
#include "j1939_tp_bdt.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_DM2_PGN        (uint32)0xFECBU          // PGN for DM2


// -- Types -------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*!
   \brief    Callback function for received DM2 informations

   The registered application function is called for every complete received
   DTC in DM2 data stream.

   \param[in]          ou16_Channel     bus number
   \param[in]          ou8_SrcAddress   the sender node address
   \param[out]         opt_Data         pointer to structure with decoded DTC

   \return
    -

   \created            10.08.2010       STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author           Description
   10.08.2010          STW/M.Greiner    function created
   \endhistory
*/
//-----------------------------------------------------------------------------
typedef void (*PR_J1939_DM2_rx)(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                                const T_J1939_DM_rx_dtc * const opt_Data);


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern void J1939_dm2_rx_handle(void * const opv_Inst, const uint8 * const opu8_Data,
                                const uint16 ou16_Count, const uint16 ou16_StreamPosition,
                                const uint16 ou16_RemainingBytes);
extern void J1939_dm2_rx_send_request(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                                      const uint8 ou8_DstAddress);
extern void J1939_dm2_rx_init_callback(const PR_J1939_DM2_rx opr_Callback);
extern sint16 J1939_dm2_tx_register(T_J1939_TP_BDT_tx_def * const opt_CommInstance);


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
