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

/* -- Includes ------------------------------------------------------------ */
#include "j1939_config.h"

/* -- Defines ------------------------------------------------------------- */
// ********** please edit only this parameters
#define J1939_CFG_MAX_LOCAL_NODES   8     // maximum number of local nodes per CAN bus
#define J1939_CFG_MAX_PGS           20    // maximum number of concurrent active PGs (Tx + Rx)
#define J1939_CFG_MAX_SPNS          150   // maximum number of concurrent active SPNs
// **********

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */
//PRQA S 3211 ++ //the variables defined in this module are intended to be used in other modules
             //otherwise we would not be able to use a centralized configuration file
//PRQA S 3406 ++ //this message is a known bug in QA-C 7.1 if global variables are not initialized
T_J1939_cfg_rt_local_node   gat_J1939_CfgRtNodes[J1939_CFG_MAX_LOCAL_NODES][J1939_CAN_CH_MAX];   // array with all local nodes
T_J1939_config_rt_pg_entry  gat_J1939_CfgRtPGEntry[J1939_CFG_MAX_PGS];                           // array with Tx and Rx PGs
T_J1939_config_rt_spn_entry gat_J1939_CfgRtSPNEntry[J1939_CFG_MAX_SPNS];                         // array with SPNs
//PRQA S 3211 --
//PRQA S 3406 --

uint16 gu16_J1939_CfgMaxNrLocalNodes   = J1939_CFG_MAX_LOCAL_NODES;
uint16 gu16_J1939_CfgMaxNrPGs          = J1939_CFG_MAX_PGS;
uint16 gu16_J1939_CfgMaxNrSPNs         = J1939_CFG_MAX_SPNS;

uint16 gu16_J1939_CfgRtNodesEntrysSize = sizeof(gat_J1939_CfgRtNodes);
uint16 gu16_J1939_CfgRtPgEntrySize     = sizeof(gat_J1939_CfgRtPGEntry);
uint16 gu16_J1939_CfgRtSpnEntrySize    = sizeof(gat_J1939_CfgRtSPNEntry);

T_J1939_cfg_rt_local_node   J1939_TRG_HUGE (*gpat_J1939_CfgRtNodes)[J1939_CAN_CH_MAX] = &gat_J1939_CfgRtNodes[0];
T_J1939_config_rt_pg_entry  J1939_TRG_HUGE * gpt_J1939_CfgRtPGEntry  = &gat_J1939_CfgRtPGEntry[0];
T_J1939_config_rt_spn_entry J1939_TRG_HUGE * gpt_J1939_CfgRtSPNEntry = &gat_J1939_CfgRtSPNEntry[0];

/* -- Module Global Variables --------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------- */

/* -- Implementation ------------------------------------------------------ */
