//-----------------------------------------------------------------------------
/*!
   \file        x02_sys.hpp
   \brief       CPP namespace extention for x02_sys.h

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

#ifndef __X02_SYS_HPP
#define __X02_SYS_HPP



/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x02_sys_init(void);
stw_types::sint16 x02_sys_get_component_info (const stw_types::uint16 ou16_Slot, const stw_types::uint16 ou16_Component, T_x_sys_info* const opt_Info);


#endif  // __X02_SYS_HPP
