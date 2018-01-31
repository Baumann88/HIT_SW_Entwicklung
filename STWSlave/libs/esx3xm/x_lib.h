//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_lib.h
   \brief      library and application version information


   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     04.04.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_LIB_H
#define _X_LIB_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

#define X_LIB_VERSION_STRING     "ESX3XM LIB"   // short description (max. 15 chars)
// note: do not parenthesize this values because of the stringify operator
#define X_LIB_VERSION_MAJOR      2              // library version
#define X_LIB_VERSION_MINOR      3              // library minor version
#define X_LIB_VERSION_RELEASE    1              // library release

// memory attributes for library and application information data
// const data marked with this memory attributes are stored in special
// memory areas, defined by the linker script:
// define memory attribute for BIOS library information
#define X_LIB_MEM_BIOS_INFO      __attribute__ ((section (".extlibinfo")))
// define memory attribute for driver and application library information
#define X_LIB_MEM_DRIVER_INFO    __attribute__ ((section (".extlibinfo")))
// define memory attribute for application information data
#define X_LIB_MEM_APPL_INFO      __attribute__ ((section (".application_info")))

// magic codes to distinguish the type of information stored in T_x_lib_info:
// tag to identify STW BIOS libraries, shall not be used by application
#define  X_LIB_INFO_BIOS_MAGIC               "Lx_?z21"
// tag to identify driver and application libraries (e.g. CAN-Protocols)
#define  X_LIB_INFO_DRIVER_MAGIC             "Lx_?z22"
// tag to identify application information
#define  X_LIB_INFO_APPL_MAGIC               "Lx_?z2."

#define X_LIB_INFO_STRUCT_VERSION            (0x01u)
#define X_LIB_INFO_CONTAINS_DEVICE_ID        (0x01u)
#define X_LIB_INFO_CONTAINS_DATE_TIME        (0x02u)
#define X_LIB_INFO_CONTAINS_PROJECT_NAME     (0x04u)
#define X_LIB_INFO_CONTAINS_PROJECT_VERSION  (0x08u)
#define X_LIB_INFO_CONTAINS_ADDITIONAL_INFO  (0x10u)
#define X_LIB_INFO_CONTAINS_ADDITIONAL_MAX   (0xFFu)
#define X_LIB_INFO_DEVICE_ID                 "Y_ESX3XM"     // library target device id


// define GNU patchlevel if not available (used by library information)
#ifndef __GNUC_PATCHLEVEL__
// note: do not parenthesize this value because of the stringify operator
#define __GNUC_PATCHLEVEL__      0
#endif


/***************************************************************************
 * example for application information tag:
 * (to be defined inside a application)
 ***************************************************************************/
/*

#define PROJECT_NAME       "DEMO_APPL"    // max. 14 chars
#define VERSION_MAJOR      1              // example for version information defines
#define VERSION_MINOR      0
#define VERSION_RELEASE    0

X_LIB_MEM_APPL_INFO const T_x_lib_info gt_x_application_info =
{
   X_LIB_INFO_APPL_MAGIC,           // magic code identifies data with application info
   X_LIB_INFO_STRUCT_VERSION,       // information struct version
                                    // information content map
   X_LIB_INFO_CONTAINS_DEVICE_ID | \
   X_LIB_INFO_CONTAINS_DATE_TIME | \
   X_LIB_INFO_CONTAINS_PROJECT_NAME | \
   X_LIB_INFO_CONTAINS_PROJECT_VERSION | \
   X_LIB_INFO_CONTAINS_ADDITIONAL_INFO,

   X_LIB_INFO_DEVICE_ID,            // device ID
   __DATE__,                        // compile date
   __TIME__,                        // compile time
   PROJECT_NAME,                    // project name (max. 14 chars)
                                    // project version
   XSTR(VERSION_MAJOR) "_" XSTR(VERSION_MINOR) "r" XSTR(VERSION_RELEASE),

   X_LIB_INFO_CONTAINS_ADDITIONAL_MAX,    // length of additional information
   "COMPILER_ID: GCC V"XSTR(__GNUC__)"."XSTR(__GNUC_MINOR__)"."XSTR(__GNUC_PATCHLEVEL__)"; " \
   "TARGET_ID: " XSTR(TARGET_ID) "; TARGET_VERSION: " XSTR(TARGET_VERSION)
};

*/

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_lib.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */
typedef struct
{
   charn acn_Magic[7];              // = "Lx_?z2." or "Lx_?z3." probability for accidental match: 10^-17
   uint8 u8_StructVersion;          // =1
   uint8 u8_ContentMap;             //Bit0 = contains device ID; Bit1 = contains date+time;
                                    //Bit2 = contains project name; Bit3 = Project version
                                    //Bit4 = contains additional information
                                    // note: must be 0x1F for this struct definition
   charn acn_DeviceID[16];          //ASCII device ID e.g. "Y_ESX3XM" (optional; recommended)
   charn acn_Date[11];              //date of compilation(format: __DATE__ ANSI C macro) (optional)
   charn acn_Time[8];               //time of compilation (format: __TIME__ ANSI C macro) (optional)
   charn acn_ProjectName[15];       //short description of project (optional)
   charn acn_ProjectVersion[10];    //version number of project; (optional)
   uint8 u8_LenAdditionalInfo;
   charn acn_AdditionalInfo[X_LIB_INFO_CONTAINS_ADDITIONAL_MAX]; //length must match u8_LenAdditionalInfo; ASCII only
} T_x_lib_info;


typedef struct
{
   charn  acn_Name[16];             // library name or short description
   charn  acn_VersionString[16];    // version string (format: 1_23r4)
   uint8  u8_MajorVersion;          // major version number
   uint8  u8_MinorVersion;          // minor version number
   uint16 u16_Release;              // release number
   uint16 u16_TargetId;             // target hardware identification
   uint16 u16_TargetVersion;        // target hardware version
   uint16 u16_CompilerMajorVersion; // compiler major version number
   uint16 u16_CompilerMinorVersion; // compiler minor version number
   uint32 u32_CompilerRelease;      // compiler release number
   charn  acn_Date[11];             // date of compilation (format: __DATE__ ANSI C macro)
   charn  acn_Time[8];              // time of compilation (format: __TIME__ ANSI C macro)
} T_x_lib_version;


/* -- Global Variables ---------------------------------------------------- */


/* -- Function Prototypes ------------------------------------------------- */

sint16 x_lib_get_version(T_x_lib_version* const opt_Version);


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif
#endif  /* _X_LIB_H */
