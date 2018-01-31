//-----------------------------------------------------------------------------
/*!
   \file        x_mpu.hpp
   \brief       CPP namespace extention for x_mpu.h

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

#ifndef __X_MPU_HPP
#define __X_MPU_HPP




/* -- Global Variables ---------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_mpu_init(const stw_types::uint32 ou32_ParentMemClass, const stw_types::uint32 ou32_Size1By, stw_types::uint32 * const opu32_ProtectedMemClass);
stw_types::sint16 x_mpu_get_status(T_x_mpu_status * const opt_Status);


#endif  // __X_MPU_HPP
