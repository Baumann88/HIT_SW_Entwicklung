//-----------------------------------------------------------------------------
/*!
   \file       col2_types.h
   \brief      CANopen functions on Layer 2.

   Type and target driver interface definition of COL2.

   \implementation
   project     COL2
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     05.09.2012  STW/M.Heiss
   \endimplementation
*/
//-----------------------------------------------------------------------------
#ifndef _COL2_TYPES_H
#define _COL2_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"


/* -- Defines ------------------------------------------------------------- */
//CANopen basics
#define COL2_MAX_NUM_OF_SLAVES         (127) //!< maximal 127 slaves are supported (127 is the maximum value in general)
#define COL2_MAX_NUM_OF_RX_PDOS        (64)  //!< maximal 64 pdos can be registered to be received
#define COL2_NUM_CAN_IDS               (0x800)


/* -- Types --------------------------------------------------------------- */
//These structures are defined in the header, so that the required memory can be instances by the application.
//Note: that does not mean that the application can rely on any of the data contained therein !
//      Always use the col2_... functions to interface with the library functionality.
/*! \brief CANopen-Layer2 - CAN object data structure. */
typedef struct
{
   uint8    u8_NewData;    //!< new data received - status flag - used for polling
                            //driver has to set this flag on reception to 1, and has to ignore the flag on transmission
   uint8    u8_DLC;        //!< payload length
   uint16   u16_ID;        //!< the CAN-ID of the received object
   uint8    au8_Data[8];   //!< payload containing the data
   uint32   u32_Time;      //!< RX timestamp [ms], ignored for TX COBs
} T_col2_cob;


typedef struct
{
   uint8 u8_SDOState;         //!< state of the SDO read / write state machine
   uint8 au8_Response[8];     //!< response data
   uint32 u32_SDORequestTime; //!< difference between (2^32 - 1) and the timestamp a SDO request was sent
} T_col2_sdo_state;


typedef struct
{
   uint8 u8_Service; //!< not assigned; PDO; SDO; heartbeat/nodeguarding; EMCY
   uint8 u8_Index;   //!< index in look up table for the selected service (for PDO)
} T_col2_id;


/*! \brief  Node information for the connected slaves. */
typedef struct
{
   //Guarding and Heartbeat
   uint8  u8_GuardMode;          //!< off; guarding; heartbeat (todo: keep this information in a separate high-level table)
   uint8  u8_NMTStatus;          //!< status of guarding / heartbeat
   uint8  u8_NodeStatus;         //!< nodes status transmitted in the rtr response or heardbeat message
   uint8  u8_GuardStatus;        //!< active; pending (guarding only)
   uint8  u8_LifeTimeFactor;     //!< max number of missed responses until a slave is delared as dead (guarding only)
   uint16 u16_GuardTime;         //!< periode (ms) a slave shall be guarded (or: heartbead supervision time)
   uint32 u32_ReXTime;           //!< timestamp of latest NG request resp. latest HB response
   uint32 u32_ReqTime1st;        //!< timestamp of first NG request try (used to determine node guarding timeout)

   //SDOs
   T_col2_sdo_state t_SDOState;     //!< SDO transfer state

   //EMCYs
   T_col2_cob t_EMCY;          //!< last received emergency message for this node
} T_col2_node;


typedef struct
{
   uint32 u32_Magic; //magic pattern used to detect invalid or uninitialized col2 instance pointer
   T_col2_node at_Slaves[COL2_MAX_NUM_OF_SLAVES];  //!< list of slave nodes

   uint8 u8_OwnNodeID;
   uint8 u8_NumOfRegisteredPDOs;
   uint8 u8_NumOfRegisteredGuardings;
   //Table of configured PDOs
   T_col2_cob at_PDOList[COL2_MAX_NUM_OF_RX_PDOS];  //!< configured RX PDOs
   //Table of configured Guardings / Heartbeats
   uint8 au8_Guardings[COL2_MAX_NUM_OF_SLAVES];

   uint32 u32_SDOTimeout;     //!< maximal time waiting for a SDO response
   uint16 u16_HeartBeatProducerTime;
   uint32 u32_NextHeartBeatSendTime;

   //filter table
   T_col2_id at_IDs[COL2_NUM_CAN_IDS]; //!< one entry for each CAN message ID
   //target driver
   void * pv_Driver;
} T_col2_network;



/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

/* -- Implementation ------------------------------------------------------ */


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
