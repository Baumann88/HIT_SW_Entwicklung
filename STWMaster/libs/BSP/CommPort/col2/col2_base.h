//-----------------------------------------------------------------------------
/*!
   \file       col2_base.h
   \brief      CANopen functions on Layer 2.

   \implementation
   project     COL2
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     27.03.2008  STW/M.Heiss
   \endimplementation
*/
//-----------------------------------------------------------------------------
#ifndef _COL2_BASE_H
#define _COL2_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include "col2_types.h"


/* -- Defines ------------------------------------------------------------- */
//BASE CAN-IDs (keep in mind: this is seen from the slave - seen from this master implementation the usage is inverted)
#define COL2_NMT_CAN_ID                   (0x00u)     //!< CAN ID for network management service
#define COL2_SYNC_CAN_ID                  (0x80u)     //!< CAN ID for SYNC messages (DLC == 0)
#define COL2_EMCY_BASE_CAN_ID             (0x80u)     //!< 1st CAN ID for emergency messages (DLC != 0)
#define COL2_TIME_STAMP_CAN_ID            (0x100u)    //!< CAN ID for time stamp message
#define COL2_TPDO1_BASE_CAN_ID            (0x180u)    //!< 1st CAN ID for 1st transmit project data object
#define COL2_RPDO1_BASE_CAN_ID            (0x200u)    //!< 1st CAN ID for 1st receive project data object
#define COL2_TPD02_BASE_CAN_ID            (0x280u)    //!< 1st CAN ID for 2nd transmit project data object
#define COL2_RPDO2_BASE_CAN_ID            (0x300u)    //!< 1st CAN ID for 2nd receive project data object
#define COL2_TPDO3_BASE_CAN_ID            (0x380u)    //!< 1st CAN ID for 3rd transmit project data object
#define COL2_RPDO3_BASE_CAN_ID            (0x400u)    //!< 1st CAN ID for 3rd receive project data object
#define COL2_TPDO4_BASE_CAN_ID            (0x480u)    //!< 1st CAN ID for 4th transmit project data object
#define COL2_RPDO4_BASE_CAN_ID            (0x500u)    //!< 1st CAN ID for 4th receive project data object
#define COL2_TSDO_BASE_CAN_ID             (0x580u)    //!< 1st CAN ID for transmit service data object
#define COL2_RSDO_BASE_CAN_ID             (0x600u)    //!< 1st CAN ID for receive service data object
#define COL2_NMT_BASE_CAN_ID              (0x700u)    //!< 1st CAN ID for error management base

//SDO error codes
#define COL2_SDO_ERR_TOGGLE               (0x05030000UL)
#define COL2_SDO_ERR_SDO_TIMEOUT          (0x05040000UL)
#define COL2_SDO_ERR_SPECIFIER_INVALID    (0x05040001UL)
#define COL2_SDO_ERR_INVALID_BLOCKSIZE    (0x05040002UL)
#define COL2_SDO_ERR_INVALID_SEQUENCE     (0x05040003UL)
#define COL2_SDO_ERR_CRC                  (0x05040004UL)
#define COL2_SDO_ERR_OUT_OF_MEMORY        (0x05040005UL)
#define COL2_SDO_ERR_UNSUPP_ACCESS        (0x06010000UL)
#define COL2_SDO_ERR_READING_WO           (0x06010001UL)
#define COL2_SDO_ERR_WRITING_RO           (0x06010002UL)
#define COL2_SDO_ERR_INDEX_INVALID        (0x06020000UL)
#define COL2_SDO_ERR_NO_MAP               (0x06040041UL)
#define COL2_SDO_ERR_PDO_TOO_LONG         (0x06040042UL)
#define COL2_SDO_ERR_GENERAL_INCOMP       (0x06040047UL)
#define COL2_SDO_ERR_HARDWARE             (0x06060000UL)
#define COL2_SDO_ERR_DATASIZE             (0x06070010UL)
#define COL2_SDO_ERR_DATA_TYPE_TOO_HIGH   (0x06070012UL)
#define COL2_SDO_ERR_DATA_TYPE_TOO_LOW    (0x06070013UL)
#define COL2_SDO_ERR_SUBINDEX_INVALID     (0x06090011UL)
#define COL2_SDO_ERR_RANGE_EXCEEDED       (0x06090030UL)
#define COL2_SDO_ERR_VALUE_TOO_HIGH       (0x06090031UL)
#define COL2_SDO_ERR_VALUE_TOO_LOW        (0x06090032UL)
#define COL2_SDO_ERR_MAX_MIN_CONFLICT     (0x06090036UL)
#define COL2_SDO_ERR_GENERAL_ERROR        (0x08000000UL)
#define COL2_SDO_ERR_DATA_TRANSFER        (0x08000020UL)
#define COL2_SDO_ERR_LOCAL_CONTROL        (0x08000021UL)
#define COL2_SDO_ERR_DEVICE_STATE         (0x08000022UL)
#define COL2_SDO_ERR_OD_ERROR             (0x08000023UL)

//NMT Commands
#define COL2_NMT_NODE_START               (0x01)      //!< NMT node start protocol (transitions: 3, 6)
#define COL2_NMT_NODE_STOP                (0x02)      //!< NMT node stop protocol (transitions: 5, 8)
#define COL2_NMT_NODE_PREOP               (0x80)      //!< NMT enter preoperational state (transitions: 4, 7)
#define COL2_NMT_NODE_RESET_APPL          (0x81)      //!< NMT reset node (transitions: 9, 10, 11)
#define COL2_NMT_NODE_RESET_COM           (0x82)      //!< NMT reset node communication (transitions: 12, 13, 14)

//Guarding / heartbeat
#define COL2_NMT_STATUS_NOT_ACTIVE        (0)    //!< guarding / heartbeat not configured
#define COL2_NMT_STATUS_NOT_STARTED       (1)    //!< guarding / heartbeat not started yet
#define COL2_NMT_STATUS_ALIVE             (2)    //!< slave is alive
#define COL2_NMT_STATUS_DEAD              (3)    //!< node is dead (heartbeat / guarding timeout or error)

#define COL2_NG_NODE_UNKNOWN              (0x00)      //!< Slaves status is unknown - maybe the slave is dead
                                                   //    or guarding / heartbeat has not started yet
#define COL2_NG_NODE_DISCONNECTING        (0x01)      //!< Slave is disconnecting
#define COL2_NG_NODE_CONNECTING           (0x02)      //!< Slave is connecting
#define COL2_NG_NODE_PREPARING            (0x03)      //!< Slave is preparing
#define COL2_NG_NODE_PREPARED             (0x04)      //!< Slave is in prepared state
#define COL2_NG_NODE_OPERATIONAL          (0x05)      //!< Slave is in operational state
#define COL2_NG_NODE_PRE_OPERATIONAL      (0x7F)      //!< Slave is in pre-operational state


/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */
//Configuration Variables: Shall be defined by application in col2_config.c
extern volatile const uint8 gu8_col2_NumSupportedBusses; //maximum number of COL2 instances
extern T_col2_network gat_col2_Networks[];   //buffer for col2 instances:


/* -- Function Prototypes ------------------------------------------------- */
//extern sint16 col2_init(...) //use target specific initialization to create a new col2 instance and bind it to target driver
extern sint16 col2_close(void * const opv_BusHandle); //close col2 instance and release target driver
extern sint16 col2_task(void * const opv_BusHandle); //execute col2 for message processing - must be called cyclically

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

//utility function, not released for public use!
extern uint32 col2_uti_get_time_ms(void * const opv_BusHandle);


/* -- Implementation ------------------------------------------------------ */


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
