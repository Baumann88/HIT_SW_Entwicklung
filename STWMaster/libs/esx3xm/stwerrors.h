//-----------------------------------------------------------------------------
/*!
   \internal
   \file       stwerrors.h
   \brief      standard error defines for all STW modules

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     20.06.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _STWERRORS_H
#define _STWERRORS_H

/**********************************************************
 * standard error defines
 **********************************************************/

#ifdef __cplusplus

namespace stw_errors
{
   const stw_types::sint16 C_NO_ERR      =   static_cast<stw_types::sint16>(0);
   const stw_types::sint16 C_UNKNOWN_ERR =   static_cast<stw_types::sint16>(-1);
   const stw_types::sint16 C_WARN        =   static_cast<stw_types::sint16>(-2);
   const stw_types::sint16 C_DEFAULT     =   static_cast<stw_types::sint16>(-3);
   const stw_types::sint16 C_BUSY        =   static_cast<stw_types::sint16>(-4);
   const stw_types::sint16 C_RANGE       =   static_cast<stw_types::sint16>(-5);
   const stw_types::sint16 C_OVERFLOW    =   static_cast<stw_types::sint16>(-6);
   const stw_types::sint16 C_RD_WR       =   static_cast<stw_types::sint16>(-7);
   const stw_types::sint16 C_NOACT       =   static_cast<stw_types::sint16>(-8);
   const stw_types::sint16 C_COM         =   static_cast<stw_types::sint16>(-9);
   const stw_types::sint16 C_CONFIG      =   static_cast<stw_types::sint16>(-10);
   const stw_types::sint16 C_CHECKSUM    =   static_cast<stw_types::sint16>(-11);
   const stw_types::sint16 C_TIMEOUT     =   static_cast<stw_types::sint16>(-12);  
   const stw_types::sint16 C_IN_PROGRESS =   static_cast<stw_types::sint16>(-13);
}

#else

/* Cause */
#define C_NO_ERR           ( 0 )
#define C_UNKNOWN_ERR      (-1 )
#define C_WARN             (-2 )
#define C_DEFAULT          (-3 )
#define C_BUSY             (-4 )
#define C_RANGE            (-5 )
#define C_OVERFLOW         (-6 )
#define C_RD_WR            (-7 )
#define C_NOACT            (-8 )
#define C_COM              (-9 )
#define C_CONFIG           (-10)
#define C_CHECKSUM         (-11)
#define C_TIMEOUT          (-12)
#define C_IN_PROGRESS      (-13)

#endif


#endif  /* _STWERRORS_H */
