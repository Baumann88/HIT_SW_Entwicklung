//-----------------------------------------------------------------------------
/*!
   \file        x_lib.hpp
   \brief       CPP namespace extention for x_lib.h

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

#ifndef __X_LIB_HPP
#define __X_LIB_HPP



/* -- Types --------------------------------------------------------------- */
typedef struct
{
   stw_types::charn acn_Magic[7];              // = "Lx_?z2." or "Lx_?z3." probability for accidental match: 10^-17
   stw_types::uint8 u8_StructVersion;          // =1
   stw_types::uint8 u8_ContentMap;             //Bit0 = contains device ID; Bit1 = contains date+time;
   //Bit2 = contains project name; Bit3 = Project version
   //Bit4 = contains additional information
   // note: must be 0x1F for this struct definition
   stw_types::charn acn_DeviceID[16];          //ASCII device ID e.g. "Y_ESX3XM" (optional; recommended)
   stw_types::charn acn_Date[11];              //date of compilation(format: __DATE__ ANSI C macro) (optional)
   stw_types::charn acn_Time[8];               //time of compilation (format: __TIME__ ANSI C macro) (optional)
   stw_types::charn acn_ProjectName[15];       //short description of project (optional)
   stw_types::charn acn_ProjectVersion[10];    //version number of project; (optional)
   stw_types::uint8 u8_LenAdditionalInfo;
   stw_types::charn acn_AdditionalInfo[X_LIB_INFO_CONTAINS_ADDITIONAL_MAX]; //length must match u8_LenAdditionalInfo; ASCII only
} T_x_lib_info;


typedef struct
{
   stw_types::charn  acn_Name[16];             // library name or short description
   stw_types::charn  acn_VersionString[16];    // version string (format: 1_23r4)
   stw_types::uint8  u8_MajorVersion;          // major version number
   stw_types::uint8  u8_MinorVersion;          // minor version number
   stw_types::uint16 u16_Release;              // release number
   stw_types::uint16 u16_TargetId;             // target hardware identification
   stw_types::uint16 u16_TargetVersion;        // target hardware version
   stw_types::uint16 u16_CompilerMajorVersion; // compiler major version number
   stw_types::uint16 u16_CompilerMinorVersion; // compiler minor version number
   stw_types::uint32 u32_CompilerRelease;      // compiler release number
   stw_types::charn  acn_Date[11];             // date of compilation (format: __DATE__ ANSI C macro)
   stw_types::charn  acn_Time[8];              // time of compilation (format: __TIME__ ANSI C macro)
} T_x_lib_version;


/* -- Global Variables ---------------------------------------------------- */


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_lib_get_version(T_x_lib_version* const opt_Version);


#endif  // __X_LIB_HPP
