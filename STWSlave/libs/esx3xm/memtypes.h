//-----------------------------------------------------------------------------
/*!
   \internal
   \file       memtypes.h
   \brief      memory attributes for TriCore controller

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     13.12.2004  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _MEMTYPES_H
#define _MEMTYPES_H


#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */
//PRQA S 2217 ++   // more than 120 characters in line, because of better readability
//PRQA S 3453 ++   // this "function like macro" can't be replaced by a (inline) function!

// alignment directive for variables
#define ALIGNED(align)     __attribute__ ((aligned (align)))      // locate a variable aligned to byte boundary

//PRQA S 3453 --


/***************************************************************************
 *                             WARNING                                     *
 * ------------------------------------------------------------------------*
 *                                                                         *
 *            Undocumented attributes must not be used!                    *
 * They are prone to change and might be not available for your target!   *
 *                                                                         *
 ***************************************************************************/



/***************************************************************************
 * memory defines for usage within the application
 ***************************************************************************/
// define memory attribute for application information data
// const data marked with this memory attribute are stored in a special
// memory area, defined by the linker script
#define X_MEM_ROM_DATA           __attribute__ ((section (".romdata")))
// define memory section attribute to place library information on a fixed address location
#define X_MEM_LIB_VERSION        __attribute__ ((section (".libversion")))
// define memory attribute for library information
#define X_MEM_LIB_INFO           __attribute__ ((section (".extlibinfo")))
#define X_MEM_APPLICATION_INFO   __attribute__ ((section (".application_info")))


// class specifier for special memory areas
#define MEM_PROT           __attribute__ ((section (".protected.data")))                     // locate initialized variable into protected memory (accessible from secure task)
// PRQA S 0286 3  // need the 'at' char for the GCC nobits section flag
#define MEM_PROT_BSS       __attribute__ ((section (".protected.bss,\"aw\",@nobits #")))     // locate zero-initialized variable into protected memory (accessible from secure task)
#define MEM_PROT_NOINIT    __attribute__ ((section (".protected.noinit,\"aw\",@nobits #")))  // locate not initialized variable into protected memory (accessible from secure task)
#define MEM_NOINIT         __attribute__ ((section (".noinit,\"aw\",@nobits #")))            // variable stored in .bss, not initialized
#define MEM_EXTROM         __attribute__ ((section (".rodata_e")))                           // read only data stored in extern flash
#define MEM_INTROM         __attribute__ ((section (".rodata_i")))                           // read only data stored in intern flash


// default compiler sections used for small addressing mode
// default .sdata and .sbss sections are located in unprotected extern RAM;
// section .sdata.rodata is located into output section .sdata2 (MCU internal ROM)
#define MEM_SMALL          __attribute__((section(".sdata")))                       // locate initialized variable into SMALL addressable extern RAM region
#define MEM_SMALL_BSS      __attribute__((section(".sbss")))                        // locate zero-initialized variable into SMALL addressable extern RAM region
#define MEM_SMALL_CONST    const __attribute__((asection(".sdata.rodata","f=as")))  // locate const variable into SMALL addressable ROM region


/***************************************************************************
 * function attributes for usage within the application
 ***************************************************************************/
// define function attribute for long calls (call over 256MB segment borders)
#define LONGCALL        __attribute__((longcall))

// define function attribute to locate function into RAM
// code will be installed on startup automatically into RAM
#define CODERAM         __attribute__((asection(".coderam","a=4","f=x"), longcall, noinline))

// define function attribute to locate function into internal ROM (cpu onchip flash)
#define INTROM          __attribute__((asection(".text_i","a=4","f=x"), longcall, noinline))
// define function attribute to locate function into external ROM
#define EXTROM          __attribute__((asection(".text_e","a=4","f=x"), longcall, noinline))

// define a alias function name, the defined function name will be substituted by func
//PRQA S 0341 1         // GCC supports the stringify operator
#define ALIAS(func)     __attribute__ ((alias (#func)))



/***************************************************************************
 * STW Internal defines that must not be used by the application
 ***************************************************************************/
// class specifier for special memory areas (for STW - BIOS use only)
// Note: the memory specifiers are based on the TC1796 target hardware
//       for the TC1797 CPU MEM_DRAM, MEM_DPRAM, MEM_SBRAM and MEM_SRAM are mapped into LDRAM memory
//       for the TC1798 CPU MEM_DRAM and MEM_DPRAM are mapped into DSPR memory and MEM_SBRAM and MEM_SRAM are mapped into SRAM memory
#define MEM_DRAM           __attribute__ ((section (".dram")))                         // locate variable into fast data RAM section
#define MEM_DRAM_CONST     const __attribute__ ((section (".dram_c")))                 // locate variable into fast data RAM section, marked as const
#define MEM_DPRAM          __attribute__ ((section (".dpram")))                        // locate variable into dual ported RAM section
#define MEM_SBRAM          __attribute__ ((section (".sbram")))                        // locate variable into SBRAM section
#define MEM_SRAM           __attribute__ ((section (".sram")))                         // locate variable into SRAM section
#define MEM_SRAM_CONST     const __attribute__ ((section (".sram_c")))                 // locate variable into SRAM section, marked as const

// default compiler sections used for absolute addressing mode (for STW - BIOS use only)
// default .zdata and .zbss sections are located in STW protected internal SRAM;
#define MEM_ABS         __attribute__ ((asection(".zdata","f=awz")))                   // locate initialized variable with absolute addressing
#define MEM_ABS_BSS     __attribute__((asection(".zbss","f=awz")))                     // locate zero-initialized variable with absolute addressing

// define function attribute to locate function into fast RAM
// code will be installed on startup automatically into fast RAM
#define FASTRAM         __attribute__((asection(".fastram","a=4","f=x"), longcall, noinline))
#define INTROM_ABS      __attribute__((asection(".abs.text_i","a=4","f=x")))           // locate function into absolute addressable memory in TriCore intern flash

#ifdef __cplusplus
} /* end of extern "C" */
#endif


#endif  /* _MEMTYPES_H */
