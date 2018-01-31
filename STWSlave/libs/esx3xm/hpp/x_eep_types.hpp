//-----------------------------------------------------------------------------
/*!
   \file        x_eep_types.hpp
   \brief       CPP namespace extention for x_eep_types.h

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

#ifndef __X_EEP_TYPES_HPP
#define __X_EEP_TYPES_HPP



typedef struct
{
   stw_types::uint32 u32_EepromSizeByte;    // eeprom size in byte
   stw_types::uint32 u32_PageSizeByte;      // eeprom page size in byte
   stw_types::uint32 u32_OpenDataPages;     // open (not written) data pages inside cache ram
   stw_types::uint32 u32_FaultyDataPages;   // number of data pages with write errors
} T_x_eep_status;


#endif  // __X_EEP_TYPES_HPP
