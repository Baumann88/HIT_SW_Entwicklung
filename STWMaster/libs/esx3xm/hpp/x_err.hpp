//-----------------------------------------------------------------------------
/*!
   \file        x_err.hpp
   \brief       CPP namespace extention for x_err.h

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

#ifndef __X_ERR_HPP
#define __X_ERR_HPP



/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
void x_err_init(const stw_types::uint32 ou32_CallbackParameter, const PR_x_err_ErrorCallback opr_ErrorCallback);
T_x_err_handle* x_err_get_handle(void);

/* -- Implementation ------------------------------------------------------ */


#endif  // __X_ERR_HPP
