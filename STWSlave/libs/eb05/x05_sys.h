//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x05_sys.h
   \brief      expansion board eb05 system routines

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     19.02.2010  STW/GW
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   ***   add your log here (above the last entry)   ***
   19.02.2010        STW/GW         new implementation for eb05 \n
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef _X05_SYS_H
#define _X05_SYS_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_sys.h"

#ifdef __cplusplus
extern "C" {
#endif



/**********************************************************
 * compiler check will be inserted here in post build step
 * do not edit!
 **********************************************************/
#if ((__GNUC__ != 3) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 5))
 #error This Library should only be used with TRICORE GCC Compiler version 3.4.5
#endif


// X05_TIMESTAMP is set by a perl script during the post build step
// PRQA S 3332 7
#ifndef X05_TIMESTAMP
   #define X05_TIMESTAMP    1402916822
#endif

#ifdef X04_TIMESTAMP
   #if (X04_TIMESTAMP != X05_TIMESTAMP)
      #define X05_LIBRARY_VERSION_ERROR
   #endif
#endif
#ifdef X08_TIMESTAMP
   #if (X08_TIMESTAMP != X05_TIMESTAMP)
      #define X05_LIBRARY_VERSION_ERROR
   #endif
#endif


#ifdef X05_LIBRARY_VERSION_ERROR
   #error eb05, eb04 and eb08 Libraries are different; please upgrade to same version!
#endif


/* -- Defines ------------------------------------------------------------- */
// multiplexer channels for eb05
#define X05_ADCMUX_BOARD_POWER_UB            (0u)
#define X05_ADCMUX_VSUP_1V25                 (1u)
#define X05_ADCMUX_VREF_3V3                  (2u)
#define X05_ADCMUX_BOARD_POWER_SWITCHED      (3u)
#define X05_ADCMUX_VREF1_5V                  (4u)
#define X05_ADCMUX_GND_OFFSET                (5u)
#define X05_ADCMUX_VSUP_5V_BOARD_GND         (6u)
#define X05_ADCMUX_VSUP_12V_BOARD_GND        (7u)
#define X05_ADCMUX_VREF_0V64                 (8u)
#define X05_ADCMUX_VSUP_12V_DIGITAL_GND      (9u)
#define X05_ADCMUX_TOTAL_CURRENT             (10u)
#define X05_ADCMUX_VSUP_5V_ANALOG_GND        (11u)
#define X05_ADCMUX_VSUP_MINUS_5V_ANALOG_GND  (12u)
#define X05_ADCMUX_TEMP_SENSE                (13u)
#define X05_ADCMUX_VREF2_5V                  (14u)
#define X05_NUM_MUX_CHANNELS                 (15u)


// ADC channel defines for input / output pins
#define X05_ADC_CH_MAX                       (12u)
#define X05_ADC_I_OUT_01                     (0u)
#define X05_ADC_I_OUT_02                     (1u)
#define X05_ADC_I_OUT_03                     (2u)
#define X05_ADC_I_OUT_04                     (3u)
#define X05_ADC_I_OUT_05                     (4u)
#define X05_ADC_I_OUT_06                     (5u)
#define X05_ADC_I_OUT_07                     (6u)
#define X05_ADC_I_OUT_08                     (7u)
#define X05_ADC_U_IN_01                      (8u)
#define X05_ADC_U_IN_02                      (9u)
#define X05_ADC_U_IN_03                      (10u)
#define X05_ADC_U_IN_04                      (11u)

// components for x05_sys_get_component_info
#define X05_SYS_COMPONENT_LIBRARY            (0)   // API Version
#define X05_SYS_COMPONENT_FPGA               (1)   // FPGA Version
#define X05_SYS_COMPONENT_CHANNEL_MAX        (2)

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x05_sys.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */


/* -- Function Prototypes ------------------------------------------------- */
sint16 x05_sys_init(void);
sint16 x05_sys_get_component_info (const uint16 ou16_Slot, const uint16 ou16_Component, T_x_sys_info* const opt_Info);
sint16 x05_sys_get_adc_value_scaled(const uint16 ou16_Slot, const uint16 ou16_MuxChannel, sint32* const ops32_Value);
sint16 x05_sys_set_adc_filter(const uint16 ou16_Slot, const uint16 ou16_AdcChannel, const uint16 ou16_FilterConfig);
sint16 x05_sys_get_adc_filter(const uint16 ou16_Slot, const uint16 ou16_AdcChannel, uint16* const opu16_FilterConfig);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
