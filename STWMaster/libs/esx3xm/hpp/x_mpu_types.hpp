//-----------------------------------------------------------------------------
/*!
   \file        x_mpu_types.hpp
   \brief       CPP namespace extention for x_mpu_types.h

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

#ifndef __X_MPU_TYPES_HPP
#define __X_MPU_TYPES_HPP



typedef struct
{
   stw_types::uint16 u16_MpuMode;
   stw_types::uint32 u32_Size;
   stw_types::uint32 u32_ParentMemClass;
   stw_types::uint32 u32_ProtectedMemClass;
} T_x_mpu_status;



#endif  // __X_MPU_TYPES_HPP
