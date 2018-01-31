//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_can_types.h
   \brief      generic x_can types used in all software layers

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     28.06.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------
/*!
   \addtogroup     x_can
   \{
*/
//-----------------------------------------------------------------------------

#ifndef _X_CAN_TYPES_H
#define _X_CAN_TYPES_H


/* -- Includes ------------------------------------------------------------ */

#include "stwtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X_CAN_BUS_FAILURE_NONE      0x0000u        // can bus is active (no error)
#define X_CAN_BUS_FAILURE_ACTIVE    0x0000u        // can bus is active (no error)
#define X_CAN_BUS_FAILURE_BUSWARN   0x0001u        // buswarn error flag
#define X_CAN_BUS_FAILURE_BUSOFF    0x0002u        // busoff error flag
#define X_CAN_BUS_LOCKED            0x0100u        // can bus is locked

#define X_CAN_OBJ_TYPE_RX           0              // RX message object type
#define X_CAN_OBJ_TYPE_TX           1              // TX message object type
#define X_CAN_OBJ_TYPE_TX_RTR       2              // TX RTR message object type
#define X_CAN_OBJ_TYPE_GATEWAY      3              // gateway object type

#define X_CAN_OBJ_NO_INIT           0              // message object not initialized
#define X_CAN_OBJ_IN_USE            1              // message object active
#define X_CAN_OBJ_LOCKED            2              // message object locked

#define X_CAN_DIRECTION_RX          0              // callback function: direction flag
#define X_CAN_DIRECTION_TX          1              // callback function: direction flag

#define X_CAN_GATEWAY_RTR_NO        0              // no action on RTR frames
#define X_CAN_GATEWAY_RTR_DEST      1              // RTR response on destination bus
#define X_CAN_GATEWAY_RTR_PASS      2              // pass RTR frames to source bus


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_can_types.hpp"
}
#else



/* -- Types --------------------------------------------------------------- */


/*! \brief  CAN ID. */
typedef struct
{
   uint32       u32_Id;        //!< CAN identifier 11/29bit
   uint8        u8_Xtd;        //!< bXtd == true: 29bit ID, bXtd == false: 11bit ID
} T_x_can_id;


/*! \brief  CAN message. */
typedef struct
{
   T_x_can_id   t_Id;           //!< CAN message ID
   uint8        u8_Dlc;         //!< Data Length Code (0..8)
   uint32       u32_Time;       //!< RX time stamp (not used for TX messages)
   uint8        au8_Data[8];    //!< message data 8x uint8 (aligned to 32bit boundary)
                                //!< (set au8_Data behind u32_Time to force 32bit alignment!!)
} T_x_can_msg;


//-----------------------------------------------------------------------------
/*!
   \brief   Signature of the callback function to handle CAN-bus errors.

   CAN bus failure callback is intended to implement an application specific failure reaction.
   The callback is executed whenever the bus enters the bus warn or bus off state. \n
   It is executed with (ou16_BusState & X_CAN_BUS_FAILURE_BUSWARN) != 0
   if one of the error counters REC or TEC reaches the warn level (default warn level is 96). \n
   It is executed with (ou16_BusState & X_CAN_BUS_FAILURE_BUSOFF) != 0
   if CAN controller is in the bus-off state.

   \attention
   The callback is not executed when the bus is recovered into active state!

   \note
   The status of the can bus is bit coded. So there are other status
   flags available in parameter \b ou16_BusState (e.g. X_CAN_BUS_LOCKED).


   \param        ou32_CallbackParameter         A user defined callback parameter
                                                (can be used to take the instance pointer of a C++ object)
   \param        ou16_Channel                   CAN bus channel number
   \param        ou16_BusState                  Bus state involved into the error - see: T_x_can_bus_status.
                                                - X_CAN_BUS_FAILURE_BUSWARN
                                                - X_CAN_BUS_FAILURE_BUSOFF

   \return
   void
*/
//-----------------------------------------------------------------------------
typedef void (*PR_x_can_bus_FailureCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Channel,
                                             const uint16 ou16_BusState);

//-----------------------------------------------------------------------------
/*!
   \brief   Signature of the callback function called when a TX, RX or RTR event occurred the CAN object.

   \par TX object
   A TX message object may generate a TX interrupt callback after successful message transmission.
   The value of parameter \b ou16_Direction is X_CAN_DIRECTION_TX.

   \par TX_RTR object
   A message object of type TX_RTR may generate also a TX interrupt callback after successful transmission
   of the prepared RTR response message (RTR frame). In this case the value of parameter ou16_Direction is
   also X_CAN_DIRECTION_TX. \n
   In the same way a TX_RTR message object may generate a RX interrupt callback after successful reception
   of a RTR request. In this case the value of parameter ou16_Direction is X_CAN_DIRECTION_RX.

   \note
   The CAN message (*opt_CanMsg) passed to The RX callback of a TX_RTR message object contains the ID, DLC and
   payload data of the prepared RTR frame if the auto response feature is enabled. \n
   If the auto response feature is disabled the CAN message contains the ID and DLC of the RTR request message
   but not the payload data of the RTR frame.

   \par RX object
   A RX message object may generate a RX interrupt callback after successful message reception.
   In this case the value of parameter ou16_Direction is X_CAN_DIRECTION_RX. \n
   A RX message object can also be used to transmit a RTR request. In this case the RX message object may generate
   a TX interrupt callback after successful transmission of the request (the value of parameter \b ou16_Direction
   is X_CAN_DIRECTION_TX).

   \par Gateway object
   For a gateway object the callback function is invoked with ou16_Direction = X_CAN_DIRECTION_TX, if a message is
   passed from source to destination bus and successfully transmitted on the destination bus
   (q_AutoTX should be set TRUE). \n
   Furthermore the callback function is invoked with ou16_Direction = X_CAN_DIRECTION_RX when a RTR frame is relayed
   from the destination bus to the source bus (only for un_RTRMode = X_CAN_GATEWAY_RTR_PASS).

   \note
   In gateway mode the channel number passed to the callback function is always the gateway source channel independent
   of the direction of a message.

   \par Return Value
   The return value of the callback function can be used to control the handling of received messages: \n
   - If the message has already been processed by the callback and is not longer needed it can be dropped. \n
      For that purpose a zero has to be returned. This means that the message data should not be
      stored in the RX buffer.
   - If the message is not completely processed in the callback and should be stored in the object buffer for later
      processing a value of "not zero" has to be returned. This means that the message data is stored in the RX buffer.

   The return value has no effect on: \n
   - callbacks generated by TX interrupts at all message objects
   - on RX interrupts invoked by message object of type TX_RTR
   - on all interrupts generated by a gateway object

   \param[in]        ou32_CallbackParameter          a user defined callback parameter
                                                     (can be used to take the instance pointer of a C++ object)
   \param[in]        ou16_Channel                    CAN bus channel number
   \param[in]        opv_Handle                      CAN object handle
   \param[in]        opt_CanMsg                      CAN message
   \param[in]        ou16_Direction                  direction of the CAN message
                                                     - X_CAN_DIRECTION_RX
                                                     - X_CAN_DIRECTION_TX

   \retval  0        message data will not be stored in the RX buffer
   \retval  !0       message data will be stored in the RX buffer
*/
//-----------------------------------------------------------------------------
typedef sint16 (*PR_x_can_obj_InterruptCallback)(const uint32 ou32_CallbackParameter, const uint16 ou16_Channel,
                                                 const void * const opv_Handle, T_x_can_msg * const opt_CanMsg,
                                                 const uint16 ou16_Direction);

//-----------------------------------------------------------------------------

/*! \var T_x_can_bus_status::u16_BusState

   This variable contains bit coded status information of the CAN bus. Each bit is represented by a define: \n
   - Bit0: X_CAN_BUS_FAILURE_BUSWARN   indication for a buswarn error
   - Bit1: X_CAN_BUS_FAILURE_BUSOFF    indication for busoff error
   - Bit8: X_CAN_BUS_LOCKED            indication weather the can bus is locked or not
*/
typedef struct
{
   uint32            u32_Bitrate;         //!< configured bitrate (bits/s)
   volatile uint32   u32_LastErrorTime;   //!< system time when last error occurred
   volatile uint16   u16_BusState;        //!< bus status (bit coded)
}T_x_can_bus_status;



/*! \var T_x_can_obj_config::u16_Pause

   Specifies a minimum pause time between the transmission of CAN messages. The time is specified as a multiple
   of 0.5ms. If u16_Pause = 0 the delay feature is off.

   \note
   This setting is only applicable for TX message objects.

   \attention
   The message object need a software FIFO buffer when using the pause functionality.
*/
/*! \var T_x_can_obj_config::u16_SoftBuffer

   Specifies the size of the additional software FIFO buffer used to store messages for transmission or the already
   received messages. \n
   The buffer is allocated dynamically from heap memory. It does not require any additional can hardware objects.

   \note
   The maximal size of u16_SoftBuffer is limited by available heap memory.

   \attention
   For message objects of type TX_RTR u16_SoftBuffer has to be set to 0, as no software buffer is allowed for
   those objects type!
*/
/*! \var T_x_can_obj_config::u16_HardBuffer

   Specifies the size of the additional hardware FIFO buffer used to store messages for transmission or the already
   received messages. \n
   The buffer is allocated dynamically from heap memory. For message objects of type RX additional message object
   are allocated from CAN hardware for each buffer element.

   Additional hardware buffer (for RX objects) allows a "relaxed software intervention". So if your application run
   the risk of loosing CAN messages as the CPU is not fast enough to copy them into the software buffer before a
   new message is received, the size of hardware buffer should be increased. \n
   However each hardware buffer element reduce the number of available CAN message objects!

   \note
   For message objects of type TX makes no sense. The resulting buffer is pure software only!

   \note
   The maximal size of u16_HardwareBuffer is limited by the number of available CAN message objects and the
   available heap memory.

   \attention
   For message objects of type TX_RTR u16_HardBuffer has to be set to 0, as no hardware buffer is allowed for
   those objects type!
*/
typedef struct
{
   T_x_can_id                t_Id;                    //!< the ID the object shall use
   uint8                     u8_MsgType;              //!< X_CAN_OBJ_TYPE_RX, X_CAN_OBJ_TYPE_TX, X_CAN_OBJ_TYPE_TX_RTR
   uint16                    u16_Pause;               //!< TX pause in steps of 0.5ms
   uint16                    u16_SoftBuffer;          //!< CAN software FIFO size
   uint16                    u16_HardBuffer;          //!< CAN hardware FIFO size
   uint32                    u32_CallbackParameter;   //!< callback parameter
   PR_x_can_obj_InterruptCallback    pr_Callback;     //!< TX/RX interrupt callback
}T_x_can_obj_config;




/*! \brief  Status information about the can object. */
typedef struct
{
   T_x_can_obj_config t_Config;                //!< objects configuration
   volatile uint32    u32_LastInterruptTime;   //!< last RX/TX event
   uint16             u16_NumberMsgs;          //!< number of messages in FIFO buffer
   uint8              u8_Usage;                //!< X_CAN_OBJ_LOCKED, X_CAN_OBJ_IN_USE, X_CAN_OBJ_NO_INIT
   volatile uint8     u8_MsgLostFlag;          //!< at least one RX message was lost by hardware
   volatile uint8     u8_OverflowCount;        //!< number of lost messages, will be reset by reading it out
}T_x_can_obj_status;


/*! \struct T_x_can_gateway_control

   If a CAN message is received on the source CAN bus object (valid message IDs filtered by t_GatewayMask
   and t_GatewayId) then the control flags t_GatewayControl determine what message fields are copied to the
   destination object.
*/
/*! \var T_x_can_gateway_control::q_CopyDlc

   If q_CopyDlc = TRUE then the DLC of the received message will be included into the set of information copied
   from source bus to destination. \n
   If q_CopyDlc = FALSE then the DLC of the received message will not be copied form source to destination. It will
   be replaced by the DLC of the default message (specified at gateway configuration).
*/
/*! \var T_x_can_gateway_control::q_CopyId

   If q_CopyId = TRUE then the CAN ID of the received message will be included into the set of information copied
   from source bus to destination. \n
   If q_CopyId = FALSE then the CAN ID of the received message will not be copied form source to destination. It will
   be replaced by the CAN ID of the default message (specified at gateway configuration).
*/
/*! \var T_x_can_gateway_control::q_CopyData

   If q_CopyData = TRUE then the CAN data of the received message will be included into the set of information copied
   from source bus to destination. \n
   If q_CopyData = FALSE then the CAN data of the received message will not be copied form source to destination.
   It will be replaced by the CAN data of the default message (specified at gateway configuration).
*/
/*! \var T_x_can_gateway_control::q_AutoTX

   If q_AutoTX = TRUE then the message transfered from source to destination bus will be transmitted automatically. \n
   If q_AutoTX = FALSE then the message will be transfered from source to destination bus but not transmitted
   automatically. This feature is useful if the gateway destination should be used as a kind of "TX_RTR" object and
   will be polled by RTR frames (un_RTRMode should be set to X_CAN_GATEWAY_RTR_DEST in this case).
*/
/*! \var T_x_can_gateway_control::q_AllIdType

   If q_AllIdType = TRUE then the acceptance filtering of the source object doesn't distinguish between 11bit and 29bit
   message identifiers. \n
   This feature may be used to relay all messages (with 11bit and 29bit identifiers) from the source bus to the
   destination bus \n
   If q_AllIdType = FALSE acceptance filtering will differ between 11bit and 29bit identifiers (default).

   \attention
   Setting q_AllIdType = TRUE makes only sense if t_GatewayMask.u32_Id = 0 (don't care) because the ID bits in the
   mask register are treated different for incoming 11bit and 29bit identifiers.
*/
/*! \var T_x_can_gateway_control::un_RTRMode

   The flag un_RTRMode controls the handling of RTR frames on the destination bus. \n
   If un_RTRMode = X_CAN_GATEWAY_RTR_NO then the RTR handling is switched off and no RTR frames are accepted by the
   destination object. \n
   If un_RTRMode = X_CAN_GATEWAY_RTR_DEST then RTR frames may be received on the destination object and this
   RTR acceptance will trigger the transmission of the message within the destination object. \n
   If un_RTRMode = X_CAN_GATEWAY_RTR_PASS then RTR frames may be received on the destination object and this
   RTR acceptance will trigger the transmission of a RTR frame from the source object (gateway RTR pass).

   \note
   Acceptance of RTR frames on the destination object is controlled by the ID filter specified by t_GatewayMask
   and t_GatewayMsg.t_Id.
*/
typedef struct
{
   uintn   q_CopyDlc    :  1;                   //!< copy DLC to destination CAN bus
   uintn   q_CopyId     :  1;                   //!< copy ID to destination CAN bus
   uintn   q_CopyData   :  1;                   //!< copy data to destination CAN bus
   uintn   q_AutoTX     :  1;                   //!< automatic transmission of destination data
   uintn   q_AllIdType  :  1;                   //!< handle standard 11bit and extended 29bit IDs
   uintn   un_RTRMode   :  2;                   //!< RTR mode
                                                //    X_CAN_GATEWAY_RTR_NO   = RTR disabled
                                                //    X_CAN_GATEWAY_RTR_DEST = RTR response at destination bus
                                                //    X_CAN_GATEWAY_RTR_PASS = pass RTR frame to source bus
} T_x_can_gateway_control;


/*! \var T_x_can_gateway_config::u16_HardBuffer


   The parameter u16_HardBuffer defines a hardware FIFO for the gateway object. A number > 0 defines the FIFO depth for
   CAN messages that should be relayed. Each FIFO element allocates an extra object out of the hardware message object
   pool.
*/
/*! \var T_x_can_gateway_config::t_GatewayId

   Specifies the CAN ID of the message object assigned to the source bus. In conjunction with t_GatewayMask
   this tupel defines the actually acceptance filter of the (source) can object. \n
   A message that pass the filter is transfered from source bus to destination bus!
*/
/*! \var T_x_can_gateway_config::t_GatewayMask

   Specifies the filter mask applied to the CAN ID of a message object assigned to the source bus. In conjunction with
   t_GatewayId this tupel defines the actually acceptance filter of the (source) can object. \n
   A message that pass the filter is transfered from source bus to destination bus!
*/
/*! \var T_x_can_gateway_config::t_GatewayMsg

   Specifies a default message (ID, DLC and data) for the destination bus.

   The default message is only relevant if the gateway control (see t_GatewayControl) is configured to transfer only a
   subset of the CAN message information (ID, DLC and data) from source to destination. \n
   In this case, the subset of the actually can message information transfered from source bus to destination is
   supplemented by the information from the default message.

   \note
   If the entire set of message information is transfered by the gateway mechanism, the default message is "don't
   care"!

   \note
   t_GatewayMsg.t_Id and t_GatewayMask define the acceptance filter for RTR frames received by the message object of
   the destination bus!
*/
typedef struct
{
   T_x_can_gateway_control t_GatewayControl;    // gateway control flags
   uint16            u16_HardBuffer;            // gateway hardware FIFO size (0 = no FIFO)
   T_x_can_id        t_GatewayId;               // gateway ID
   T_x_can_id        t_GatewayMask;             // gateway mask
   T_x_can_msg       t_GatewayMsg;              // default destination message
   uint32            u32_CallbackParameter;     // callback parameter (C++)
   PR_x_can_obj_InterruptCallback pr_Callback;  // TX/RX interrupt callback
} T_x_can_gateway_config;


#endif  //__cplusplus


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_CAN_TYPES_H */

/*! \} */
