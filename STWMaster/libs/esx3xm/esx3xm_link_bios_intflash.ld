/*
 * GNU GCC linker script for ESX-3XM executables
 *
 * Christoph Baldauf, STW                         15.06.2012
 *
 *
 * external RAM memory 0xA4000000..0xA43FFFFF (4MB)
 *
 * usage of external RAM memory (see MEMORY {...} statement):
 *
 * ext_res:  0xA4000000..0xA400FFFF, 64KB RAM reserved for debugger
 * ext_dram: 0xA4010000..0xA43EFFFF, ~4MB (-2x 64KB) data memory
 * ext_cram: 0xA43F0000..0xA43FFFFF, 64KB RAM for code running in RAM (Flash functions etc.)
 *
 * internal static RAM memory 0xC0000000..0xC000FFFF (64KB)
 *
 * user & interrupt stack located inside internal data RAM (int_dram)
 *
 */


OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_start)


/* define available memory regions: */

MEMORY
{
  int_crom  (arx!p):    org = 0xA0020000, len = 0x01E0000     /* TC1796 on chip flash ROM (no cache)                      */
  int_crom_max     :    org = 0xA0200000, len = 0             /* TC1796 on chip flash ROM (no cache) end address          */
  ext_crom  (arx!p):    org = 0xA1020000, len = 0x03E0000     /* external ROM (no cache)                                  */
  ext_crom_max     :    org = 0xA1400000, len = 0             /* external ROM (no cache) end address                      */

  ext_ram_start    :    org = 0xA4000000, len = 0             /* external RAM start address (used by RAM tests!)          */
  ext_res   (!arxp):    org = 0xA4000000, len = 0x0010000     /* reserved external RAM (used by Lauterbach Emulator)      */
  ext_res_max      :    org = 0xA4010000, len = 0             /* reserved external RAM end address                        */
  ext_dram  (aw!xp):    org = 0xA4010000, len = 0x03E0000     /* external data RAM                                        */
  ext_dram_max     :    org = 0xA43F0000, len = 0             /* external data RAM end address                            */
  ext_cram  (arx!p):    org = 0xA43F0000, len = 0x0010000     /* external code RAM (for flash programming functions etc.) */
  ext_cram_max     :    org = 0xA4400000, len = 0             /* external code RAM end address                            */

  int_drom1 (ar!xp):    org = 0xAFE00000, len = 0x0010000     /* TC1796 on chip data flash bank1 (no cache)               */
  int_drom1_max    :    org = 0xAFE10000, len = 0             /* TC1796 on chip data flash bank1 end address              */
  int_drom2 (ar!xp):    org = 0xAFE10000, len = 0x0010000     /* TC1796 on chip data flash bank2 (no cache)               */
  int_drom2_max    :    org = 0xAFE20000, len = 0             /* TC1796 on chip data flash bank2 end address              */

  int_sram  (aw!xp):    org = 0xC0000000, len = 0x0010000     /* TC1796 internal data RAM                                 */
  int_sram_max     :    org = 0xC0010000, len = 0             /* TC1796 internal data RAM end address                     */
  int_sbram (aw!xp):    org = 0xC03FC000, len = 0x0004000     /* TC1796 internal stand by data RAM                        */
  int_sbram_max    :    org = 0xC0400000, len = 0             /* TC1796 internal stand by data RAM end address            */

  int_dram  (aw!xp):    org = 0xD0000000, len = 0x000E000     /* TC1796 internal fast data RAM                            */
  int_dram_max     :    org = 0xD000E000, len = 0             /* TC1796 internal fast data RAM end address                */
  int_dpram (aw!xp):    org = 0xD000E000, len = 0x0002000     /* TC1796 internal dual ported data RAM                     */
  int_dpram_max    :    org = 0xD0010000, len = 0             /* TC1796 internal dual ported data RAM end address         */

  int_spram_start  :    org = 0xD4000000, len = 0             /* TC1796 code scratchpad RAM start address                 */
  int_ivram (arx!p):    org = 0xD4000000, len = 0x2000        /* scratchpad RAM interrupt vector table                    */
  int_tvram (arx!p):    org = 0xD4002000, len = 0x0100        /* scratchpad RAM trap vector table                         */
  int_fcram (arx!p):    org = 0xD4002200, len = 0x9E00        /* scratchpad RAM for fast code (no wait states)            */
  int_spram_max    :    org = 0xD400C000, len = 0             /* scratchpad RAM end address                               */

  pcp_data  (awp!x):    org = 0xF0050000, len = 16K           /* TC1796 PCP data memory                                   */
  pcp_data_max     :    org = 0xF0054000, len = 0             /* TC1796 PCP data memory end address                       */
  pcp_text  (arxp) :    org = 0xF0060000, len = 32K           /* TC1796 PCP code memory                                   */
  pcp_text_max     :    org = 0xF0068000, len = 0             /* TC1796 PCP code memory end address                       */
}



SECTIONS
{
  /* Beginning of the memory areas (dummy sections) */
  .int_crom_min  (NOLOAD): { MEM_INT_CROM_START   = ABSOLUTE(.); } > int_crom        /* define int. ROM start address                            */
  .ext_crom_min  (NOLOAD): { MEM_EXT_CROM_START   = ABSOLUTE(.); } > ext_crom        /* define ext. ROM start address                            */
  .ext_ram_min   (NOLOAD): { MEM_EXT_RAM_START    = ABSOLUTE(.); } > ext_ram_start   /* external RAM start address (used by RAM tests!)          */
  .ext_res_min   (NOLOAD): { MEM_EXT_RES_START    = ABSOLUTE(.); } > ext_res         /* reserved external RAM end address                        */
  .ext_dram_min  (NOLOAD): { MEM_EXT_DRAM_START   = ABSOLUTE(.); } > ext_dram        /* external data RAM end address                            */
  .ext_cram_min  (NOLOAD): { MEM_EXT_CRAM_START   = ABSOLUTE(.); } > ext_cram        /* external code RAM end address                            */
  .int_drom1_min (NOLOAD): { MEM_INT_DROM1_START  = ABSOLUTE(.); } > int_drom1       /* TC1796 internal data rom 1 start address                 */
  .int_drom2_min (NOLOAD): { MEM_INT_DROM2_START  = ABSOLUTE(.); } > int_drom2       /* TC1796 internal data rom 2 start address                 */
  .int_sram_min  (NOLOAD): { MEM_INT_SRAM_START   = ABSOLUTE(.); } > int_sram        /* TC1796 internal data RAM start address                   */
  .int_sbram_min (NOLOAD): { MEM_INT_SBRAM_START  = ABSOLUTE(.); } > int_sbram       /* TC1796 internal stand by data RAM end address            */
  .int_dram_min  (NOLOAD): { MEM_INT_DRAM_START   = ABSOLUTE(.); } > int_dram        /* TC1796 internal fast data RAM end address                */
  .int_dpram_min (NOLOAD): { MEM_INT_DPRAM_START  = ABSOLUTE(.); } > int_dpram       /* TC1796 internal dual ported data RAM end address         */
  .int_spram_min (NOLOAD): { MEM_INT_SPRAM_START  = ABSOLUTE(.); } > int_spram_start /* TC1796 internal scratchpad RAM end address               */
  .pcp_data_min  (NOLOAD): { MEM_PCP_DATA_START   = ABSOLUTE(.); } > pcp_data        /* TC1796 internal PCP data memory end address              */
  .pcp_text_min  (NOLOAD): { MEM_PCP_TEXT_START   = ABSOLUTE(.); } > pcp_text        /* TC1796 internal PCP code memory end address              */

  /* End of the memory areas (dummy sections) */
  .int_crom_max  (NOLOAD): { MEM_INT_CROM_END   = ABSOLUTE(.); } > int_crom_max      /* define int. ROM end address                              */
  .ext_crom_max  (NOLOAD): { MEM_EXT_CROM_END   = ABSOLUTE(.); } > ext_crom_max      /* define ext. ROM end address                              */
  .ext_res_max   (NOLOAD): { MEM_EXT_RES_END    = ABSOLUTE(.); } > ext_res_max       /* reserved external RAM end address                        */
  .ext_dram_max  (NOLOAD): { MEM_EXT_DRAM_END   = ABSOLUTE(.); } > ext_dram_max      /* external data RAM end address                            */
  .ext_cram_max  (NOLOAD): { MEM_EXT_CRAM_END   = ABSOLUTE(.); } > ext_cram_max      /* external code RAM end address                            */
  .int_drom1_max (NOLOAD): { MEM_INT_DROM1_END  = ABSOLUTE(.); } > int_drom1_max     /* TC1796 internal data rom 1 end address                   */
  .int_drom2_max (NOLOAD): { MEM_INT_DROM2_END  = ABSOLUTE(.); } > int_drom2_max     /* TC1796 internal data rom 2 end address                   */
  .int_sram_max  (NOLOAD): { MEM_INT_SRAM_END   = ABSOLUTE(.); } > int_sram_max      /* TC1796 internal data RAM end address                     */
  .int_sbram_max (NOLOAD): { MEM_INT_SBRAM_END  = ABSOLUTE(.); } > int_sbram_max     /* TC1796 internal stand by data RAM end address            */
  .int_dram_max  (NOLOAD): { MEM_INT_DRAM_END   = ABSOLUTE(.); } > int_dram_max      /* TC1796 internal fast data RAM end address                */
  .int_dpram_max (NOLOAD): { MEM_INT_DPRAM_END  = ABSOLUTE(.); } > int_dpram_max     /* TC1796 internal dual ported data RAM end address         */
  .int_spram_max (NOLOAD): { MEM_INT_SPRAM_END  = ABSOLUTE(.); } > int_spram_max     /* TC1796 internal scratchpad RAM end address               */
  .pcp_data_max  (NOLOAD): { MEM_PCP_DATA_END   = ABSOLUTE(.); } > pcp_data_max      /* TC1796 internal PCP data memory end address              */
  .pcp_text_max  (NOLOAD): { MEM_PCP_TEXT_END   = ABSOLUTE(.); } > pcp_text_max      /* TC1796 internal PCP code memory end address              */
}

__APPLICATION_START = MEM_EXT_CROM_START;                                 /* start from external ROM */

SECTIONS
{
  /*
   * The startup code should be placed where the CPU expects it after a reset.
   */
  .boot __APPLICATION_START :
  {
    KEEP(*(.boot_code))
  } > ext_crom =0

  /*
   * This magic key signals a valid applicaton to the flashloader
   */
   .validprogramkey (__APPLICATION_START + 0x18) :
   {
      LONG(0x900dc0de);
   } > ext_crom =0

  /*
   * allocate the library information data at address offset 0x20
   */
  .libversion (__APPLICATION_START + 0x20) :
  {
    KEEP(*(.libversion))
  } > ext_crom =0

  /*
   * external libinfo data address offset
   */
  .extlibinfo_start (__APPLICATION_START + 0xFC) :
  {
    LONG(__EXTLIBINFO_OFFSET);
  } > ext_crom =0

  /*
   * allocate the default trap vector table code at address offset 0x100 (load address)
   * the run time location is the scratchpad ram memory (int_tvram)
   * the code is loaded by the startup code (see also __copy_table)
   */
  .tvect : AT(__APPLICATION_START + 0x100)
  {
    KEEP(*(.traptab))
  } > int_tvram

  gu32_default_trap_vect = LOADADDR(.tvect);

  /*
   * if application information data available: allocate it at address offset 0x200
   */
  .application_info (__APPLICATION_START + 0x200) :
  {
    KEEP(*(.application_info))
    . = ALIGN(4) ;
  } > ext_crom =0

  /*
   * allocate external library information data
   */
  .extlibinfo :
  {
    . = ALIGN(4) ;
    __EXTLIBINFO_START = ABSOLUTE(.);
    KEEP(*(.extlibinfo))
    . = ALIGN(4) ;
  } > ext_crom =0

  __EXTLIBINFO_OFFSET = (SIZEOF(.extlibinfo) > 0) ? (__EXTLIBINFO_START - __APPLICATION_START) : 0 ;

  /*
   * provide the end address of the used ROM area (1st. unused address)
   * C usage (external definition):
   * extern const uint32 gu32_EndOfUsedRom;
   */
  .romendinfo :
  {
    . = ALIGN(4);
    gu32_EndOfUsedRomInternal = .;      /* provide this symbol for HLL access */
    LONG(MEM_INT_CROM_USED_END);        /* 1st unused internal ROM address */
    gu32_EndOfUsedRom = .;              /* provide this symbol for HLL access */
    LONG(MEM_EXT_CROM_USED_END);        /* 1st unused external ROM address */
  } > ext_crom =0

  /*
   *  This section provides a signature block that can be modified using the STWFlashSignatureGenerator
   *  tool in a post-build step. The linker will insert the start and end addresses of intern and
   *  extern flash used by the application. The "QUAD(0);" entries are placeholder for the signature.
   *  This signature should be checked by the application to assure flash content integrity.
   */
  .block_signature :
  {
    . = ALIGN(8);

    gt_ApplicationSignatureBlock = ABSOLUTE(.);
    LONG(0x6D777A3B);
    LONG(0x55674B32);
    LONG(0x0200215A);
    LONG(0x00000034);
    LONG(0x02000002);
    LONG(MEM_INT_CROM_START);
    LONG(MEM_INT_CROM_USED_END - 1);
    LONG(MEM_EXT_CROM_START);
    LONG(MEM_EXT_CROM_USED_END - 1);
    QUAD(0);
    QUAD(0);
  } > ext_crom


  /*
   * allocate all absolute callable code at the beginning of the intern flash sections
   * (possible address range for absolute callable code: 0xA0000000 -- 0xA00FFFFF)
   */
  .abs_text_i :
  {
    . = ALIGN(4);
    *(.abs.text_i)
    *(.abs.text_i.*)
    . = ALIGN(4);
  } > int_crom =0


  /*
   * allocate all .text ( = executable code) sections into ext. flash memory
   */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text.*)
    /* .gnu.linkonce sections are used by gcc for vague linking   */
    *(.gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf32.em.   */
    *(.gnu.warning)
    . = ALIGN(4);
  } > ext_crom =0


  .stw_bios_text :
  {
    KEEP(*(.startup_code))
    SEC_STW_BIOS_TEXT_START = ABSOLUTE(.);

    /*
     *  Within stw_bios.text section, we define a subsection for safety critical code and export
     *  it's address boundaries for the MPU code protection. This allows an MPU configuration, which
     *  can deny safety critical code access from non-interfering code.
     */
    . = ALIGN(8);
    MPU_EXPORT_SAFETY_CRITICAL_STW_BIOS_CODE_START = ABSOLUTE(.);
    /* Safety zone not required for code protection */
    KEEP(*(*.safety_critical.stw_bios.text*))
    . = ALIGN(8);
    MPU_EXPORT_SAFETY_CRITICAL_STW_BIOS_CODE_END = ABSOLUTE(.);

    /* allocate remaining stw_bios.text sections */
    KEEP(*(*.stw_bios.text*))

    SEC_STW_BIOS_TEXT_END = ABSOLUTE(.);

  } > int_crom =0


  /*
   * allocate non-interfering code (not callable from safety relevant code )
   */
  .ext_noninterfering.text :
  {
    SEC_EXT_NONINTERFERING_CODE_START = ABSOLUTE(.);
    . = ALIGN(8);
    MPU_EXPORT_NONINTERFERING_CODE_START = ABSOLUTE(.);
    KEEP(*(*.ext_noninterfering.text.*))
    KEEP(*(*.ext_noninterfering.text))
    . = ALIGN(8) ;
    MPU_EXPORT_NONINTERFERING_CODE_END = ABSOLUTE(.);
    SEC_EXT_NONINTERFERING_CODE_END = ABSOLUTE(.);
   } > int_crom = 0


  /*
   * allocate all read only data sections
   */
  .rodata :
  {
    . = ALIGN(8);

    *(.rodata)

    /* sort rodata according to their alignement (only needed with -maligned-data-sections compiler switch) */
    *(.rodata.a1)             /* 1-byte alignement                */
    *(.rodata.a2)             /* 2-byte alignement                */
    *(.rodata.a4)             /* 4-byte alignement                */
    *(.rodata.a8)             /* >= 8-byte alignement             */
    *(.rodata.*)

    /* .gnu.linkonce sections are used by gcc for vague linking   */
    *(.gnu.linkonce.r.*)
    *(.rodata1)

  } > ext_crom =0

  .stw_bios_rodata :
  {
    . = ALIGN(8);
    SEC_STW_BIOS_RODATA_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.rodata*))
    SEC_STW_BIOS_RODATA_END = ABSOLUTE(.);
    . = ALIGN(4);
  } > int_crom =0

  /*
   * C++ Constructors and destructors.
   */
  .ctors :
  {
    . = ALIGN(4) ;
    __CTOR_LIST__ = . ;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2);
    KEEP(*(.ctors))
    LONG(0) ;
    __CTOR_END__ = . ;
    . = ALIGN(4) ;
  } > ext_crom =0

  .dtors :
  {
    . = ALIGN(4) ;
    __DTOR_LIST__ = . ;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2);
    KEEP(*(.dtors))
    LONG(0) ;
    __DTOR_END__ = . ;
    . = ALIGN(4) ;
  } > ext_crom =0
}


/* Include all standard sections that don't change with the build targets */
INCLUDE tricore_std_sections.ld
