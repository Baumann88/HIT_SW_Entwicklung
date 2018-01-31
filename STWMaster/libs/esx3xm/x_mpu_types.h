//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_mpu_types.h
   \brief      generic x_mpu types and defines used in all software layers

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     14.02.2012  Baldauf
   \endimplementation

*/
//-----------------------------------------------------------------------------
/*!
   \addtogroup     x_mpu
   \{
*/
//-----------------------------------------------------------------------------

#ifndef _X_MPU_TYPES_H
#define _X_MPU_TYPES_H


/* -- Includes ------------------------------------------------------------ */

#include "stwtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */
#define X_MPU_MODE_ACTIVE                 (0x0001u)
#define X_MPU_MODE_SAFETY_LAYER_USED      (0x0002u)

/* -- Types --------------------------------------------------------------- */

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_mpu_types.hpp"
}
#else


typedef struct
{
    uint16 u16_MpuMode;
    uint32 u32_Size;
    uint32 u32_ParentMemClass;
    uint32 u32_ProtectedMemClass;
} T_x_mpu_status;



#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif // _X_MPU_TYPES_H

/*! \} */
