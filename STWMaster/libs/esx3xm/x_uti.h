//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_uti.h
   \brief      utility functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     08.03.2006  Ulrich Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_UTI_H
#define _X_UTI_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
 
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_uti.hpp"
}
#else


/* -- Function Prototypes ------------------------------------------------- */

//-----------------------------------------------------------------------------
/*!
   \brief    calculate CRC over n bytes \ pu8_Data

             the function use the CCITT X25 polynomial 0x11021 \n
             the start value *pwCRC should be 0xFFFF \n
             it uses the look up table mawCRC16[] \n

   \ingroup  x_uti

   \param    ou32_Count: number of data bytes that should be CRC checked \n
   \param    opu8_Data:  data pointer \n
   \param    opu16_Crc:  pointer to CRC value, start value should be 0xFFFF \n

   \return   C_NO_ERR \n

   \created  08.03.2006  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_uti_calc_crc_16(const uint32 ou32_Count, const uint8* const opu8_Data, uint16* const opu16_Crc);


//-----------------------------------------------------------------------------
/*!
   \brief    calculate STW CRC over n bytes \ pu8_Data

             the function use the polynomial 0x11021 \n
             the start value *pwCRC should be 0x0000 \n
             it uses the look up table mawCRC16[] \n

   \ingroup  x_uti

   \note     the STW CRC algorithm is not compatible to standard CRC generation \n

   \param    ou32_Count: number of data bytes that should be CRC checked \n
   \param    opu8_Data:  data pointer \n
   \param    opu16_Crc:  pointer to CRC value, start value should be 0xFFFF \n

   \return   C_NO_ERR \n

   \created  08.03.2006  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_uti_calc_crc_stw(const uint32 ou32_Count, const uint8* const opu8_Data, uint16* const opu16_Crc);


//-----------------------------------------------------------------------------
/*!
   \brief    calculate 32bit CRC over n 32bit words

             the function use the ethernet polynomial 0x104C11DB7  \n
             and TriCore memchecker hardware \n

   \ingroup  x_uti

   \note     the TriCore algorithm is not compatible to standard CRC generation \n

   \param    ou32_Count: number of 32bit data words that should be CRC checked \n
   \param    opu32_Data: data pointer (start address) \n
   \param    opu32_Crc:  pointer to CRC value, start value should be 0xFFFFFFFF \n

   \return   C_NO_ERR \n
             C_RANGE  (pu32_Data is not a 32bit word address) \n

   \created  13.04.2005  Herb

*/
//-----------------------------------------------------------------------------
sint16 x_uti_calc_crc_tricore(const uint32 ou32_Count, const uint32* const opu32_Data, uint32* const opu32_Crc);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_UTI_H */
