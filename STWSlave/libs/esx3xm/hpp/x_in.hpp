//-----------------------------------------------------------------------------
/*!
   \file        x_in.hpp
   \brief       CPP namespace extention for x_in.h

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

#ifndef __X_IN_HPP
#define __X_IN_HPP



/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint16   u16_InputType;       // input type configuration
   stw_types::uint16   u16_InputCircuit;    // input circuit configuration
   stw_types::uint16   u16_FilterConfig;    // configured filter value for digital debouncing or analog filtering
   stw_types::uint16   u16_DigitalState;    // digital input state (not filtered)
   stw_types::uint16   u16_AdcValue;        // analog value in 12bit ADC digits (not filtered)
   stw_types::sint32   s32_ScaledValue;     // scaled analog value (not filtered)
} T_x_in_status;

typedef struct
{
   stw_types::uint16 u16_AvgSamples;              // number of samples for average calculation [1 ... X_IN_FREQ_AVG_SAMPLES_MAX]
   stw_types::uint16 u16_AvgMode;                 // average operation mode
   stw_types::uint16 u16_FilterConfigUs;          // input debounce filter in micro seconds [0 ... 65535]
   stw_types::uint16 u16_VirtualPeriodThreshold;  // virtual period threshold in per mil [1000 ... 65535]
   // u16_VirtualPeriodThreshold < 1000 => virtual period feature deactivated
   stw_types::uint32 u32_MinFrequency;            // input min frequency measurement limit scaled in milli Hertz
   stw_types::uint32 u32_MaxFrequency;            // input max frequency measurement limit scaled in milli Hertz
} T_x_t_in_freq_avg_config;


/* -- Types --------------------------------------------------------------- */

// event callback function prototype
typedef void (*PR_x_in_EventCallback)(const stw_types::uint32 ou32_CallbackParameter, const stw_types::uint16 ou16_Channel);


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_in_init(const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Type, const stw_types::uint16 ou16_FilterConfig,
                            const stw_types::uint16 ou16_InputCircuit, const stw_types::uint32 ou32_CallbackParameter,
                            const PR_x_in_EventCallback opr_EventCallback);
stw_types::sint16 x_in_get_value(const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Value);
stw_types::sint16 x_in_get_raw_value(const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Value);
stw_types::sint16 x_in_get_status(const stw_types::uint16 ou16_Channel, T_x_in_status* const opt_Status);
stw_types::sint16 x_in_get_frequency(const stw_types::uint16 ou16_Channel, stw_types::uint32* const opu32_Frequency);
stw_types::sint16 x_in_get_duty_cycle(const stw_types::uint16 ou16_Channel, stw_types::uint32* const opu32_DutyCycle);
stw_types::sint16 x_in_get_counter(const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Counter);
stw_types::sint16 x_in_set_counter(const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Counter);
stw_types::sint16 x_in_get_counter_direction(const stw_types::uint16 ou16_Channel, stw_types::uint8* const opu8_CntDir);
stw_types::sint16 x_t_in_init_frequency_avg(const stw_types::uint16 ou16_Channel, const T_x_t_in_freq_avg_config* const opt_Config);
stw_types::sint16 x_t_in_get_frequency_avg(const stw_types::uint16 ou16_Channel, stw_types::uint32* const opu32_Frequency);


#endif  // __X_IN_HPP
