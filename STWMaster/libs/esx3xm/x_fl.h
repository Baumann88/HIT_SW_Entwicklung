//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_fl.h
   \brief      flashloader functions


   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     28.08.2008  CB
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_FL_H
#define _X_FL_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_fl_types.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */
#define X_FL_IF_01   (0U)
#define X_FL_IF_02   (1U)
#define X_FL_IF_03   (2U)
#define X_FL_IF_04   (3U)
#define X_FL_IF_05   (4U)


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_fl.hpp"
}
#else

/* -- Types --------------------------------------------------------------- */

typedef struct
{
   uint32 u32_StartAddress;
   uint32 u32_EndAddress;
} T_x_fl_Area;

typedef struct
{
   uint8    au8_Signature[8];
} T_x_fl_Signature;

typedef struct
{
   charn             acn_Magic[11];
   uint8             u8_StructVersion;
   uint16            u16_StructSize;
   uint8             au8_Reserved1[2];
   uint16            u16_SignatureAlgorithm;
   uint8             u8_Reserved2;
   uint8             u8_NumOfAreas;
   T_x_fl_Area       at_Areas[2];
   T_x_fl_Signature  at_Signatures[2];
} T_x_fl_main_signature_block;

/* -- Global Variables ---------------------------------------------------- */
extern T_x_fl_main_signature_block const gt_ApplicationSignatureBlock;

/* -- Function Prototypes ------------------------------------------------- */
sint16 x_fl_get_version(uint16 * const opu16_Version);

sint16 x_fl_get_num_interfaces(uint16 * const opu16_NumInterfaces);
sint16 x_fl_get_interface_parameters(const uint16 ou16_InterfaceNumber,
                                     T_x_fl_interface_parameters * const opt_Parameters);
sint16 x_fl_set_interface_parameters(const uint16 ou16_InterfaceNumber,
                                     const T_x_fl_interface_parameters * const opt_Parameters);

//checksum functions
sint16 x_fl_get_num_checksum_blocks(uint16 * const opu16_NumBlocks);

//checksum functions for flashloader protocol versions >= V3.00r0 (block based checksums)
sint16 x_fl_get_checksum_block_addresses(const uint16 ou16_BlockNumber,
                                         T_x_fl_checksum_block_addresses * const opt_ChecksumBlockAddresses);
sint16 x_fl_set_checksum_block_addresses(const uint16 ou16_BlockNumber,
                                         const T_x_fl_checksum_block_addresses * const opt_ChecksumBlockAddresses);

//checksum comparison activation functions (needs flashloader version >= 2_02r0!)
sint16 x_fl_get_checksum_block_check(const uint16 ou16_BlockNumber, uint8 * const opu8_OnOff);
sint16 x_fl_set_checksum_block_check(const uint16 ou16_BlockNumber, const uint8 ou8_OnOff);

//fingerprint access function
sint16 x_fl_get_finger_print(T_x_fl_finger_print * const opt_FingerPrint);

//flash signature block checks
sint16 x_fl_get_content_changed_flag(uint8 * const opu8_ChangeState);
sint16 x_fl_reset_content_changed_flag(void);
sint16 x_fl_perform_signature_block_check(const void * const opv_SignatureBlock);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_FL_H */
