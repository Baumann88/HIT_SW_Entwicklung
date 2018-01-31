//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_err.h
   \brief      Errorhandler-Modul

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     19.11.2007  Heiss
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_ERR_H
#define _X_ERR_H

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include "x_err_types.h"
#include "x_err_defines.h"


#ifdef __cplusplus
extern "C" {
#endif

/* -- Defines ------------------------------------------------------------- */
#define X_ERR_WARNING    (1)         // hardware / environmental errors
#define X_ERR_ERROR      (2)         // programming erros
#define X_ERR_INTERNAL   (3)         // errors within bios functions


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
 
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_err.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
void x_err_init(const uint32 ou32_CallbackParameter, const PR_x_err_ErrorCallback opr_ErrorCallback);
T_x_err_handle* x_err_get_handle(void);

/* -- Implementation ------------------------------------------------------ */


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif // _X_ERR_H
