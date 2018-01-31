//-----------------------------------------------------------------------------
/*!
   \file       stwtypes.h
   \brief      STW specific standard defines and types

   Definition of standard types according to STW C coding rules
   here: for gnu compiler (gcc) - cpu-type: 32bit powerpc controllers

   \implementation
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     12.03.2007  STW/A.Stangl
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   13.03.2009        STW/F.Belser  adaptions for 32bit powerpc controllers
   12.03.2007        STW/A.Stangl  file created
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef _STWTYPES_H
#define _STWTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */

/* -- Defines ------------------------------------------------------------- */
#define INLINE inline

/* -- Types --------------------------------------------------------------- */
typedef unsigned char         uint8;      // data type unsigned 8bit
typedef signed char           sint8;      // data type signed 8bit
typedef unsigned short        uint16;     // data type unsigned 16bit
typedef signed short          sint16;     // data type signed 16bit
typedef unsigned long         uint32;     // data type unsigned 32bit
typedef signed long           sint32;     // data type signed 32bit
typedef unsigned long long    uint64;     // data type unsigned 64bit (requires compiler option "--long-long")
typedef signed long long      sint64;     // data type signed 64bit (requires compiler option "--long-long")

typedef float                 float32;    // data type IEEE float 32bit
typedef double                float64;    // data type IEEE float 64bit
typedef long double           float80;    // data type IEEE float 80bit

// native data types
typedef unsigned int          uintn;      // native unsigned int
typedef signed int            sintn;      // native signed int
typedef char                  charn;      // native char type

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

/* -- Implementation ------------------------------------------------------ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _STWTYPES_H */
