//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x02_lib_version.h
   \brief      X02 expansion board library version

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     23.04.2007  Baldauf
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef X02_LIB_VERSION_H
#define X02_LIB_VERSION_H

/* -- Includes ------------------------------------------------------------ */
#include "x_stdtypes.h"
#include "x_lib.h"
#include "x02_lib_string.h"

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************
 * temporary MISRA deviations:
 *
 * message 3219 off:
 * message 3450 off: the TriCore GCC need inline functions to be declared static
 * message 3480 off: inline functions are defined inside the header file
 * message 6002 off: inline functions are declared static, but they have global scope
 ***************************************************************************/

//PRQA S 3219, 3450, 3480, 6002 ++


/* -- Defines ------------------------------------------------------------- */

#define  X02_LIB_MAJOR_VERSION  2               // library version
#define  X02_LIB_MINOR_VERSION  0               // library minor version
#define  X02_LIB_RELEASE        5               // library release

#define  X02_TARGET_ID          0               // library target id (not used by expansion board)
#define  X02_TARGET_VERSION     0               // library target version (not used by expansion board)

#define  X02_LIB_INFO_DEVICE_ID "Y_EB02"        // library target device id


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x02_lib.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
typedef T_x_lib_version    T_x02_lib_version;


/* -- Global Variables ---------------------------------------------------- */

sint16 x02_lib_get_version(T_x02_lib_version * const opt_Version);

// deprecated prototype (for compatibility with older releases only)
INLINE sint16 x02_get_lib_version(T_x02_lib_version * const opt_Version)
{
   return x02_lib_get_version(opt_Version);
}


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_LIB_VERSION_H */
