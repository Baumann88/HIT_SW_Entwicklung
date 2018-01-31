//-----------------------------------------------------------------------------
/*!
   \file        x02_lib.hpp
   \brief       CPP namespace extention for x02_lib.h

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

#ifndef __X02_LIB_HPP
#define __X02_LIB_HPP



/* -- Types --------------------------------------------------------------- */
typedef T_x_lib_version    T_x02_lib_version;


/* -- Global Variables ---------------------------------------------------- */

stw_types::sint16 x02_lib_get_version(T_x02_lib_version * const opt_Version);

// deprecated prototype (for compatibility with older releases only)
INLINE stw_types::sint16 x02_get_lib_version(T_x02_lib_version * const opt_Version)
{
   return x02_lib_get_version(opt_Version);
}


#endif  // __X02_LIB_HPP
