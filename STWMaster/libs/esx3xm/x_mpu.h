//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_mpu.h
   \brief      memory protection unit support


   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     28.06.2006  Herb
   \endimplementation

   */
//-----------------------------------------------------------------------------

#ifndef _X_MPU_H
#define _X_MPU_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_mpu_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_mpu.hpp"
}
#else



/* -- Global Variables ---------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

sint16 x_mpu_init(const uint32 ou32_ParentMemClass, const uint32 ou32_Size1By, uint32 * const opu32_ProtectedMemClass);
sint16 x_mpu_get_status(T_x_mpu_status * const opt_Status);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _x_mpu_H */
