//-----------------------------------------------------------------------------
/*!
   \file        x_out.hpp
   \brief       CPP namespace extention for x_out.h

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

#ifndef __X_OUT_HPP
#define __X_OUT_HPP



/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint16   u16_OutputType;         // the configured output type
   stw_types::sint32   s32_MaxValue;           // value that defines 100% output
   stw_types::sint32   s32_OutValue;           // output value (depends on type)
   stw_types::uint32   u32_OutFrequency;       // output frequency
   stw_types::uint32   u32_SetTime;            // system time when output was set (milli seconds since system start)
   stw_types::uint32   u32_OutState;           // output state (bit coded)
} T_x_out_status;

typedef struct
{
   stw_types::sint32   s32_Setpoint;           // current control setpoint (also control start value)
   stw_types::sint32   s32_P_Value;            // proportional gain in 0.001 KR
   stw_types::sint16   s16_I_Value;            // integral time Ti in ms
   stw_types::sint16   s16_D_Value;            // derivation time Td in ms
   stw_types::sint16   s16_SampleTime;         // current control sample time T in ms
   stw_types::sint16   s16_OutputLimitMin;     // minimum output duty cycle in 0.01%
   stw_types::sint16   s16_OutputLimitMax;     // maximum output duty cycle in 0.01%
} T_x_out_pid_parameters;


/* -- Types --------------------------------------------------------------- */

// error callback function prototype
typedef void (*PR_x_out_ErrorCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Channel,
                                       const stw_types::uint16 ou16_Event);


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_out_init(const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Type, const stw_types::sint32 os32_MaxValue,
                             const stw_types::uint32 ou32_CallbackParameter, const PR_x_out_ErrorCallback opr_ErrorCallback);
stw_types::sint16 x_out_set_control_parameters(const stw_types::uint16 ou16_Channel, const T_x_out_pid_parameters* const opt_Parameters);
stw_types::sint16 x_out_get_control_parameters(const stw_types::uint16 ou16_Channel, T_x_out_pid_parameters* const opt_Parameters);
stw_types::sint16 x_out_set_value(const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Value);
stw_types::sint16 x_out_set_frequency(const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_Frequency);
stw_types::sint16 x_out_get_current(const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Current);
stw_types::sint16 x_out_get_status(const stw_types::uint16 ou16_Channel, T_x_out_status * const opt_Status);
stw_types::sint16 x_out_reset_error(const stw_types::uint16 ou16_Channel);
stw_types::sint16 x_out_set_value_ramping(const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Value,
                                          const stw_types::uint32 ou32_DeltaOutput, const stw_types::uint32 ou32_DeltaTime);

#endif  // __X_OUT_HPP
