//-----------------------------------------------------------------------------
/*!
   \file        x02_in.hpp
   \brief       CPP namespace extention for x02_in.h

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

#ifndef __X02_IN_HPP
#define __X02_IN_HPP



/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x02_in_EventCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel);

typedef T_x_in_status  T_x02_in_status;

/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x02_in_init (const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                               const stw_types::uint16 ou16_Type, const stw_types::uint16 ou16_FilterConfig,
                               stw_types::uint16 ou16_InputCircuit, const stw_types::uint32 ou32_CallbackParameter,
                               const PR_x02_in_EventCallback opr_EventCallback);
stw_types::sint16 x02_in_get_value(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                                   stw_types::sint32 * const ops32_Value);
stw_types::sint16 x02_in_get_raw_value(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                                       stw_types::sint32 * const ops32_Value);
stw_types::sint16 x02_in_get_status(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, T_x02_in_status * const opt_Status);
stw_types::sint16 x02_in_set_threshold(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                                       const stw_types::sint32 os32_OnValue, const stw_types::sint32 os32_OffValue);
stw_types::sint16 x02_in_set_counter(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Value);
stw_types::sint16 x02_in_get_counter(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, stw_types::sint32 * const ops32_Value);

// deprecated api functions - may no longer be supported in further releases
stw_types::sint32 x02_in_reset_inc(const stw_types::uint32 ou32_Slot, const stw_types::uint32 ou32_Channel) __attribute__ ((deprecated));
stw_types::sint32 x02_in_set_inc_threshold(const stw_types::uint32 ou32_Slot, const stw_types::uint32 ou32_Channel,
                                           const stw_types::uint32 ou32_ThresholdHigh, const stw_types::uint32 ou32_ThresholdLow) __attribute__ ((deprecated));


#endif  // __X02_IN_HPP
