//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_err_types.h
   \brief      generic x_err types and defines used in all software layers

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     30.11.2004  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------
/*!
   \addtogroup     x_err
   \{
*/
//-----------------------------------------------------------------------------

#ifndef _X_ERR_TYPES_H
#define _X_ERR_TYPES_H

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
   #include "./hpp/x_err_types.hpp"
}
#else


typedef struct
{
   charn  acn_Name[16];             //!< library name or short description
   charn  acn_Version[16];          //!< version string (format: 1_23r4)
} T_x_err_library;

typedef struct
{
   const T_x_err_library * pt_Library;  //!< pointer to a library global datastructure for library details
   uint16 u16_LibraryId;            //!< CCITT X25 CRC checksum over the 32 bytes of *pt_Library used as ID
   uint16 u16_AreaNameIndex;        //!< specifies the area-index in which the error occured
   uint16 u16_FunctionNameIndex;    //!< specifies the function-index in which the error occured
   uint16 u16_ErrorIndex;           //!< specifies the index of the error
   sint16 s16_ErrorCode;            //!< specifies the  errorcode (e.g. C_RANGE)
   uint32 u32_Detail;               //!< additional error information
} T_x_err_error;

//-----------------------------------------------------------------------------
/*!
   \brief   Signature of the error handler callback function.

   \param[in]   ou32_CallbackParameter    a user defined callback parameter
                                          (can be used to take the instance pointer of a C++ object)
   \param[in]   opt_Error                 data set of error information

   \return
   void
*/
//-----------------------------------------------------------------------------
typedef void (*PR_x_err_ErrorCallback)(const uint32 ou32_CallbackParameter, const T_x_err_error* const opt_Error,
                                       const uint16 ou16_InterruptLevel);


typedef struct
{
   const T_x_err_library * pt_Library;       // pointer to a library global datastructure for library details
   uint16 u16_LibraryId;                     // CCITT X25 CRC checksum over the 32 bytes of *pt_Library used as ID
   uint32 u32_CallbackParameter;             // errorhandler callback parameter
   PR_x_err_ErrorCallback pr_ErrorHandler;   // errorhandler callback pointer
} T_x_err_handle;


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif // _X_ERR_TYPES_H

/*! \} */
