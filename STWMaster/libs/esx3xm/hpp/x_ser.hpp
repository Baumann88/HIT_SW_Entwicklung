//-----------------------------------------------------------------------------
/*!
   \file        x_ser.hpp
   \brief       CPP namespace extention for x_ser.h

   This header was automatically created. DO NOT EDIT!

   \implementation
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     by hpp_generator.pl
   \endimplementation


   \internal
   \history
   Date(dd.mm.yyyy)  Author                Description
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef __X_SER_HPP
#define __X_SER_HPP



/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_ser_init( const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_Bitrate, const stw_types::uint16 ou16_Mode,
                              const stw_types::uint16 ou16_StopBits, const stw_types::uint32 ou32_ErrorCallbackParameter,
                              const PR_x_ser_ErrorCallback opr_ErrorCallback );
stw_types::sint16 x_ser_close( const stw_types::uint16 ou16_Channel );
stw_types::sint16 x_ser_init_rx_buf( const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_BufSize, const stw_types::uint32 ou32_CallbackParameter,
                                     const PR_x_ser_EventCallback opr_EventCallback );
stw_types::sint16 x_ser_init_tx_buf( const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_BufSize, const stw_types::uint32 ou32_CallbackParameter,
                                     const PR_x_ser_EventCallback opr_EventCallback );
stw_types::sint16 x_ser_clear_rx_buf( const stw_types::uint16 ou16_Channel );
stw_types::sint16 x_ser_clear_tx_buf( const stw_types::uint16 ou16_Channel );
stw_types::sint16 x_ser_get_rx_buf_count( const stw_types::uint16 ou16_Channel, stw_types::uint16* const opu16_Count );
stw_types::sint16 x_ser_get_tx_buf_count( const stw_types::uint16 ou16_Channel, stw_types::uint16* const opu16_Count );
stw_types::sint16 x_ser_read( const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Count, stw_types::uint8* const opu8_Data );
stw_types::sint16 x_ser_write( const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Count, const stw_types::uint8* const opu8_Data );
stw_types::sint16 x_ser_write_string( const stw_types::uint16 ou16_Channel, const stw_types::charn* const opcn_String );
stw_types::sint16 x_ser_set_bitrate( const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_Bitrate );
stw_types::sint16 x_ser_get_status( const stw_types::uint16 ou16_Channel, T_x_ser_status* const opt_Status );


#endif  // __X_SER_HPP
