//-----------------------------------------------------------------------------
/*!
   \internal
   \file       stwtypes.h
   \brief      STW specific standard defines and types

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     30.11.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _STWTYPES_H
#define _STWTYPES_H


#ifdef __cplusplus
extern "C" {
#endif



/* -- Defines ------------------------------------------------------------- */

// define function attributes for inline code
#define NO_INLINE       __attribute__((noinline))           // function attribute to suppress inline code
#define ALWAYS_INLINE   __attribute__((always_inline))      // function attribute to force inline code
#define INLINE          static inline ALWAYS_INLINE         // default GCC inline attribute

// define function attribute to designate functions as deprecated
#define DEPRECATED      __attribute__((deprecated))

// define attribute for weak symbols
#define WEAK            __attribute__((weak))

#ifdef __cplusplus
namespace stw_types
{
#endif

/* -- Types --------------------------------------------------------------- */

typedef unsigned char         uint8;      // data type unsigned 8bit
typedef signed char           sint8;      // data type signed 8bit
typedef unsigned short        uint16;     // data type unsigned 16bit
typedef signed short          sint16;     // data type signed 16bit
typedef unsigned long         uint32;     // data type unsigned 32bit
typedef signed long           sint32;     // data type signed 32bit
typedef unsigned long long    uint64;     // data type unsigned 64bit
typedef signed long long      sint64;     // data type signed 64bit

typedef float                 float32;    // data type IEEE float 32bit
typedef double                float64;    // data type IEEE float 64bit
// long double is treated like double (64bit), no extra typedef exists


// native data types
typedef unsigned int          uintn;      // native unsigned int
typedef signed int            sintn;      // native signed int
typedef char                  charn;      // native char type


/**********************************************************
 * create bit types "boolean" and "_bit" dependant on
 * the compiler (GNU ANSI-C or C++)
 **********************************************************/

#ifdef __cplusplus

   typedef bool               boolean;    // define type boolean
   #define _bit               bool        // tricore-g++ can't use type _bit variables -> use bool

#else

   typedef uint8              boolean;    // ANSI-C: STW type boolean is of type uint8

#endif

#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _STWTYPES_H */
