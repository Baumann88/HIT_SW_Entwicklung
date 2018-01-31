//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_ser.h
   \brief      serial communication functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     26.06.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_SER_H
#define _X_SER_H

/* -- Includes ------------------------------------------------------------ */

#include "x_ser_types.h"
#include "x_stdtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X_SER_CH_MAX                (1u)           // total number of serial interfaces
#define X_SER_01                    (0u)           // select UART/ASC0

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
 
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_ser.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

sint16 x_ser_init( const uint16 ou16_Channel, const uint32 ou32_Bitrate, const uint16 ou16_Mode,
                   const uint16 ou16_StopBits, const uint32 ou32_ErrorCallbackParameter,
                   const PR_x_ser_ErrorCallback opr_ErrorCallback );
sint16 x_ser_close( const uint16 ou16_Channel );
sint16 x_ser_init_rx_buf( const uint16 ou16_Channel, const uint16 ou16_BufSize, const uint32 ou32_CallbackParameter,
                          const PR_x_ser_EventCallback opr_EventCallback );
sint16 x_ser_init_tx_buf( const uint16 ou16_Channel, const uint16 ou16_BufSize, const uint32 ou32_CallbackParameter,
                          const PR_x_ser_EventCallback opr_EventCallback );
sint16 x_ser_clear_rx_buf( const uint16 ou16_Channel );
sint16 x_ser_clear_tx_buf( const uint16 ou16_Channel );
sint16 x_ser_get_rx_buf_count( const uint16 ou16_Channel, uint16* const opu16_Count );
sint16 x_ser_get_tx_buf_count( const uint16 ou16_Channel, uint16* const opu16_Count );
sint16 x_ser_read( const uint16 ou16_Channel, const uint16 ou16_Count, uint8* const opu8_Data );
sint16 x_ser_write( const uint16 ou16_Channel, const uint16 ou16_Count, const uint8* const opu8_Data );
sint16 x_ser_write_string( const uint16 ou16_Channel, const charn* const opcn_String );
sint16 x_ser_set_bitrate( const uint16 ou16_Channel, const uint32 ou32_Bitrate );
sint16 x_ser_get_status( const uint16 ou16_Channel, T_x_ser_status* const opt_Status );


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_SER_H */
