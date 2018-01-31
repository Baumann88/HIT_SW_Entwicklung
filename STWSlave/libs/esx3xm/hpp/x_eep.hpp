//-----------------------------------------------------------------------------
/*!
   \file        x_eep.hpp
   \brief       CPP namespace extention for x_eep.h

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

#ifndef __X_EEP_HPP
#define __X_EEP_HPP


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_eep_read( const stw_types::uint32 ou32_Address, const stw_types::uint32 ou32_Count, stw_types::uint8* const opu8_Data );
stw_types::sint16 x_eep_write( const stw_types::uint32 ou32_Address, const stw_types::uint32 ou32_Count, const stw_types::uint8* const opu8_Data );
stw_types::sint16 x_eep_flush( void );
stw_types::sint16 x_eep_get_status(const stw_types::uint32 ou32_Address, const stw_types::uint32 ou32_Size, T_x_eep_status* const opt_Status);


#endif  // __X_EEP_HPP
