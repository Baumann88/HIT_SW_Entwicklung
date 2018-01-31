//-----------------------------------------------------------------------------
/*!
   \internal
   \file       stdtypes.h
   \brief      standard defines and types for TriCore GCC projects

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     30.11.2004  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _STDTYPES_H
#define _STDTYPES_H


/* -- Includes ------------------------------------------------------------ */

#include <stddef.h>  // we need this include because of the NULL define


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// GCC supports the stringify operators
// PRQA S 341, 3453 3
#define STR(s)      #s           // the C preprocessor need two steps
#define XSTR(s)     STR(s)       // to stringify a macro...

#define TRUE        1            // boolean TRUE
#define FALSE       0            // boolean FALSE

#define ON          1            // boolean on == TRUE
#define OFF         0            // boolean off == FALSE

#define HIGH        1            // boolean HIGH == TRUE
#define LOW         0            // boolean LOW == FALSE


/* -- Types --------------------------------------------------------------- */


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _STDTYPES_H */
