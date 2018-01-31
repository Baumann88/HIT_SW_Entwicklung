//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 library

   Define the J1939 library application interface

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     28.04.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   28.04.2010         STW/M.Greiner    file created
   \endhistory
*/
//------------------------------------------------------------------------------


#ifndef _J1939_H_                          // Avoid multiple/recursive inclusion
#define _J1939_H_


// -- Includes ----------------------------------------------------------------
#include "j1939_target.h"
#include "j1939_spn.h"
#include "j1939_pgn.h"
#include "j1939_pgn_cfg.h"
#include "j1939_pg_rt_config.h"
#include "j1939_protocol_core.h"
#include "j1939_stack_core.h"
#include "j1939_tp.h"
#include "j1939_tp_bdt.h"
#include "j1939_tp_cmdt.h"
#include "j1939_dm1.h"
#include "j1939_dm2.h"
#include "j1939_dm3.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------

// *** macros for PG configuration table ***
//  network topology
#define J1939_BUS(CHANNEL)    {J1939_PG_CFG_CHANNEL,CHANNEL,0,NULL,NULL,J1939_UNSCALED_SPN,{0}},
#define J1939_NODE(NODE_ADDR) {J1939_PG_CFG_NODE_ADDR,NODE_ADDR,0,NULL,NULL,J1939_UNSCALED_SPN,{0}},
#define J1939_CFG_TABLE_END   {J1939_PG_CFG_END,0,0,NULL,NULL,J1939_UNSCALED_SPN,{0}}

//  user selected SPNs
#define J1939_SELECT_SPN(PG_TYPE, SPN_VARIABLE_NAME) \
           (offsetof(PG_TYPE,SPN_VARIABLE_NAME)),
#define J1939_SELECT_SPN_END (0)}},

//  Rx PGs
#define J1939_RX_PG_UNSCALED_SPN(PEER_ADDR, TIMEOUT, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_RX_PG,PEER_ADDR,TIMEOUT,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_UNSCALED_SPN,{0}},
#define J1939_RX_PG_SCALED_SPN(PEER_ADDR, TIMEOUT, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_RX_PG,PEER_ADDR,TIMEOUT,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_SCALED_SPN,{0}},
#define J1939_RX_PG_ALL_SPN(PEER_ADDR, TIMEOUT, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_RX_PG,PEER_ADDR,TIMEOUT,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_ALL_SPN,{0}},
#define J1939_RX_PG_SELECTED_SPN(PEER_ADDR, TIMEOUT, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_RX_PG,PEER_ADDR,TIMEOUT,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_SELECTED_SPN,{

//  Tx PGs
#define J1939_TX_PG_UNSCALED_SPN(PEER_ADDR, REPEAT_RATE, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_TX_PG,PEER_ADDR,REPEAT_RATE,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_UNSCALED_SPN,{0}},
#define J1939_TX_PG_SCALED_SPN(PEER_ADDR, REPEAT_RATE, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_TX_PG,PEER_ADDR,REPEAT_RATE,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_SCALED_SPN,{0}},
#define J1939_TX_PG_ALL_SPN(PEER_ADDR, REPEAT_RATE, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_TX_PG,PEER_ADDR,REPEAT_RATE,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_ALL_SPN,{0}},
#define J1939_TX_PG_SELECTED_SPN(PEER_ADDR, REPEAT_RATE, DATA_POOL_INSTANCE, PG_CONFIG) \
           {J1939_PG_CFG_TX_PG,PEER_ADDR,REPEAT_RATE,&DATA_POOL_INSTANCE,&PG_CONFIG,J1939_SELECTED_SPN,{

// *** macros for TP configuration table ***
//  end mark in TP_BDT/CMDT config array
#define J1939_TP_CFG_END       0xFF

//  macros for TP_BDT arrays
#define J1939_TPBDT_RX(CHANNEL, SRC_NODE, PGN, BUFFER_NAME, BUFFER_SIZE, FCT) \
           {CHANNEL,SRC_NODE,PGN,BUFFER_NAME,BUFFER_SIZE,FCT,{J1939_TP_CTRL_READY,0},{0,0},{0}},
#define J1939_TPBDT_RX_TABLE_END  J1939_TPBDT_RX(J1939_TP_CFG_END,0,0,NULL,0,NULL)

#define J1939_TPBDT_TX(CHANNEL, SRC_NODE, PGN, BUFFER_NAME, BUFFER_SIZE, FCT) \
           {CHANNEL,SRC_NODE,PGN,BUFFER_NAME,BUFFER_SIZE,FCT,{J1939_TP_CTRL_READY,0},{0,0,0},{0}},
#define J1939_TPBDT_TX_TABLE_END  J1939_TPBDT_TX(J1939_TP_CFG_END,0,0,NULL,0,NULL)

//  macros for TP_CMDT arrays
#define J1939_TPCMDT_RX(CHANNEL, SRC_NODE, DST_NODE, PGN, BUFFER_NAME, BUFFER_SIZE, FCT) \
           {CHANNEL,SRC_NODE,DST_NODE,PGN,BUFFER_NAME,BUFFER_SIZE,FCT,{J1939_TP_CTRL_READY,0},{0},{0,0,0}},
#define J1939_TPCMDT_RX_TABLE_END  J1939_TPCMDT_RX(J1939_TP_CFG_END,0,0,0,NULL,0,NULL)

#define J1939_TPCMDT_TX(CHANNEL, SRC_NODE, DST_NODE, PGN, BUFFER_NAME, BUFFER_SIZE, FCT) \
           {CHANNEL,SRC_NODE,DST_NODE,PGN,BUFFER_NAME,BUFFER_SIZE,FCT,{J1939_TP_CTRL_READY,0},{0},{0,0,0,0,0,0}},
#define J1939_TPCMDT_TX_TABLE_END  J1939_TPCMDT_TX(J1939_TP_CFG_END,0,0,0,NULL,0,NULL)

// *** macros for DM messages ***
//  macros for DM1
#define J1939_SET_DM1_RX(CHANNEL, SRC_NODE) \
           J1939_TPBDT_RX(CHANNEL, SRC_NODE, J1939_DM1_PGN, NULL, 0, &J1939_dm1_rx_handle)

#define J1939_SET_DM1_TX(CHANNEL, SRC_NODE) \
           J1939_TPBDT_TX(CHANNEL, SRC_NODE, J1939_DM1_PGN, NULL, 0, NULL)

//  macros for DM2
#define J1939_SET_DM2_RX(CHANNEL, SRC_NODE) \
           J1939_TPBDT_RX(CHANNEL, SRC_NODE, J1939_DM2_PGN, NULL, 0, &J1939_dm2_rx_handle)

#define J1939_SET_DM2_TX(CHANNEL, SRC_NODE) \
           J1939_TPBDT_TX(CHANNEL, SRC_NODE, J1939_DM2_PGN, NULL, 0, NULL)


// -- Types -------------------------------------------------------------------


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern uint16 J1939_library_get_version(void);
extern sint16 J1939_init(const T_J1939_bus_parameters * const opt_Config);
extern sint16 J1939_close(const uint16 ou16_Channel);
extern void   J1939_task(void);
extern void   J1939_task_tx(void);
extern sint16 J1939_set_pgs_configuration(const T_J1939_PG_declaration* const opt_Pgs);
extern void   J1939_init_unk_rx_pdu_callback(const PR_J1939_ReceivedPDU opr_Callback);
extern void   J1939_init_pg_request_rx_callback(const PR_J1939_RequestReceived opr_Callback);
extern void   J1939_init_ack_callback(const PR_J1939_ReceivedAck opr_Callback);
extern void   J1939_set_tp_configuration(T_J1939_TP_BDT_rx_def  * const opt_RxBdt,
                                         T_J1939_TP_BDT_tx_def  * const opt_TxBdt,
                                         T_J1939_TP_CMDT_rx_def * const opt_RxCmdt,
                                         T_J1939_TP_CMDT_tx_def * const opt_TxCmdt);


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
