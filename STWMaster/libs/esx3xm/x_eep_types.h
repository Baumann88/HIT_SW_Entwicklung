//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_eep_types.h
   \brief      generic x_eep types and defines used in all software layers

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     01.12.2011  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------
/*!
   \addtogroup     x_eep
   \{
*/
//-----------------------------------------------------------------------------

#ifndef _X_EEP_TYPES_H
#define _X_EEP_TYPES_H


/* -- Includes ------------------------------------------------------------ */

#include "stwtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

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
   #include "./hpp/x_eep_types.hpp"
}
#else


typedef struct
{
   uint32 u32_EepromSizeByte;    // eeprom size in byte
   uint32 u32_PageSizeByte;      // eeprom page size in byte
   uint32 u32_OpenDataPages;     // open (not written) data pages inside cache ram
   uint32 u32_FaultyDataPages;   // number of data pages with write errors
} T_x_eep_status;


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif // _X_EEP_TYPES_H

/*! \} */
