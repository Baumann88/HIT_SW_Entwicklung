//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x05_lib.h
   \brief      expansion board eb05 library routines

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     23.02.2010  STW/GW
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   ***   add your log here (above the last entry)   ***
   23.02.2010        STW/GW         new implementation for eb05 \n
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef _X05_LIB_H
#define _X05_LIB_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* -- Defines ------------------------------------------------------------- */


#define  X05_LIB_MAJOR_VERSION    2
#define  X05_LIB_MINOR_VERSION    1
#define  X05_LIB_RELEASE          1

#define  X05_TARGET_ID          0               // library target id (not used by expansion board)
#define  X05_TARGET_VERSION     0               // library target version (not used by expansion board)

#define  X05_LIB_INFO_DEVICE_ID "Y_EB05"        // library target device id

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x05_lib.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
typedef T_x_lib_version    T_x05_lib_version;


/* -- Function Prototypes ------------------------------------------------- */
sint16 x05_lib_get_version(T_x05_lib_version* const opt_Version);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
