//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 PGN configuration module

   Define the Pararameter Groups elements

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     23.04.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   23.04.2010         STW/M.Greiner    file created
   \endhistory
*/
//-----------------------------------------------------------------------------


#ifndef _J1939_PGN_CFG_H_                 // Avoid multiple/recursive inclusion
#define _J1939_PGN_CFG_H_


// -- Includes ----------------------------------------------------------------
#include "j1939_target.h"
#include "j1939_spn.h"

#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------


// -- Types -------------------------------------------------------------------
typedef struct
{
   uint32                                         u32_Pgn;         // the identification number of the PG
   uint16                                         u16_PgSize;      // size of the PG data buffer (most time 8 bytes)
   uint16                                         u16_StructSize;  // the size of the structure in application data pool
   uint16                                         u16_RxTimeout;   // the PG default timeout for receiving PGs [ms]
   uint16                                         u16_TxTimeout;   // the PG default transmit cycle time [ms]
   const T_J1939_SPN_description J1939_TRG_HUGE * pt_SpnsConfig;   // array with all defined SPNs for this PG
}
T_J1939_PGN_parameters;                            // definition of each individual PG


// -- Global Variables --------------------------------------------------------
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_TSC1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_TC1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_XBR;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_ERC1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_EEC1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_EEC2;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_ET1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_HOURS;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_EFLP1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_LFE;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_AMB;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_CCVS;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_VEP1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_IC1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_TRF1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_TI1;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_WFI;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_RF;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_DD;
extern const T_J1939_PGN_parameters gt_J1939_PGN_CFG_CTL;


// -- Function Prototypes -----------------------------------------------------


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
