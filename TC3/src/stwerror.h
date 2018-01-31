/**
 * \file      xll_stderror.h
 * \brief     standard error defines for all BIOS modules
 *
 * \author    Ulrich Herb
 * \date      20.06.2006
 * \version   1.00
 *
 *
 * \par Specifications:
 *
 * \par History:
 * 07.03.2008:  Herb, checked STW naming conventions
 * 05.09.2007:  Herb, MISRA-C:2004 rules checked
 * 20.06.2006:  Herb, file created  \n
 *****************************************************************************/

#ifndef _XLL_STDERROR_H
#define _XLL_STDERROR_H


#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************
 * standard error defines
 **********************************************************/

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

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _XLL_STDERROR_H */
