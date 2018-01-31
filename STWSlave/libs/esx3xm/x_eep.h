//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_eep.h
   \brief      eeprom functions


   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     28.06.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_EEP_H
#define _X_EEP_H

/* -- Includes ------------------------------------------------------------ */

#include "x_eep_types.h"
#include "x_stdtypes.h"


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
   #include "./hpp/x_eep.hpp"
}
#else

/* -- Function Prototypes ------------------------------------------------- */

sint16 x_eep_read( const uint32 ou32_Address, const uint32 ou32_Count, uint8* const opu8_Data );
sint16 x_eep_write( const uint32 ou32_Address, const uint32 ou32_Count, const uint8* const opu8_Data );
sint16 x_eep_flush( void );
sint16 x_eep_get_status(const uint32 ou32_Address, const uint32 ou32_Size, T_x_eep_status* const opt_Status);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_EEP_H */
