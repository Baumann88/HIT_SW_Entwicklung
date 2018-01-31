//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x02_sys.h
   \brief      X02 expansion board initalisation routine

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     23.04.2007  Baldauf
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X02_SYS_H
#define _X02_SYS_H

/* -- Includes ------------------------------------------------------------ */
#include "x_stdtypes.h"
#include "x_sys.h"
#include "x_eb.h"

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************
 * compiler check will be inserted here in post build step
 * do not edit!
 **********************************************************/
#if ((__GNUC__ != 3) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 5))
 #error This Library should only be used with TRICORE GCC Compiler version 3.4.5
#endif


/* -- Types --------------------------------------------------------------- */

/* -- Defines ------------------------------------------------------------- */

// components for x02_sys_get_component_info
#define X02_SYS_COMPONENT_LIBRARY         (0)   // API Version
#define X02_SYS_COMPONENT_FPGA            (1)   // FPGA Version
#define X02_SYS_COMPONENT_CHANNEL_MAX     (2)

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x02_sys.hpp"
}
#else


/* -- Function Prototypes ------------------------------------------------- */
sint16 x02_sys_init(void);
sint16 x02_sys_get_component_info (const uint16 ou16_Slot, const uint16 ou16_Component, T_x_sys_info* const opt_Info);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
