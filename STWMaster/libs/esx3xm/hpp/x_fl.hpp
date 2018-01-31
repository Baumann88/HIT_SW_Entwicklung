//-----------------------------------------------------------------------------
/*!
   \file        x_fl.hpp
   \brief       CPP namespace extention for x_fl.h

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

#ifndef __X_FL_HPP
#define __X_FL_HPP


/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint32 u32_StartAddress;
   stw_types::uint32 u32_EndAddress;
} T_x_fl_Area;

typedef struct
{
   stw_types::uint8    au8_Signature[8];
} T_x_fl_Signature;

typedef struct
{
   stw_types::charn             acn_Magic[11];
   stw_types::uint8             u8_StructVersion;
   stw_types::uint16            u16_StructSize;
   stw_types::uint8             au8_Reserved1[2];
   stw_types::uint16            u16_SignatureAlgorithm;
   stw_types::uint8             u8_Reserved2;
   stw_types::uint8             u8_NumOfAreas;
   T_x_fl_Area       at_Areas[2];
   T_x_fl_Signature  at_Signatures[2];
} T_x_fl_main_signature_block;

/* -- Global Variables ---------------------------------------------------- */
extern T_x_fl_main_signature_block const gt_ApplicationSignatureBlock;

/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x_fl_get_version(stw_types::uint16 * const opu16_Version);

stw_types::sint16 x_fl_get_num_interfaces(stw_types::uint16 * const opu16_NumInterfaces);
stw_types::sint16 x_fl_get_interface_parameters(const stw_types::uint16 ou16_InterfaceNumber,
                                                T_x_fl_interface_parameters * const opt_Parameters);
stw_types::sint16 x_fl_set_interface_parameters(const stw_types::uint16 ou16_InterfaceNumber,
                                                const T_x_fl_interface_parameters * const opt_Parameters);

//checksum functions
stw_types::sint16 x_fl_get_num_checksum_blocks(stw_types::uint16 * const opu16_NumBlocks);

//checksum functions for flashloader protocol versions >= V3.00r0 (block based checksums)
stw_types::sint16 x_fl_get_checksum_block_addresses(const stw_types::uint16 ou16_BlockNumber,
                                                    T_x_fl_checksum_block_addresses * const opt_ChecksumBlockAddresses);
stw_types::sint16 x_fl_set_checksum_block_addresses(const stw_types::uint16 ou16_BlockNumber,
                                                    const T_x_fl_checksum_block_addresses * const opt_ChecksumBlockAddresses);

//checksum comparison activation functions (needs flashloader version >= 2_02r0!)
stw_types::sint16 x_fl_get_checksum_block_check(const stw_types::uint16 ou16_BlockNumber, stw_types::uint8 * const opu8_OnOff);
stw_types::sint16 x_fl_set_checksum_block_check(const stw_types::uint16 ou16_BlockNumber, const stw_types::uint8 ou8_OnOff);

//fingerprint access function
stw_types::sint16 x_fl_get_finger_print(T_x_fl_finger_print * const opt_FingerPrint);

//flash signature block checks
stw_types::sint16 x_fl_get_content_changed_flag(stw_types::uint8 * const opu8_ChangeState);
stw_types::sint16 x_fl_reset_content_changed_flag(void);
stw_types::sint16 x_fl_perform_signature_block_check(const void * const opv_SignatureBlock);


#endif  // __X_FL_HPP
