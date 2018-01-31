//-----------------------------------------------------------------------------
/*!
   \file        x05_out.hpp
   \brief       CPP namespace extention for x05_out.h

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

#ifndef __X05_OUT_HPP
#define __X05_OUT_HPP



/* -- Types --------------------------------------------------------------- */
// event callback function prototype
typedef void (*PR_x05_out_ErrorCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Event);
typedef T_x_out_status           T_x05_out_status;
typedef T_x_out_pid_parameters T_x05_out_pid_parameters;

/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x05_out_set_relay(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::uint8 ou8_OnOff);
stw_types::sint16 x05_out_init(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Type,
                               const stw_types::sint32 os32_MaxValue, const stw_types::uint32 ou32_CallbackParameter,
                               const PR_x05_out_ErrorCallback opr_ErrorCallback);
stw_types::sint16 x05_out_set_control_parameters(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                                                 const T_x05_out_pid_parameters* const opt_Parameters);
stw_types::sint16 x05_out_get_control_parameters(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel,
                                                 T_x05_out_pid_parameters* const opt_Parameters);
stw_types::sint16 x05_out_set_value(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Value);
stw_types::sint16 x05_out_set_frequency(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_Frequency);
stw_types::sint16 x05_out_get_status(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, T_x05_out_status* const opt_Status );
stw_types::sint16 x05_out_get_current(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Current );
stw_types::sint16 x05_out_get_voltage(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Voltage );
stw_types::sint16 x05_out_init_gnd_error(const stw_types::uint16 ou16_Slot, const stw_types::uint32 ou32_CallbackParameter,
                                         const PR_x05_out_ErrorCallback opr_ErrorCallback);
stw_types::sint16 x05_out_reset_gnd_error(const stw_types::uint16 ou16_Slot);
stw_types::sint16 x05_out_reset_oc_error(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Channel);


#endif  // __X05_OUT_HPP
