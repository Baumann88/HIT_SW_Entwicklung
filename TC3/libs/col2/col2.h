//-----------------------------------------------------------------------------
/*!
   \file       col2.h
   \brief      CANopen functions on Layer 2.

   \implementation
   project     COL2
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     27.03.2008  STW/M.Heiss
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   xx.11.2009        STW/A.Stangl  reworked:
                                   - added additional parameter for channel
                                   - harmonized function names
                                   - made structure definitions public so required buffers for multiple instances can
                                     be allocated in application space
   02.11.2009        STW/A.Stangl  removed gt_col2_SDOError (use col2_sdo_get_last_error)
                                   added function col2_sdo_get_last_error
   24.06.2009        STW/A.Stangl  changed return values to sint16 to reflect changes in SEPI
                                   changed interface of col2_init as the parameters are potentially
                                    target specific
   27.03.2008        STW/M.Heiss   created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _COL2_H
#define _COL2_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include "col2_target_public.h"


/* -- Defines ------------------------------------------------------------- */
//CANopen basics
#define COL2_MAX_NUM_OF_SLAVES         (127) //!< maximal 127 slaves are supported (127 is the maximum value in general)
#define COL2_MAX_NUM_OF_RX_PDOS        (64)  //!< maximal 64 pdos can be registered to be received


//BASE CAN-IDs (keep in mind: this is seen from the slave - seen from this master implementation the usage is inverted)
#define COL2_NMT_CAN_ID                (0x00u)     //!< CAN ID for network management service
#define COL2_SYNC_CAN_ID               (0x80u)     //!< CAN ID for SYNC messages (DLC == 0)
#define COL2_EMCY_BASE_CAN_ID          (0x80u)     //!< 1st CAN ID for emergency messages (DLC != 0)
#define COL2_TIME_STAMP_CAN_ID         (0x100u)    //!< CAN ID for time stamp message
#define COL2_TPDO1_BASE_CAN_ID         (0x180u)    //!< 1st CAN ID for 1st transmit project data object
#define COL2_RPDO1_BASE_CAN_ID         (0x200u)    //!< 1st CAN ID for 1st receive project data object
#define COL2_TPD02_BASE_CAN_ID         (0x280u)    //!< 1st CAN ID for 2nd transmit project data object
#define COL2_RPDO2_BASE_CAN_ID         (0x300u)    //!< 1st CAN ID for 2nd receive project data object
#define COL2_TPDO3_BASE_CAN_ID         (0x380u)    //!< 1st CAN ID for 3rd transmit project data object
#define COL2_RPDO3_BASE_CAN_ID         (0x400u)    //!< 1st CAN ID for 3rd receive project data object
#define COL2_TPDO4_BASE_CAN_ID         (0x480u)    //!< 1st CAN ID for 4th transmit project data object
#define COL2_RPDO4_BASE_CAN_ID         (0x500u)    //!< 1st CAN ID for 4th receive project data object
#define COL2_TSDO_BASE_CAN_ID          (0x580u)    //!< 1st CAN ID for transmit service data object
#define COL2_RSDO_BASE_CAN_ID          (0x600u)    //!< 1st CAN ID for receive service data object
#define COL2_NMT_BASE_CAN_ID           (0x700u)    //!< 1st CAN ID for error management base

//SDO error codes
#define COL2_SDO_ERR_TOGGLE             (0x05030000UL)
#define COL2_SDO_ERR_SDO_TIMEOUT        (0x05040000UL)
#define COL2_SDO_ERR_SPECIFIER_INVALID  (0x05040001UL)
#define COL2_SDO_ERR_INVALID_BLOCKSIZE  (0x05040002UL)
#define COL2_SDO_ERR_INVALID_SEQUENCE   (0x05040003UL)
#define COL2_SDO_ERR_CRC                (0x05040004UL)
#define COL2_SDO_ERR_OUT_OF_MEMORY      (0x05040005UL)
#define COL2_SDO_ERR_UNSUPP_ACCESS      (0x06010000UL)
#define COL2_SDO_ERR_READING_WO         (0x06010001UL)
#define COL2_SDO_ERR_WRITING_RO         (0x06010002UL)
#define COL2_SDO_ERR_INDEX_INVALID      (0x06020000UL)
#define COL2_SDO_ERR_NO_MAP             (0x06040041UL)
#define COL2_SDO_ERR_PDO_TOO_LONG       (0x06040042UL)
#define COL2_SDO_ERR_GENERAL_INCOMP     (0x06040047UL)
#define COL2_SDO_ERR_HARDWARE           (0x06060000UL)
#define COL2_SDO_ERR_DATASIZE           (0x06070010UL)
#define COL2_SDO_ERR_DATA_TYPE_TOO_HIGH (0x06070012UL)
#define COL2_SDO_ERR_DATA_TYPE_TOO_LOW  (0x06070013UL)
#define COL2_SDO_ERR_SUBINDEX_INVALID   (0x06090011UL)
#define COL2_SDO_ERR_RANGE_EXCEEDED     (0x06090030UL)
#define COL2_SDO_ERR_VALUE_TOO_HIGH     (0x06090031UL)
#define COL2_SDO_ERR_VALUE_TOO_LOW      (0x06090032UL)
#define COL2_SDO_ERR_MAX_MIN_CONFLICT   (0x06090036UL)
#define COL2_SDO_ERR_GENERAL_ERROR      (0x08000000UL)
#define COL2_SDO_ERR_DATA_TRANSFER      (0x08000020UL)
#define COL2_SDO_ERR_LOCAL_CONTROL      (0x08000021UL)
#define COL2_SDO_ERR_DEVICE_STATE       (0x08000022UL)
#define COL2_SDO_ERR_OD_ERROR           (0x08000023UL)

//NMT Commands
#define COL2_NMT_NODE_START            (0x01)      //!< NMT node start protocol (transitions: 3, 6)
#define COL2_NMT_NODE_STOP             (0x02)      //!< NMT node stop protocol (transitions: 5, 8)
#define COL2_NMT_NODE_PREOP            (0x80)      //!< NMT enter preoperational state (transitions: 4, 7)
#define COL2_NMT_NODE_RESET_APPL       (0x81)      //!< NMT reset node (transitions: 9, 10, 11)
#define COL2_NMT_NODE_RESET_COM        (0x82)      //!< NMT reset node communication (transitions: 12, 13, 14)

//Guarding / heartbeat
#define COL2_NMT_STATUS_NOT_ACTIVE     (0)    //!< guarding / heartbeat not configured
#define COL2_NMT_STATUS_NOT_STARTED    (1)    //!< guarding / heartbeat not started yet
#define COL2_NMT_STATUS_ALIVE          (2)    //!< slave is alive
#define COL2_NMT_STATUS_DEAD           (3)    //!< node is dead (heartbeat / guarding timeout or error)

#define COL2_NG_NODE_UNKNOWN           (0x00)      //!< Slaves status is unknown - maybe the slave is dead
                                                   //    or guarding / heartbeat has not started yet
#define COL2_NG_NODE_DISCONNECTING     (0x01)      //!< Slave is disconnecting
#define COL2_NG_NODE_CONNECTING        (0x02)      //!< Slave is connecting
#define COL2_NG_NODE_PREPARING         (0x03)      //!< Slave is preparing
#define COL2_NG_NODE_PREPARED          (0x04)      //!< Slave is in prepared state
#define COL2_NG_NODE_OPERATIONAL       (0x05)      //!< Slave is in operational state
#define COL2_NG_NODE_PRE_OPERATIONAL   (0x7F)      //!< Slave is in pre-operational state

#define COL2_NUM_CAN_IDS   (0x800)

/* -- Types --------------------------------------------------------------- */
//These structures are defined in the header, so that the required memory can be instances by the application.
//Note: that does not mean that the application can rely on any of the data contained therein !
//      Always use the col2_... functions to interface with the library functionality.
typedef struct
{
   uint8 u8_SDOState;         //!< state of the SDO read / write state machine
   uint8 au8_Response[8];     //!< response data
   uint32 u32_SDORequestTime; //!< difference between (2^32 - 1) and the timestamp a SDO request was sent
} T_col2_sdo_state;

/*! \brief CANopen-Layer2 - CAN object data structure. */
typedef struct
{
   uint8    u8_NewData;                      //!< new data received - status flag - used for polling
   uint8    u8_DLC;                          //!< payload length
   uint16   u16_ID;                          //!< the CAN-ID of the received object
   uint8    au8_Data[8];                     //!< payload containing the data
   uint32   u32_Time;                        //!< RX timestamp
} T_col2_cob;

typedef struct
{
   uint8 u8_Service; //!< not assigned; PDO; SDO; heartbeat/nodeguarding; EMCY
   uint8 u8_Index;   //!< index in look up table for the selected service (for PDO)
} T_col2_id;

/*! \brief  Node information for the connected slaves. */
typedef struct
{
   //Guarding and Heartbeat
   uint8   u8_GuardMode;       //!< off; guarding; heartbeat (todo: keep this information in a separate high-level table)
   uint8   u8_MissedResponses; //!< number of un-acknowledged rtr requests (guarding only)
   uint8   u8_NMTStatus;       //!< status of guarding / heartbeat
   uint8   u8_NodeStatus;      //!< nodes status transmitted in the rtr response or heardbeat message
   uint8   u8_GuardStatus;     //!< active; pending (guarding only)
   uint8   u8_LifeTimeFactor;  //!< max number of missed responses until a slave is delared as dead (guarding only)
   uint16  u16_GuardTime;      //!< periode (ms) a slave shall be guarded (or: heartbead supervision time)
   uint32  u32_RequestTime;    //!< timestamp the node must be guarded again
   uint32  u32_ResponseTime;   //!< timestamp a rtr request must be acknowledged (guarding only)

   //SDOs
   T_col2_sdo_state t_SDOState;     //!< SDO transfer state

   //EMCYs
   T_col2_cob t_EMCY;          //!< last received emergency message for this node
} T_col2_node;

typedef struct
{
   T_col2_node at_Slaves[COL2_MAX_NUM_OF_SLAVES];  //!< list of slave nodes

   //Table of configured PDOs
   T_col2_cob at_PDOList[COL2_MAX_NUM_OF_RX_PDOS];  //!< configured RX PDOs
   uint8     u8_NumOfRegisteredPDOs;

   //Table of configured Guardings / Heartbeats
   uint8 au8_Guardings[COL2_MAX_NUM_OF_SLAVES];
   uint8 u8_NumOfRegisteredGuardings;

   uint32 u32_SDOTimeout;     //!< maximal time waiting for a SDO response

   uint8 u8_OwnNodeID;
   uint16 u16_HeartBeatProducerTime;
   uint32 u32_NextHeartBeatSendTime;

   uint8 u8_InstanceIsInitialized;

   uint8 u8_RTRActive;

   //filter table
   T_col2_id at_IDs[COL2_NUM_CAN_IDS]; //!< one entry for each CAN message ID

   T_col2_target_instance_data t_TargetData;

} T_col2_network;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint16 col2_init(const T_col2_bus_parameters * const opt_Config, const uint16 ou16_SDOTimeoutMS,
                        const uint8 ou8_OwnNodeID, void ** const oppv_BusHandle);
extern sint16 col2_close(void * const opv_BusHandle);

extern sint16 col2_task(void * const opv_BusHandle);

//network management functions
extern sint16 col2_guarding_register_slave(void * const opv_BusHandle, const uint8 ou8_NodeID,
                                           const uint16 ou16_GuardTimeMS, const uint8 ou8_LifeTimeFactor);
extern sint16 col2_heartbeat_init(void * const opv_BusHandle, const uint16 ou16_ProducerTimeMS);
extern sint16 col2_heartbeat_register_consumer(void * const opv_BusHandle, const uint8 ou8_NodeID,
                                               const uint16 ou16_ConsumerTimeMS);
extern sint16 col2_nmt_get_slave_status(void * const opv_BusHandle, const uint8 ou8_NodeID,
                                        uint8 * const opu8_NMTStatus, uint8 * const opu8_NodeStatus);
extern sint16 col2_nmt_send(void * const opv_BusHandle, const uint8 ou8_NodeID, const uint8 ou8_NMTCommand);

//emergency information
extern sint16 col2_emcy_read(void * const opv_BusHandle, const uint8 ou8_NodeID, uint8 * const opu8_Data,
                             uint8 * const opu8_DLC);

//PDO functions
extern sint16 col2_pdo_register(void * const opv_BusHandle, const uint16 ou16_COBID, void ** const oppv_PDOHandle);
extern sint16 col2_pdo_write(void * const opv_BusHandle, const uint16 ou16_COBID, const uint8 * const opu8_Data,
                             const uint8 ou8_Dlc);
extern sint16 col2_pdo_read(void * const opv_PDOHandle, uint8 * const opu8_Data, uint8 * const opu8_Dlc);
#ifndef COL2_NO_TIMESTAMPS_AVAILABLE
extern sint16 col2_pdo_read_timestamped(void * const opv_PDOHandle, uint8 * const opu8_Data, uint8 * const opu8_Dlc,
                                        uint32 * const opu32_TimeStamp);
#endif

//SDO functions
extern sint16 col2_sdo_write(void * const opv_BusHandle, const uint8 ou8_NodeID, const uint16 ou16_Index,
                             const uint8 ou8_SubIndex, const uint32 ou32_Data, const uint8 ou8_Count);
extern sint16 col2_sdo_read(void * const opv_BusHandle, const uint8 ou8_NodeID, const uint16 ou16_Index,
                            const uint8 ou8_SubIndex, uint32 * const opu32_Data, uint8 * const opu8_Count);
extern sint16 col2_sdo_get_last_error(void * const opv_BusHandle, const uint8 ou8_NodeID,
                                      uint32 * const opu32_ErrorCode);

//library info
extern uint16 col2_library_get_version(void);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
