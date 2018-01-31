//-----------------------------------------------------------------------------
/*!
   \internal
   \file          j1939_config.c
   \brief         J1939 library configuration file

   The buffers for use by the J1939 library are defined in this module. It will
   be linked with the application.
   Thus it's possible to change the lib internal buffer sizes without recompiling
   the J1939 library.

   \implementation
   project     J1939 library
   copyright   STW (c) 1999-201x
   license     use only under terms of contract / confidential

   created     16.08.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author          Description
   16.08.2010        STW/M.Greiner   created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _J1939_CONFIG_H_                  // Avoid multiple/recursive inclusion
#define _J1939_CONFIG_H_

// -- Includes ----------------------------------------------------------------
#include "j1939_target.h"
#include "j1939_pgn_cfg.h"

#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif

// -- Defines -----------------------------------------------------------------

// -- Types -------------------------------------------------------------------
typedef struct
{
   uint8  u8_NodeAddr;                                // node address
   uint16 u16_FirstRxPGIdx;                           // index of the first PG
   uint16 u16_NrRxPGs;                                // number of PGs
   uint16 u16_FirstTxPGIdx;                           // index of the first PG
   uint16 u16_NrTxPGs;                                // number of PGs
}
T_J1939_cfg_rt_local_node;

typedef struct
{
   const T_J1939_SPN_description J1939_TRG_HUGE * pt_Description;    // pointer to SPN description structure
}
T_J1939_config_rt_spn_entry;                          // SPN entry in the runtime configuration

typedef struct
{
   uint32                  u32_Pgn;                   // PGN of the PG
   // user configuration array
   uint16                  u16_UserArrayIndx;         // index of the PG in user supplied configuration array
   // PG definition in lib PGs array
   const T_J1939_PGN_parameters J1939_TRG_HUGE * pt_Definition;      // pointer to PG definition
   // data pool variables
   void J1939_TRG_HUGE *   pv_DataPoolStruct;         // pointer to struct variable in data pool
   uint16                  u16_DataBufferSize;        // size od data buffer (most PGs 8 bytes)
   // communication socket
   uint16                  u16_Channel;               // bus number on which is connected the node
   uint8                   u8_NodeAddr;               // Network address of the node ()
   uint8                   u8_PeerNodeAddr;           // Network address of the peer (needed for point to point links)
   // the used SPNs
   uint16                  u16_FirstSpnIndx;          // index of the first registered SPN for this PG
   uint16                  u16_NrSpnEntrys;           // the number of registered SPNs
   // cyclic data transfer
   uint16                  u16_CycleTime;             // if not NULL, store cycle time [ms]
   uint32                  u32_NextTime;              // Next receiving/sending cycle time [ms]
}
T_J1939_config_rt_pg_entry;                           // PG entry in the runtime configuration

// -- Global Variables --------------------------------------------------------
extern T_J1939_cfg_rt_local_node   gat_J1939_CfgRtNodes[][J1939_CAN_CH_MAX];   // array with all local nodes
extern T_J1939_config_rt_pg_entry  gat_J1939_CfgRtPGEntry[];                   // array with Tx and Rx PGs
extern T_J1939_config_rt_spn_entry gat_J1939_CfgRtSPNEntry[];                  // array with SPNs

extern uint16 gu16_J1939_CfgMaxNrLocalNodes;
extern uint16 gu16_J1939_CfgMaxNrPGs;
extern uint16 gu16_J1939_CfgMaxNrSPNs;

extern uint16 gu16_J1939_CfgRtNodesEntrysSize;
extern uint16 gu16_J1939_CfgRtPgEntrySize;
extern uint16 gu16_J1939_CfgRtSpnEntrySize;

extern T_J1939_cfg_rt_local_node   J1939_TRG_HUGE (*gpat_J1939_CfgRtNodes)[J1939_CAN_CH_MAX];
extern T_J1939_config_rt_pg_entry  J1939_TRG_HUGE * gpt_J1939_CfgRtPGEntry;    // array with Tx and Rx PGs
extern T_J1939_config_rt_spn_entry J1939_TRG_HUGE * gpt_J1939_CfgRtSPNEntry;   // array with SPNs

// -- Function Prototypes -----------------------------------------------------

// -- Implementation ----------------------------------------------------------

#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
