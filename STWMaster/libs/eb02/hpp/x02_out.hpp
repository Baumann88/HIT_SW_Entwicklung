//-----------------------------------------------------------------------------
/*!
   \file        x02_out.hpp
   \brief       CPP namespace extention for x02_out.h

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

#ifndef __X02_OUT_HPP
#define __X02_OUT_HPP



/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x02_out_ErrorCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Event);
typedef T_x_out_status T_x02_out_status;


/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x02_out_init(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                               const stw_types::uint16 ou16_Type, const stw_types::sint32 os32_MaxValue,
                               const stw_types::uint32 ou32_CallbackParameter,
                               const PR_x02_out_ErrorCallback opr_ErrorCallback);

stw_types::sint16 x02_out_set_value(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Value);
stw_types::sint16 x02_out_reset_error(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel);
stw_types::sint16 x02_out_get_status(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, T_x02_out_status * const opt_Status );


#endif  // __X02_OUT_HPP
