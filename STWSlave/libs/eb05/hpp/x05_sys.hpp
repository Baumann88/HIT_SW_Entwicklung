//-----------------------------------------------------------------------------
/*!
   \file        x05_sys.hpp
   \brief       CPP namespace extention for x05_sys.h

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

#ifndef __X05_SYS_HPP
#define __X05_SYS_HPP



/* -- Types --------------------------------------------------------------- */


/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x05_sys_init(void);
stw_types::sint16 x05_sys_get_component_info (const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Component, T_x_sys_info* const opt_Info);
stw_types::sint16 x05_sys_get_adc_value_scaled(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_MuxChannel, stw_types::sint32* const ops32_Value);
stw_types::sint16 x05_sys_set_adc_filter(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_AdcChannel, const stw_types::uint16 ou16_FilterConfig);
stw_types::sint16 x05_sys_get_adc_filter(const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_AdcChannel, stw_types::uint16* const opu16_FilterConfig);


#endif  // __X05_SYS_HPP
