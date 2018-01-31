//-----------------------------------------------------------------------------
/*!
   \file        x05_in.hpp
   \brief       CPP namespace extention for x05_in.h

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

#ifndef __X05_IN_HPP
#define __X05_IN_HPP



/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x05_in_EventCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel);
typedef T_x_in_status  T_x05_in_status;


/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x05_in_init(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                              const stw_types::uint16 ou16_Type, const stw_types::uint16 ou16_FilterConfig,
                              const stw_types::uint16 ou16_InputCircuit, const stw_types::uint32 ou32_CallbackParameter,
                              const PR_x05_in_EventCallback opr_EventCallback);
stw_types::sint16 x05_in_get_value(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, stw_types::sint32 * const ops32_Value);
stw_types::sint16 x05_in_get_raw_value(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, stw_types::sint32 * const ops32_Value);
stw_types::sint16 x05_in_get_status(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, T_x05_in_status* const opt_Status);


#endif  // __X05_IN_HPP
