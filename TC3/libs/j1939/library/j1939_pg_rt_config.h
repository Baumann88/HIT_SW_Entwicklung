//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 PGN run time configuration management module

   The module manage the PGs and SPNs configuration on runtime. Store all
   used PGs and all used SPNs.

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     29.04.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   29.04.2010         STW/M.Greiner    file created
   \endhistory
*/
//------------------------------------------------------------------------------


#ifndef _J1939_PG_RT_CONFIG_H_             // Avoid multiple/recursive inclusion
#define _J1939_PG_RT_CONFIG_H_


// -- Includes ----------------------------------------------------------------
#include "stwtypes.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_MAX_SPN_NR    15                                // maximal nummer of selectable SPNs per PG

#define J1939_DISABLE_TIME  0                                 // disable time monitoring
#define J1939_DEFAULT_TIME  0xFFFFU                           // use default timeout on PG

// PG configuration table entry types
#define J1939_PG_CFG_END         0                            // end mark
#define J1939_PG_CFG_CHANNEL     1                            // can bus number
#define J1939_PG_CFG_NODE_ADDR   2                            // node address
#define J1939_PG_CFG_TX_PG       3                            // transmiting ParameterGroup
#define J1939_PG_CFG_RX_PG       4                            // receiving ParameterGroup

// SPN selection
#define J1939_UNSCALED_SPN       0                            // select all unscaled SPNs from PG
#define J1939_SCALED_SPN         1                            // select all scaled SPNs from PG
#define J1939_ALL_SPN            2                            // select all SPNs
#define J1939_SELECTED_SPN       3                            // only the explicit specified SPNs

// -- Types -------------------------------------------------------------------
typedef struct
{
   uint8 u8_EntryType;                                        // configuration entry type: Channel, NodeAddr, Rx PG, Tx PG
   // - network relevant configuration
   uint8 u8_NetValue;                                         // the value meaning is dependent from ConfigEntryType
   uint16 u16_Time;                                           // user defined timeout (RX PG) or repeat rate (TX PG)
                                                              //    J1939_DEFAULT_TIME, J1939_DISABLE_TIME
   // - the link to structure instance which store the PG data
   void J1939_TRG_HUGE * pv_Instance;                         // pointer to PG instance
   // - the link to PG configuration
   const T_J1939_PGN_parameters J1939_TRG_HUGE * pt_Config;   // pointer to PG configuration
   // - select the PG SPNs
   uint8 u8_SPNSelection;                                     // which SPNs use (scalled, unscaled, all, user)
   uint16 au16_SPNSelection[J1939_MAX_SPN_NR];                // pointer to PG configuration
}
T_J1939_PG_declaration;                                       // declare a ParameterGroup


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern sint16 J1939_build_rt_configuration(const T_J1939_PG_declaration* const opt_PGsArray);


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
