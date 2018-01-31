//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_ser_types.h
   \brief      generic x_ser types and defines for serial communication functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     06.10.2009  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

/*!
   \addtogroup     x_ser
   \{
*/

#ifndef _X_SER_TYPES_H
#define _X_SER_TYPES_H

/* -- Includes ------------------------------------------------------------ */

#include "stwtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// UART modes
#define X_SER_MODE_7DB_EVEN_PARITY  (0x0023u)      // use 7bits and even parity
#define X_SER_MODE_7DB_ODD_PARITY   (0x1023u)      // use 7bits and odd parity
#define X_SER_MODE_8DB_EVEN_PARITY  (0x0027u)      // use 8bits and even parity
#define X_SER_MODE_8DB_ODD_PARITY   (0x1027u)      // use 8bits and odd parity
#define X_SER_MODE_8DB_NO_PARITY    (0x0001u)      // use 8bits, no parity

// status bits for x_ser_get_status
#define X_SER_STATUS_PARITY_ERR     (0x01u)        // parity error
#define X_SER_STATUS_FRAME_ERR      (0x02u)        // frame error
#define X_SER_STATUS_OVERRUN        (0x04u)        // hardware buffer overflow error
#define X_SER_STATUS_RXFIFO_OVERRUN (0x08u)        // RX FIFO buffer overflow error
#define X_SER_STATUS_TXFIFO_OVERRUN (0x10u)        // TX FIFO buffer overflow error


/* -- Types --------------------------------------------------------------- */

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_ser_types.hpp"
}
#else


//-----------------------------------------------------------------------------
/*!
   \brief   Signature of the callback function to handle serial interface errors.

   Serial RS232 error callback is intended to implement an application specific error reaction.
   The callback is executed whenever a RS232 transfer related error occur.

   The error is passed to the callback function as a bit coded information in parameter \b ou32_Status.
   The status correspond to the status that can be found in T_x_ser_status::u32_Status. \n
   However \b ou32_Status contains only those flags that actually leads to the error. In contrast to
   T_x_ser_status::u32_Status that contains all errof flags since the last time the status was read using function
   x_ser_get_status.

   The following error flags may be possible:
   - Bit0: X_SER_STATUS_PARITY_ERR        paritiy bit of the latest RX characters was incorrect
                                          -> character will not be saved!
   - Bit1: X_SER_STATUS_FRAME_ERR         the latest RX character had incorrect frame format
   - Bit2: X_SER_STATUS_OVERRUN           the pending character in the RX hardware buffer was overwritten with new data
   - Bit3: X_SER_STATUS_RXFIFO_OVERRUN    the character read from the RX hardware buffer was dropped as the
                                          RX software buffer is full

   \param[in]        ou32_CallbackParameter     A user defined callback parameter
                                                (can be used to take the instance pointer of a C++ object)
   \param[in]        ou16_Channel               RS232 interface channel number the error occured
   \param[in]        ou32_Status                RS232 status involved into the callback - see:  T_x_ser_status.

   \return
   void
*/
//-----------------------------------------------------------------------------
typedef void (*PR_x_ser_ErrorCallback)(const uint32 ou32_Parameter, const uint16 ou16_Channel,
                                       const uint32 ou32_Status);


//-----------------------------------------------------------------------------
/*!
   \brief   Signature of the callback function called when a TX or RX event occurres on the serial interface.

   Serial RS232 event callback is intended to implement an application specific TX and RX reaction.
   The callback may be executed for TX and RX events.

   \par TX Event
   Whenever the tranmission of an character has been started, the TX event callback will be executed. The user defined
   parameter (specified at callback installation) ,the channel number of the involved serial interface and the
   actually TX data will be passed back to the callback function.

   \note
   This event can be used by the application to reload the TX buffer!

   \par RX Event
   Whenever a character was received successfully the RX event will be executed. The user defined
   parameter (specified at callback installation) mthe channel number of the involved serial interface and the
   actually RX data will be passed back to the callback function.

   \note
   This event is executed before the RX data will be stored into the RX software buffer. Neverthelesl the data will
   be stored into the RX software buffer afterwards. \n
   If the RX data will be processed in the callback the user application is responsible to prefent an RX buffer
   overflow (e.g. by clearing the buffer cyclically).


   \param[in]        ou32_CallbackParameter          a user defined callback parameter
                                                     (can be used to take the instance pointer of a C++ object)
   \param[in]        ou16_Channel                    RS232 interface channel number the event occured
   \param[in]        ou8_Data                        the RX data resp. the TX data

   \return
   void
*/
//-----------------------------------------------------------------------------
typedef void (*PR_x_ser_EventCallback)(const uint32 ou32_Parameter, const uint16 ou16_Channel, const uint8 ou8_Data);



/*! \var T_x_ser_status::u32_Status

   This variable contains bitcoded status information of the serial RS232 interface. The status variable is cleared
   whenever the status is read using x_ser_get_status. According to this the flags reflect the status since the last
   time the status was read. \n
   Each bit is represented by a define:
   - Bit0: X_SER_STATUS_PARITY_ERR        the paritiy bit of at least one of the received characters was incorrect
   - Bit1: X_SER_STATUS_FRAME_ERR         at least one of the received characters had incorrect frame format
   - Bit2: X_SER_STATUS_OVERRUN           at least one character was lost due to a  RX (hardware) buffer overflow
   - Bit3: X_SER_STATUS_RXFIFO_OVERRUN    at least one character was lost as RX (software) buffer was full

   \note
   The status X_SER_STATUS_TXFIFO_OVERRUN (bit 4) is intercepted by the BIOS. So this error flag will never occur!
*/
typedef struct
{
   uint32   u32_Bitrate;      // configured bitrate (bits/s)
   uint16   u16_Mode;         // operating mode (no_of_data_bits X parity_bit)
   uint16   u16_Stopbit;      // number of stop bits
   uint32   u32_Status;       // bit coded: X_SER_STATUS_...
   uint16   u16_RxBufSize;    // RX buffer size in byte
   uint16   u16_TxBufSize;    // TX buffer size in byte
} T_x_ser_status;


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_SER_TYPES_H */

/*! \} */
