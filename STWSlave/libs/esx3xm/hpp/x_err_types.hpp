//-----------------------------------------------------------------------------
/*!
   \file        x_err_types.hpp
   \brief       CPP namespace extention for x_err_types.h

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

#ifndef __X_ERR_TYPES_HPP
#define __X_ERR_TYPES_HPP



typedef struct
{
   stw_types::charn  acn_Name[16];             //!< library name or short description
   stw_types::charn  acn_Version[16];          //!< version string (format: 1_23r4)
} T_x_err_library;

typedef struct
{
   const T_x_err_library * pt_Library;  //!< pointer to a library global datastructure for library details
   stw_types::uint16 u16_LibraryId;            //!< CCITT X25 CRC checksum over the 32 bytes of *pt_Library used as ID
   stw_types::uint16 u16_AreaNameIndex;        //!< specifies the area-index in which the error occured
   stw_types::uint16 u16_FunctionNameIndex;    //!< specifies the function-index in which the error occured
   stw_types::uint16 u16_ErrorIndex;           //!< specifies the index of the error
   stw_types::sint16 s16_ErrorCode;            //!< specifies the  errorcode (e.g. C_RANGE)
   stw_types::uint32 u32_Detail;               //!< additional error information
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
typedef void (*PR_x_err_ErrorCallback)(const stw_types::uint32 ou32_CallbackParameter, const T_x_err_error* const opt_Error,
                                       const stw_types::uint16 ou16_InterruptLevel);


typedef struct
{
   const T_x_err_library * pt_Library;       // pointer to a library global datastructure for library details
   stw_types::uint16 u16_LibraryId;                     // CCITT X25 CRC checksum over the 32 bytes of *pt_Library used as ID
   stw_types::uint32 u32_CallbackParameter;             // errorhandler callback parameter
   PR_x_err_ErrorCallback pr_ErrorHandler;   // errorhandler callback pointer
} T_x_err_handle;


#endif  // __X_ERR_TYPES_HPP
