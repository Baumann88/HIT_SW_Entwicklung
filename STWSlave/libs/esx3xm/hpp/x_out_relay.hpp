//-----------------------------------------------------------------------------
/*!
   \file        x_out_relay.hpp
   \brief       CPP namespace extention for x_out_relay.h

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

#ifndef __X_OUT_RELAY_HPP
#define __X_OUT_RELAY_HPP



/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint8  u8_OnOff;              // last output state set by software
   stw_types::sint32 s32_VoltageUb;         // unit mV (filtered, scaled ADC value)
   stw_types::sint32 s32_VoltageUc;         // unit mV (filtered, scaled ADC value)
   stw_types::sint32 s32_CurrentI;          // unit uA (filtered, scaled ADC value)
   stw_types::uint16 u16_RelayState;        // relay error states (or'ed X_OUT_RELAY_STATE_...; 0 = no error currently pending)
   stw_types::uint16 u16_ErrorFlags;        // relay error flags (sticky relay error states)
} T_x_out_relay_status;


typedef void (*PR_x_out_ErrorRelayCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Channel,
                                            const stw_types::uint16 ou16_Event);

typedef struct
{
   stw_types::uint32                        u32_CallbackParameter;
   PR_x_out_ErrorRelayCallback   pr_ErrorCallback;
} T_x_out_relay_config;


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_out_relay_init(const stw_types::uint16 ou16_Channel, const T_x_out_relay_config * const opt_Config);
stw_types::sint16 x_out_relay_set(const stw_types::uint16 ou16_Channel, const stw_types::uint8 ou8_OnOff);
stw_types::sint16 x_out_relay_set_all(const stw_types::uint8 ou8_OnOff);
stw_types::sint16 x_out_relay_get_status(const stw_types::uint16 ou16_Channel, T_x_out_relay_status * const opt_Status);
stw_types::sint16 x_out_relay_reset_error(const stw_types::uint16 ou16_Channel);


#endif  // __X_OUT_RELAY_HPP
