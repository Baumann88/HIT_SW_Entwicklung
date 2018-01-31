//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       Handle DM1 datas

   Process DM1 sending and receiving.

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


#ifndef _J1939_DM1_H_                     // Avoid multiple/recursive inclusion
#define _J1939_DM1_H_


// -- Includes ----------------------------------------------------------------
#include "j1939_tp_bdt.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_DM1_PGN           (uint32)0xFECAU          // PGN for DM1

#define J1939_DM1_TX_TABLE(DTC_LIST, COMM_INST)                                                          \
   static uint8 mau8_LastState_##DTC_LIST[sizeof(DTC_LIST)/sizeof(T_J1939_DM_tx_dtc)];                   \
   static uint8 mau8_TxDm1Buf_##DTC_LIST[2+4*(sizeof(DTC_LIST)/sizeof(T_J1939_DM_tx_dtc))];              \
   static uint8 mau8_TxDm2Buf_##DTC_LIST[2+4*(sizeof(DTC_LIST)/sizeof(T_J1939_DM_tx_dtc))];              \
   static T_J1939_DM_dtc_tx_management mt_Mng_##DTC_LIST = {DTC_LIST,                                    \
                                                            (sizeof(DTC_LIST)/sizeof(T_J1939_DM_tx_dtc)),\
                                                            &COMM_INST,                                  \
                                                            NULL,                                        \
                                                            mau8_LastState_##DTC_LIST,                   \
                                                            0,0,0,                                       \
                                                            mau8_TxDm1Buf_##DTC_LIST,                    \
                                                            mau8_TxDm2Buf_##DTC_LIST,                    \
                                                           };

#define J1939_DM1_GET_TX_TABLE_MNG(DTC_LIST)  &mt_Mng_##DTC_LIST


// -- Types -------------------------------------------------------------------
typedef struct
{
   uint8  u8_MalfIndLamp;              // malfunction indicator lamp status (2 bits)
   uint8  u8_RedStopLamp;              // red stop lamp status (2 bits)
   uint8  u8_AmberWarnLamp;            // amber warning lamp status (2 bits)
   uint8  u8_ProtectLamp;              // protect warning lamp status (2 bits)
}
T_J1939_DM_lamp;                       // lamp state for the DTC table

typedef struct
{
   uint32 u32_Spn;                     // the SPN
   uint8  u8_Fmi;                      // FMI
   uint8  u8_SpnConvMode;              // SPN conversion mode
   uint8  u8_OccurCounter;             // occurrence counter
}
T_J1939_DM_dtc;                        // DM DTC structure

typedef struct
{
   uint16 u16_TotalNrDtc;              // maximal number of DTC in received data stream
   uint16 u16_DtcIndex;                // the index of the reported DTC [1 ... u16_TotalNrDtc]
}
T_J1939_DM_rx_dtc_state;               // state of the received DTC

typedef struct
{
   T_J1939_DM_rx_dtc_state t_DtcState; // state of the reported DTC
   T_J1939_DM_lamp         t_Lamp;     // node lamp values
   T_J1939_DM_dtc          t_Dtc;      // the DTC values
}
T_J1939_DM_rx_dtc;                     // DM Rx DTC structure

typedef struct
{
   uint8          u8_State;            // ON - error active, OFF - error not active
   uint8          u8_PrevActive;       // TRUE if corresponding DM1 was previously active
   T_J1939_DM_dtc t_Dtc;               // DTC values
}
T_J1939_DM_tx_dtc;                     // DM Tx DTC structure

typedef struct
{
   // connect the DTC list with the communication instance
   T_J1939_DM_tx_dtc J1939_TRG_HUGE *pt_DtcList;           // pointer to list with DTC
   uint16 u16_NrDtc;                                       // number of DTCs in list
   T_J1939_TP_BDT_tx_def J1939_TRG_HUGE *pt_Dm1CommInst;   // pointer to TP.BDT Tx communication instance
   T_J1939_TP_BDT_tx_def J1939_TRG_HUGE *pt_Dm2CommInst;   // pointer to TP.BDT Tx communication instance
   // internal states
   uint8 J1939_TRG_HUGE *pu8_LastState;                    // needed for detecting state changes
   uint32 u32_NextSendTime;                                // next send time or 0 if no send is active
   uint8 u8_SendBeforeTime;                                // TRUE if a message is send before 1s as expired
   uint8 u8_ChangeFlag;                                    // TRUE if the state of least one has changed
   uint8 J1939_TRG_HUGE *pu8_Dm1TxBuffer;                  // store the TP.BDT data buffer for DM1
   uint8 J1939_TRG_HUGE *pu8_Dm2TxBuffer;                  // store the TP.BDT data buffer for DM2
}
T_J1939_DM_dtc_tx_management;   // management structure for DTC list send

//-----------------------------------------------------------------------------
/*!
   \brief    Callback function for received DM1 informations

   The registered application function is called for every complete received
   DTC in DM1 data stream.

   \param[in]          ou16_Channel     bus number
   \param[in]          ou8_SrcAddress   the sender node address
   \param[out]         opt_Data         pointer to structure with decoded DTC

   \return
    -

   \created            02.08.2010       STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author           Description
   02.08.2010          STW/M.Greiner    function created
   \endhistory
*/
//-----------------------------------------------------------------------------
typedef void (*PR_J1939_DM1_rx)(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                                const T_J1939_DM_rx_dtc * const opt_Data);


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern void J1939_dm1_rx_init_callback(const PR_J1939_DM1_rx opr_Callback);
extern void J1939_dm1_rx_handle(void * const opv_Inst, const uint8 * const opu8_Data,
                                const uint16 ou16_Count, const uint16 ou16_StreamPosition,
                                const uint16 ou16_RemainingBytes);
extern sint16 J1939_dm1_tx_register_dtc_list(T_J1939_DM_dtc_tx_management* const opt_DtcListMng);
extern void J1939_dm1_tx_set_lamps(const T_J1939_DM_dtc_tx_management * const opt_DtcListMng,
                                   const T_J1939_DM_lamp * const opt_Lamp);
extern void J1939_dm1_tx_get_lamps(const T_J1939_DM_dtc_tx_management * const opt_DtcListMng,
                                   T_J1939_DM_lamp * const opt_Lamp);


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
