//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 SPN processing module

   Define the SPN decoding and encoding functions

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     13.04.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   13.04.2010         STW/M.Greiner    file created
   \endhistory
*/
//------------------------------------------------------------------------------


#ifndef _J1939_SPN_H_                      // Avoid multiple/recursive inclusion
#define _J1939_SPN_H_


// -- Includes ----------------------------------------------------------------
#include "stwtypes.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_SPN_SCALED         0xFFFEU

#define J1939_NOT_AVAILABLE      0xFFFFFFFFU  // SPN not available in PG (-1)
#define J1939_ERROR_VALUE        0xFFFFFFFEU  // SPN received value invalid range (-2)
#define J1939_SCALED_VALUE_DEF   0            // out of range value for scaled values

// bitfield size mask
#define SPN_FIELD_MASK_1_BIT     0x0001U
#define SPN_FIELD_MASK_2_BIT     0x0003U
#define SPN_FIELD_MASK_3_BIT     0x0007U
#define SPN_FIELD_MASK_4_BIT     0x000FU
#define SPN_FIELD_MASK_5_BIT     0x001FU
#define SPN_FIELD_MASK_6_BIT     0x003FU
#define SPN_FIELD_MASK_7_BIT     0x007FU
#define SPN_FIELD_MASK_8_BIT     0x00FFU
#define SPN_FIELD_MASK_9_BIT     0x01FFU
#define SPN_FIELD_MASK_10_BIT    0x03FFU
#define SPN_FIELD_MASK_11_BIT    0x07FFU
#define SPN_FIELD_MASK_12_BIT    0x0FFFU
#define SPN_FIELD_MASK_13_BIT    0x1FFFU
#define SPN_FIELD_MASK_14_BIT    0x3FFFU
#define SPN_FIELD_MASK_15_BIT    0x7FFFU
#define SPN_FIELD_MASK_16_BIT    0xFFFFU

#define SPN_SCALING_FACTOR_1     0x0000U
#define SPN_SCALING_FACTOR_2     0x0001U
#define SPN_SCALING_FACTOR_4     0x0002U
#define SPN_SCALING_FACTOR_8     0x0003U
#define SPN_SCALING_FACTOR_16    0x0004U
#define SPN_SCALING_FACTOR_32    0x0005U
#define SPN_SCALING_FACTOR_64    0x0006U
#define SPN_SCALING_FACTOR_128   0x0007U
#define SPN_SCALING_FACTOR_256   0x0008U
#define SPN_SCALING_FACTOR_512   0x0009U
#define SPN_SCALING_FACTOR_1024  0x000AU
#define SPN_SCALING_FACTOR_2048  0x000BU


// -- Types -------------------------------------------------------------------
typedef void (*PR_J1939_SPN_HandleRx)(const uint8* const opu8_Data, const void* const opt_Parameter,
                                      void * const opv_Result);
typedef void (*PR_J1939_SPN_HandleTx)(uint8* const opu8_Data, const void* const opt_Parameter,
                                      const void* const opv_Value);

typedef struct
{
   uint16                u16_DataOffsetInStruct; // position of the Src/Dest variable in PG user structure
   const void*           pv_Configuration;       // pointer to structure which contain the SPN description
   PR_J1939_SPN_HandleRx pr_GetData;             // pointer to decoding function (needed on receiving PGs)
   PR_J1939_SPN_HandleTx pr_SetData;             // pointer to encoding function (needed on sending PGs)
}
T_J1939_SPN_description;                         // informations which descript a specific SPN


typedef struct
{
   uint8  u8_BitFieldMask;                       // the bitfield mask
   uint8  u8_BitIndex;                           // index of the first field bit [0..7]
   uint16 u16_ByteIndex;                         // index of the byte in data buffer [0 .. ]
   // valid range definition
   uint8  u8_HighValue;                          // the highest valid value
}
T_J1939_SPN_u8_bit_field;                        // bit field with length 1..8

typedef struct
{
   uint16 u16_ByteIndex;                         // index of the first byte in data buffer [0 .. ]
   // valid range definition
   uint32 u32_HighValue;                         // the highest valid value
}
T_J1939_SPN_unscaled;

typedef struct
{
   uint16 u16_ByteIndex;                         // index of the byte in data buffer [0 .. ]
   uint16 u16_Factor;                            // scaling multiplication/division factor [SPN_SCALING_FACTOR_X]
   sint16 s16_Offset;                            // scaling offset
   // valid range definition
   uint16 u16_HighValue;                         // the highest valid value (before execute scaling)
}
T_J1939_SPN_scaled;                              // scaling with factor 2^N

typedef struct
{
   uint16 u16_ByteIndex;                         // index of the byte in data buffer [0 .. ]
   uint16 u16_Factor1;                           // scaling multiplication/division factor    [SPN_SCALING_FACTOR_X]
   uint16 u16_Factor2;                           // additional multiplication/division factor [SPN_SCALING_FACTOR_X]
   sint16 s16_Offset;                            // scaling offset
   // valid range definition
   uint16 u16_HighValue;                         // the highest valid value (before execute scaling)
}
T_J1939_SPN_scaled_2_factors;                    // scaling with factor M/(2^N)


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------
extern void J1939_spn_get_bitfield(const uint8 * const opu8_Data,
                                   const T_J1939_SPN_u8_bit_field * const opt_Parameter,
                                   void * const opv_Result);
extern void J1939_spn_get_u8_unscaled(const uint8 * const opu8_Data,
                                      const T_J1939_SPN_unscaled * const opt_Parameter,
                                      void * const opv_Result);
extern void J1939_spn_get_u16_unscaled(const uint8 * const opu8_Data,
                                       const T_J1939_SPN_unscaled * const opt_Parameter,
                                       void * const opv_Result);
extern void J1939_spn_get_u32_unscaled(const uint8 * const opu8_Data,
                                       const T_J1939_SPN_unscaled * const opt_Parameter,
                                       void * const opv_Result);
extern void J1939_spn_get_u16_u16_scaled_div(const uint8 * const opu8_Data,
                                             const T_J1939_SPN_scaled * const opt_Parameter,
                                             void * const opv_Result);
extern void J1939_spn_get_s8_u8_scaled_offset(const uint8 * const opu8_Data,
                                              const T_J1939_SPN_scaled * const opt_Parameter,
                                              void * const opv_Result);
extern void J1939_spn_get_s16_u8_scaled_offset(const uint8 * const opu8_Data,
                                               const T_J1939_SPN_scaled * const opt_Parameter,
                                               void * const opv_Result);
extern void J1939_spn_get_s16_u8_scaled_r_mult_offset(const uint8 * const opu8_Data,
                                                      const T_J1939_SPN_scaled * const opt_Parameter,
                                                      void * const opv_Result);
extern void J1939_spn_get_u16_u8_scaled_mult(const uint8 * const opu8_Data,
                                             const T_J1939_SPN_scaled * const opt_Parameter,
                                             void * const opv_Result);
extern void J1939_spn_get_u16_u8_scaled_r_mult(const uint8 * const opu8_Data,
                                               const T_J1939_SPN_scaled * const opt_Parameter,
                                               void * const opv_Result);
extern void J1939_spn_get_s16_u16_scaled_div_offset(const uint8 * const opu8_Data,
                                                    const T_J1939_SPN_scaled_2_factors * const opt_Parameter,
                                                    void * const opv_Result);


extern void J1939_spn_set_bitfield(uint8 * const opu8_Data,
                                   const T_J1939_SPN_u8_bit_field * const opt_Parameter,
                                   const void * const opv_Value);
extern void J1939_spn_set_u8_unscaled(uint8 * const opu8_Data,
                                      const T_J1939_SPN_unscaled * const opt_Parameter,
                                      const void * const opv_Value);
extern void J1939_spn_set_u16_unscaled(uint8 * const opu8_Data,
                                       const T_J1939_SPN_unscaled * const opt_Parameter,
                                       const void * const opv_Value);
extern void J1939_spn_set_u32_unscaled(uint8 * const opu8_Data,
                                       const T_J1939_SPN_unscaled * const opt_Parameter,
                                       const void * const opv_Value);
extern void J1939_spn_set_u16_u16_scaled_div(uint8 * const opu8_Data,
                                             const T_J1939_SPN_scaled * const opt_Parameter,
                                             const void * const opv_Value);
extern void J1939_spn_set_s8_u8_scaled_offset(uint8 * const opu8_Data,
                                              const T_J1939_SPN_scaled * const opt_Parameter,
                                              const void * const opv_Value);
extern void J1939_spn_set_s16_u8_scaled_offset(uint8 * const opu8_Data,
                                               const T_J1939_SPN_scaled * const opt_Parameter,
                                               const void * const opv_Value);
extern void J1939_spn_set_s16_u8_scaled_r_mult_offset(uint8 * const opu8_Data,
                                                      const T_J1939_SPN_scaled * const opt_Parameter,
                                                      const void * const opv_Value);
extern void J1939_spn_set_u16_u8_scaled_mult(uint8 * const opu8_Data,
                                             const T_J1939_SPN_scaled * const opt_Parameter,
                                             const void * const opv_Value);
extern void J1939_spn_set_u16_u8_scaled_r_mult(uint8 * const opu8_Data,
                                               const T_J1939_SPN_scaled * const opt_Parameter,
                                               const void * const opv_Value);
extern void J1939_spn_set_s16_u16_scaled_div_offset(uint8 * const opu8_Data,
                                                    const T_J1939_SPN_scaled_2_factors * const opt_Parameter,
                                                    const void * const opv_Value);


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
