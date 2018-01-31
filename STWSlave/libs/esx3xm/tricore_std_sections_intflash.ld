/*
 * GNU GCC linker script extension for standard Tricore Projects
 *
 * Christoph Baldauf, STW                         20.03.2013
 *
 * This file defines the standard linker script definitions and sections
 * that will be defined after project specific sections.
 *
 * NOTE:
 * MPU_EXPORT_* symbols are used as address boundaries for the MPU configuration.
 * TriCore 1.6 Core architecture requires an 8 Byte alignment for these
 * address values. Therefore every MPU_EXPORT_ definition should be prepend by an
 * ALIGN(8) instruction. This may sometimes override the section alignment
 * definition, which defines the minimum alignment requirements of the current
 * output section, to a stricter alignment.
 */


/*
 * define hardware stack size
 */
__ISTACK_SIZE = DEFINED (__ISTACK_SIZE) ? __ISTACK_SIZE : 4K;     /* interrupt stack size          */
__USTACK_SIZE = DEFINED (__USTACK_SIZE) ? __USTACK_SIZE : 20K;    /* user stack size               */


/*
 * define minimum CSA area in byte
 */
__CSA_MIN = DEFINED (__CSA_MIN) ? __CSA_MIN : 24K;


/*
 * Define the headroom for the LCX in number of CSAs before __CSA_END
 * any user defined trap handler needs 3 CSAs (without any
 * subroutines inside the user trap handler function!)
 * the worst case condition is to service a synchronous trap that is
 * interrupted by a asynchronous trap
 */
__LCX_HEADROOM = DEFINED (__LCX_HEADROOM) ? __LCX_HEADROOM : 6;


  /*
   * The heap is the memory between __HEAP and __HEAP_END
   * programs can dynamically allocate space in this area using malloc()
   * and various other functions.
   * Below you can define the minimum amount of memory that the heap
   * should provide.
   */
__HEAP_MIN = DEFINED (__HEAP_MIN) ? __HEAP_MIN : 512K;
__HEAP_SYS_INTERN_MIN = DEFINED (__HEAP_SYS_INTERN_MIN) ? __HEAP_SYS_INTERN_MIN : 16K;
__HEAP_SYS_EXTERN_MIN = DEFINED (__HEAP_SYS_EXTERN_MIN) ? __HEAP_SYS_EXTERN_MIN : 80K;
__HEAP_SYS_EXTERN_SIZE = DEFINED (__HEAP_SYS_EXTERN_SIZE) ? __HEAP_SYS_EXTERN_SIZE : __HEAP_SYS_EXTERN_MIN;


/*
 * memory statistics, only for information (see also statistic section)
 */
MEM_INT_CROM_SIZE = MEM_INT_CROM_END - MEM_INT_CROM_START;
MEM_INT_CROM_USED = MEM_INT_CROM_USED_END - MEM_INT_CROM_START;

MEM_EXT_CROM_SIZE = MEM_EXT_CROM_END - MEM_EXT_CROM_START;
MEM_EXT_CROM_USED = MEM_EXT_CROM_USED_END - MEM_EXT_CROM_START;

MEM_EXT_RES_SIZE  = MEM_EXT_RES_END - MEM_EXT_RES_START;

MEM_EXT_DRAM_SIZE = MEM_EXT_DRAM_END - MEM_EXT_DRAM_START;
MEM_EXT_DRAM_USED = MEM_EXT_DRAM_USED_END - MEM_EXT_DRAM_START;

MEM_EXT_CRAM_SIZE = MEM_EXT_CRAM_END - MEM_EXT_CRAM_START;
MEM_EXT_CRAM_USED = MEM_EXT_CRAM_USED_END - MEM_EXT_CRAM_START;

MEM_INT_SRAM_SIZE = MEM_INT_SRAM_END - MEM_INT_SRAM_START;
MEM_INT_SRAM_USED = MEM_INT_SRAM_USED_END - MEM_INT_SRAM_START;

MEM_INT_SBRAM_SIZE = MEM_INT_SBRAM_END - MEM_INT_SBRAM_START;
MEM_INT_SBRAM_USED = MEM_INT_SBRAM_USED_END - MEM_INT_SBRAM_START;

MEM_INT_DRAM_SIZE = MEM_INT_DRAM_END - MEM_INT_DRAM_START;
MEM_INT_DRAM_USED = MEM_INT_DRAM_USED_END - MEM_INT_DRAM_START;

MEM_INT_DPRAM_SIZE = MEM_INT_DPRAM_END - MEM_INT_DPRAM_START;
MEM_INT_DPRAM_USED = MEM_INT_DPRAM_USED_END - MEM_INT_DPRAM_START;

MEM_INT_FCRAM_SIZE = MEM_INT_FCRAM_END - MEM_INT_FCRAM_START;
MEM_INT_FCRAM_USED = MEM_INT_FCRAM_USED_END - MEM_INT_FCRAM_START;

MEM_INT_FCRAM_LOADADDR_START      = MEM_INT_FCRAM_LOADADDR_START;
MEM_INT_FCRAM_LOADADDR_USED_END   = MEM_INT_FCRAM_LOADADDR_START + MEM_INT_FCRAM_USED;

MEM_INT_IVRAM_LOADADDR_START = MEM_INT_IVRAM_LOADADDR_START;


MEM_PCP_DATA_SIZE = MEM_PCP_DATA_END - MEM_PCP_DATA_START;
MEM_PCP_DATA_USED = MEM_PCP_DATA_USED_END - MEM_PCP_DATA_START;

MEM_PCP_TEXT_SIZE = MEM_PCP_TEXT_END - MEM_PCP_TEXT_START;
MEM_PCP_TEXT_USED = MEM_PCP_TEXT_USED_END - MEM_PCP_TEXT_START;


/* statistic data of stack and CSA area */
__ISTACK_BEGIN = __ISTACK_START;             /* interrupt stack begin         */
__ISTACK_END = __ISTACK;                     /* interrupt stack end address   */
__USTACK_BEGIN = __ISTACK;                   /* user stack begin              */
__USTACK_END = __USTACK;                     /* user stack start end address  */
__CSA_END = MEM_INT_DRAM_END;                /* end of CSA area = end of DRAM */
__CSA_SIZE = __CSA_END - __CSA_BEGIN;        /* define CSA size               */


STW_BIOS_TEXT_USED       = SEC_STW_BIOS_TEXT_END - SEC_STW_BIOS_TEXT_START;
STW_BIOS_RODATA_USED     = SEC_STW_BIOS_RODATA_END - SEC_STW_BIOS_RODATA_START;
STW_BIOS_FASTRAM_USED    = SEC_STW_BIOS_FASTRAM_END - SEC_STW_BIOS_FASTRAM_START;
STW_BIOS_CODERAM_USED    = SEC_STW_BIOS_CODERAM_END - SEC_STW_BIOS_CODERAM_START;
STW_BIOS_SRAM_USED       = (SEC_STW_BIOS_SRAM_END - SEC_STW_BIOS_SRAM_START);
STW_BIOS_EXT_DRAM_USED   = (SEC_STW_BIOS_DATA_END - SEC_STW_BIOS_DATA_START) + (SEC_STW_BIOS_BSS_END - SEC_STW_BIOS_BSS_START) + (SEC_STW_BIOS_NOINIT_END - SEC_STW_BIOS_NOINIT_START);
STW_BIOS_INT_DRAM_USED   = SEC_STW_BIOS_DRAM_END - SEC_STW_BIOS_DRAM_START;
STW_BIOS_DPRAM_USED      = SEC_STW_BIOS_DPRAM_END - SEC_STW_BIOS_DPRAM_START;

/*
 * Compatibility defines:
 * These are deprecated and might be removed in the future
 */
gu32_INT_CROM_FIRST_ADDRESS  = MEM_INT_CROM_START;
gu32_EXT_CROM_FIRST_ADDRESS  = MEM_EXT_CROM_START;
gu32_EXT_RAM_FIRST_ADDRESS   = MEM_EXT_RAM_START;
gu32_EXT_RES_FIRST_ADDRESS   = MEM_EXT_RES_START;
gu32_EXT_DRAM_FIRST_ADDRESS  = MEM_EXT_DRAM_START;
gu32_EXT_CRAM_FIRST_ADDRESS  = MEM_EXT_CRAM_START;
gu32_INT_SRAM_FIRST_ADDRESS  = MEM_INT_SRAM_START;
gu32_INT_SBRAM_FIRST_ADDRESS = MEM_INT_SBRAM_START;
gu32_INT_DRAM_FIRST_ADDRESS  = MEM_INT_DRAM_START;
gu32_INT_DPRAM_FIRST_ADDRESS = MEM_INT_DPRAM_START;
gu32_INT_SPRAM_FIRST_ADDRESS = MEM_INT_SPRAM_START;
gu32_PCP_DATA_FIRST_ADDRESS  = MEM_PCP_DATA_START;
gu32_PCP_TEXT_FIRST_ADDRESS  = MEM_PCP_TEXT_START;
gu32_INT_CROM_LAST_ADDRESS   = MEM_INT_CROM_END - 1;
gu32_EXT_CROM_LAST_ADDRESS   = MEM_EXT_CROM_END - 1;
gu32_EXT_RES_LAST_ADDRESS    = MEM_EXT_RES_END - 1;
gu32_EXT_DRAM_LAST_ADDRESS   = MEM_EXT_DRAM_END - 1;
gu32_EXT_CRAM_LAST_ADDRESS   = MEM_EXT_CRAM_END - 1;
gu32_INT_SRAM_LAST_ADDRESS   = MEM_INT_SRAM_END - 1;
gu32_INT_SBRAM_LAST_ADDRESS  = MEM_INT_SBRAM_END - 1;
gu32_INT_DRAM_LAST_ADDRESS   = MEM_INT_DRAM_END - 1;
gu32_INT_DPRAM_LAST_ADDRESS  = MEM_INT_DPRAM_END - 1;
gu32_INT_SPRAM_LAST_ADDRESS  = MEM_INT_SPRAM_END - 1;
gu32_PCP_DATA_LAST_ADDRESS   = MEM_PCP_DATA_END - 1;
gu32_PCP_TEXT_LAST_ADDRESS   = MEM_PCP_TEXT_END - 1;
gu32_DIAG_RAM_BASE = SEC_STW_DIAG_RAM_START;
gu32_DIAG_RAM_END =  SEC_STW_DIAG_RAM_END;


EXT_RES_BASE                 = MEM_EXT_RES_START;


  /* check user / interrupt stack address and size */
  _. = ASSERT ((__ISTACK & 7) == 0 , "ISTACK not doubleword aligned");
  _. = ASSERT ((__USTACK & 7) == 0 , "USTACK not doubleword aligned");

  /* Make sure CSA, stack and heap addresses are properly aligned.  */
  _. = ASSERT ((__CSA_BEGIN & 0x3f) == 0 , "illegal CSA start address");
  _. = ASSERT ((__CSA_SIZE & 0x3f) == 0 , "illegal CSA size");
  _. = ASSERT (__CSA_SIZE >= __CSA_MIN , "not enough memory for CSA");
  _. = ASSERT ((__CSA_SIZE >> 6) > __LCX_HEADROOM , "LCX does not fit in CSA area");
  _. = ASSERT (__LCX_HEADROOM >= 6 , "__LCX_HEADROOM should be >= 6");


  /* Define a default symbol for address 0.  */
  NULL = DEFINED (NULL) ? NULL : 0;

  /* force linking of library version information */
  /* even if not referenced by the application    */
  EXTERN(gt_x_lib_version);


  /*
      Emit special address boundaries for MPU usage
  */
  MPU_EXPORT_DATA_MIN_ADDR = 0x80000000;                         /* first data address is cached read only data from internal flash */
  MPU_EXPORT_DATA_MAX_ADDR = 0xE0000000;                         /* mpu can check addresses up to 0xE0000000 where the periphery address space starts*/

  MPU_EXPORT_CODE_MIN_ADDR = MEM_INT_CROM_START;                 /* code can be executed from the internal flash... */
  MPU_EXPORT_CODE_MAX_ADDR = MEM_INT_SPRAM_END;                  /* up to the scratchpad ram area                   */

  MPU_EXPORT_SRAM_START = MEM_INT_SRAM_START;

  /* make sure, that interrupt and user stack are within MPU - protected area */
  _. = ASSERT (((MPU_EXPORT_DATA_MIN_ADDR <= __ISTACK_START) && (MPU_EXPORT_DATA_MAX_ADDR >= (__ISTACK_START + __ISTACK_SIZE))), "interrupt Stack must be within MPU protected area!");
  _. = ASSERT (((MPU_EXPORT_DATA_MIN_ADDR <= __USTACK_START) && (MPU_EXPORT_DATA_MAX_ADDR >= (__USTACK_START + __USTACK_SIZE))), "user Stack must be within MPU protected area!");


/* Standard read-only Sections for all build targets */

SECTIONS
{
  .init  :
  {
      /* we have to keep all .init/.fini section
         because the linker should not delete this
         sections with --gc-sections
       */
    KEEP( *(SORT(.init*)) )
    KEEP( *(SORT(.fini*)) )
    . = ALIGN(8);
  } > int_crom =0

  /*
   * Create the clear and copy tables that tell the startup code
   * which memory areas to clear and to copy, respectively.
   */
  .clear_sec :
  {
    . = ALIGN(4) ;
    __clear_table = .;
    LONG(0 + ADDR(.bss));     LONG(BSS_CLEAR);
    LONG(0 + ADDR(.sbss4));   LONG(SIZEOF(.sbss4));
    LONG(0 + ADDR(.sbss));    LONG(SIZEOF(.sbss));
    LONG(0 + ADDR(.zbss));    LONG(SIZEOF(.zbss));
    /* include additional clear sections */
    *(.clear_sec)
  } > int_crom =0

  .heap_tab :
  {
    /*
     * Create the default heap memory table:
     * the symbol gu32_MemClassDefaultMax defines the number of default memory class entries
     * MemClass entries are: Heap start address, pointer to free memory (=start address), heap end address+1
     * 1st entry is default heap, used by malloc (stdlib.h)
     * 2nd entry is the SYSTEM HEAP located in the internal SRAM
     * 3rd entry is the SYSTEM HEAP located in the external RAM
     * the table is copied into C variable "gat_MemClass[]" (if defined)
     */
    . = ALIGN(4) ;
    gu32_MemClassDefaultMax = ABSOLUTE(.);
    LONG(3);

    /* Emmit Index Constants to select the correct memclass */
    gu32_MemClassDefault = ABSOLUTE(.);
    LONG(0);
    gu32_MemClassSysIntern = ABSOLUTE(.);
    LONG(1);
    gu32_MemClassSysExtern = ABSOLUTE(.);
    LONG(2);

    __HEAP_TAB_START = ABSOLUTE(.);
    LONG(__HEAP);             LONG(__HEAP);              LONG(__HEAP_END);
    LONG(__HEAP_SYS_INTERN);  LONG(__HEAP_SYS_INTERN);   LONG(__HEAP_SYS_INTERN_END);
    LONG(__HEAP_SYS_EXTERN);  LONG(__HEAP_SYS_EXTERN);   LONG(__HEAP_SYS_EXTERN_END);
    __HEAP_TAB_SIZE = (ABSOLUTE(.) - __HEAP_TAB_START);

    __HEAP_TAB_DEST = DEFINED(gat_MemClass) ? ABSOLUTE(gat_MemClass) : NULL;
    __HEAP_TAB_SIZE = (__HEAP_TAB_DEST == NULL) ? NULL : __HEAP_TAB_SIZE;
  } > int_crom =0

  .copy_sec :
  {
    __copy_table = .;
    LONG(LOADADDR(.data));    LONG(0 + ADDR(.data));      LONG(SIZEOF(.data));
    LONG(LOADADDR(.sdata4));  LONG(0 + ADDR(.sdata4));    LONG(SIZEOF(.sdata4));
    LONG(LOADADDR(.sdata));   LONG(0 + ADDR(.sdata));     LONG(SIZEOF(.sdata));
    LONG(LOADADDR(.zdata));   LONG(0 + ADDR(.zdata));     LONG(SIZEOF(.zdata));
    LONG(LOADADDR(.ivect));   LONG(0 + ADDR(.ivect));     LONG(SIZEOF(.ivect));
    LONG(LOADADDR(.tvect));   LONG(0 + ADDR(.tvect));     LONG(SIZEOF(.tvect));
    LONG(LOADADDR(.fcram));   LONG(0 + ADDR(.fcram));     LONG(SIZEOF(.fcram));
    LONG(LOADADDR(.cram));    LONG(0 + ADDR(.cram));      LONG(SIZEOF(.cram));
    LONG(LOADADDR(.pcptext)); LONG(0 + ADDR(.pcptext));   LONG(SIZEOF(.pcptext));
    LONG(LOADADDR(.pcpdata)); LONG(0 + ADDR(.pcpdata));   LONG(SIZEOF(.pcpdata));
    LONG(LOADADDR(.sram));    LONG(0 + ADDR(.sram));      LONG(SIZEOF(.sram));
    LONG(LOADADDR(.sbram));   LONG(0 + ADDR(.sbram));     LONG(SIZEOF(.sbram));
    LONG(LOADADDR(.dram));    LONG(0 + ADDR(.dram));      LONG(SIZEOF(.dram));
    LONG(LOADADDR(.dpram));   LONG(0 + ADDR(.dpram));     LONG(SIZEOF(.dpram));
    LONG(__HEAP_TAB_START);   LONG(__HEAP_TAB_DEST);      LONG(__HEAP_TAB_SIZE);
    /* include additional copy sections */
    *(.copy_sec)
    } > int_crom =0

  /*
   * C++ exception handling tables.  NOTE: gcc emits .eh_frame
   * sections when compiling C sources with debugging enabled (-g).
   * If you can be sure that your final application consists
   * exclusively of C objects (i.e., no C++ objects), you may use
   * the -R option of the "strip" and "objcopy" utilities to remove
   * the .eh_frame section from the executable.
   */
  .eh_frame :
  {
    . = ALIGN(8) ;
    *(.gcc_except_table)
    __EH_FRAME_BEGIN__ = . ;
    KEEP (*(.eh_frame))
    __EH_FRAME_END__ = . ;
    . = ALIGN(4) ;
  } > int_crom =0


  /*
   * allocate all .text_i ( = executable code) sections into internal flash
   */
  .text_i :
  {
    . = ALIGN(4);
    *(.text_i)
    *(.text_i.*)
  } > int_crom =0

  /*
   * allocate all read only data sections defined for internal flash
   */
  .rodata_i :
  {
    . = ALIGN(8);
    *(.rodata_i)
    *(.rodata_i.*)
  } > int_crom =0

  /*
   * allocate all executable code explicitly placed to external flash
   */
  .text_e :
  {
    . = ALIGN(4);
    *(.text_e)
    *(.text_e.*)
  } > int_crom =0

  /*
   * allocate all read only data sections explicitly defined for external flash
   */
  .rodata_e :
  {
    . = ALIGN(8);
    *(.rodata_e)
    *(.rodata_e.*)

    *(.toc)
    *(.jcr)

  } > int_crom =0
}




  /*
   *  we locate the STW Bios Sections for .data, .bss and .noinit first,
   *  in case they shall be protected from the Application
   *
   *  MPU_EXPORT_STW_BIOS_EXT_RAM_START and MPU_EXPORT_STW_BIOS_EXT_RAM_END
   *  are exported as values for the MPU
   */
SECTIONS
{
  .stw_bios_data (MEM_EXT_RES_END):
  {
    /* Export address for MPU usage */
    . = ALIGN(8);
    MPU_EXPORT_STW_BIOS_EXT_RAM_START = ABSOLUTE(.);
    /* Add 8 Byte MPU safety zone (unused) */
    . += 8;
    SEC_STW_BIOS_DATA_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.data*))
    . = ALIGN(4);
    SEC_STW_BIOS_DATA_END = ABSOLUTE(.);
    } > ext_dram AT> int_crom


  /* stw_bios_bss MUST be adjacent with stw_bios_data section */
  .stw_bios_bss (SEC_STW_BIOS_DATA_END)(NOLOAD):
  {
    SEC_STW_BIOS_BSS_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.bss*))
    SEC_STW_BIOS_BSS_END = ABSOLUTE(.);

    SEC_STW_BIOS_NOINIT_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.noinit*))
    SEC_STW_BIOS_NOINIT_END = ABSOLUTE(.);

    /* Reserve memory for extern system heap in STW - protected memory area */
    . = ALIGN(8);
    __HEAP_SYS_EXTERN = ABSOLUTE(.);
    . += __HEAP_SYS_EXTERN_SIZE;
    __HEAP_SYS_EXTERN_END = ABSOLUTE(.);


    /* add another 8 Byte MPU safety zone... */
    . += 8;
    /* ... before we export the last address used by the STW Bios */
    . = ALIGN(8);
    MPU_EXPORT_STW_BIOS_EXT_RAM_END = ABSOLUTE(.);
    } >ext_dram

  /* Make sure enough memory is available for extern system heap.  */
  _. = ASSERT ((__HEAP_SYS_EXTERN & 7) == 0 , "extern SYSTEM HEAP not doubleword aligned") ;
  _. = ASSERT ((__HEAP_SYS_EXTERN_END - __HEAP_SYS_EXTERN) >= __HEAP_SYS_EXTERN_MIN , "not enough memory for extern SYSTEM HEAP") ;

  _. = ASSERT((SEC_STW_BIOS_BSS_START == SEC_STW_BIOS_DATA_END), "STW BIOS bss and data sections must be contiguous!");


  .clear_sec :
  {
    LONG(SEC_STW_BIOS_BSS_START);   LONG(SEC_STW_BIOS_BSS_END - SEC_STW_BIOS_BSS_START);
  } > int_crom


  .copy_sec :
  {
    LONG(LOADADDR(.stw_bios_data));   LONG(0 + ADDR(.stw_bios_data));LONG(SIZEOF(.stw_bios_data));
  } > int_crom
}


/*
 *  Followed by .data, .bss and .noinit sections for the
 *  "protected application data"
 *
 *  MPU_EXPORT_PROTECTED_EXT_RAM_START and MPU_EXPORT_PROTECTED_EXT_RAM_END
 *  are exported as values for the MPU
 */
SECTIONS
{
  .protected_data (MPU_EXPORT_STW_BIOS_EXT_RAM_END):
  {
    /* Export address for MPU usage */
    . = ALIGN(8);
    MPU_EXPORT_PROTECTED_EXT_RAM_START = ABSOLUTE(.);
    /* Add 8 Byte MPU safety zone (unused) */
    . += 8;
    SEC_PROTECTED_DATA_START = ABSOLUTE(.);
    KEEP(*(*.protected.data*))
    . = ALIGN(4);
    SEC_PROTECTED_DATA_END = ABSOLUTE(.);
  } > ext_dram AT> int_crom


  /* protected_bss MUST be adjacent with protected_data section */
  .protected_bss (SEC_PROTECTED_DATA_END)(NOLOAD):
  {
    SEC_PROTECTED_BSS_START = ABSOLUTE(.);
    KEEP(*(*.protected.bss*))
    SEC_PROTECTED_BSS_END = ABSOLUTE(.);

    SEC_PROTECTED_NOINIT_START = ABSOLUTE(.);
    KEEP(*(*.protected.noinit*))
    SEC_PROTECTED_NOINIT_END = ABSOLUTE(.);
    /* add another 8 Byte MPU safety zone... */
    . += 8;
    . = ALIGN(8);
    /* ... before we export the last address used by the STW Bios */
    MPU_EXPORT_PROTECTED_EXT_RAM_END = ABSOLUTE(.);
    } >ext_dram

    _. = ASSERT((SEC_PROTECTED_BSS_START == SEC_PROTECTED_DATA_END),"protected bss and data sections must be contiguous!");

    .clear_sec :
  {
    LONG(SEC_PROTECTED_BSS_START);   LONG(SEC_PROTECTED_BSS_END - SEC_PROTECTED_BSS_START);
  } > int_crom

  .copy_sec :
  {
    LONG(LOADADDR(.protected_data));   LONG(0 + ADDR(.protected_data));LONG(SIZEOF(.protected_data));
  } > int_crom
}



  /*
   * The following sections are special in that their initial code or
   * data (if any) must also be stored in said text part of an
   * executable, but they "live" at completely different addresses
   * at runtime -- usually in RAM areas.  NOTE: This is not really
   * necessary if you use a special program loader (e.g., a debugger)
   * to load a complete executable consisting of code, data, BSS, etc.
   * into the RAM of some target hardware or a simulator, but it *is*
   * necessary if you want to burn your application into non-volatile
   * memories such as EPROM or FLASH.
   */
SECTIONS
{
  .ivect :
  {
    KEEP(*(.inttab))
  } > int_ivram AT> int_crom

  /* we need fcram load address for the rom monitor because it must patch the default interrupt vector table */
  MEM_INT_IVRAM_LOADADDR_START = LOADADDR(.ivect);


  .fcram :
  {
    MEM_INT_FCRAM_START = ABSOLUTE(.);
    SEC_STW_BIOS_FASTRAM_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.fastram*))
    SEC_STW_BIOS_FASTRAM_END = ABSOLUTE(.);

    KEEP(*(.fastram))
    . = ALIGN(4) ;
    MEM_INT_FCRAM_END = ABSOLUTE(.);
  } > int_fcram AT> int_crom

  /* we need fcram load address for the memory statistics */
  MEM_INT_FCRAM_LOADADDR_START = LOADADDR(.fcram);

  .cram :
  {
    SEC_STW_BIOS_CODERAM_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.coderam*))
    SEC_STW_BIOS_CODERAM_END = ABSOLUTE(.);
    KEEP(*(.coderam))
    . = ALIGN(4) ;
  } > ext_cram AT> int_crom

  .pcptext :
  {
    KEEP(*(.pcptext))
    KEEP(*(.pcptext.*))
    . = ALIGN(4) ;
  } > pcp_text AT> int_crom

  .pcpdata :
  {
    KEEP(*(.pcpdata))
    KEEP(*(.pcpdata.*))
    . = ALIGN(4) ;
  } > pcp_data AT> int_crom
}



/*
 * Locate application standard data sections...
 */

SECTIONS
{
  .data :
  {
    . = ALIGN(8);
    MPU_EXPORT_UNPROTECTED_EXT_RAM_START = ABSOLUTE(.);
    /* Add 8 Byte MPU safety zone (unused) */
    . += 8;
    SEC_DATA_START = ABSOLUTE(.);
    *(.data)

    /* sort data according to their alignment (only needed with -maligned-data-sections compiler switch) */
    *(.data.a1)                  /* 1-byte alignment       */
    *(.data.a2)                  /* 2-byte alignment       */
    *(.data.a4)                  /* 4-byte alignment       */
    *(.data.a8)                  /* >= 8-byte alignment    */
    *(.data.*)

    *(.gnu.linkonce.d.*)
    SEC_DATA_END = ABSOLUTE(.);
    . = ALIGN(8);
  } > ext_dram AT> int_crom

  /*
   * Allocate space for BSS sections.
   */
  .bss (NOLOAD) :
  {
    SEC_BSS_START = ABSOLUTE(.);
    *(.bss)

    /* sort bss according to their alignment (only needed with -maligned-data-sections compiler switch) */
    *(.bss.a1)                /* 1-byte alignment       */
    *(.bss.a2)                /* 2-byte alignment       */
    *(.bss.a4)                /* 4-byte alignment       */
    *(.bss.a8)                /* >= 8-byte alignment    */
    *(.bss.*)

    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(8) ;
    BSS_CLEAR = ABSOLUTE(.) - (SEC_BSS_START);
    SEC_BSS_END = ABSOLUTE(.);
    
    SEC_NOINIT_START = ABSOLUTE(.);
    *(.noinit)
    SEC_NOINIT_END = ABSOLUTE(.);
    
    . = ALIGN(8) ;
    /* Add 8 Byte MPU safety zone (unused) */
    . += 8;
    MPU_EXPORT_UNPROTECTED_EXT_RAM_END = ABSOLUTE(.);
  } > ext_dram
}



/*
 * These are tricore - specific sections for special memory areas and addressing types
 */
SECTIONS
{
  /*
   * Allocate space for absolute addressable sections; this requires that
   * "int_sram" starts at a TriCore segment (256M) and points to
   * some RAM area!  If these conditions are not met by your particular
   * hardware setup, you should either not use absolute data, or you
   * must move .{z,b}{data,bss}{,.*} input sections to some appropriate
   * memory area.
   */
  .zdata :
  {
    ZDATA_BASE = ABSOLUTE(.) ;
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
    *(.bdata)
    *(.bdata.*)
    . = ALIGN(8) ;
    ZDATA_END = ABSOLUTE(.) ;
  } > int_sram AT> int_crom

  /* make sure, that zdata is placed at an absolute addressable memory region */
  _. = ASSERT(((ZDATA_BASE & 0x0FFFC000) == 0) &&
              ((ZDATA_END & 0x0FFFC000) == 0) &&
              ((ZDATA_BASE & 0xF0000000) == (ZDATA_END & 0xF0000000)),
              "zdata section must be inside an absolute addressable memory region!");

  .zbss (NOLOAD) :
  {
    ZBSS_BASE = ABSOLUTE(.) ;
    *(.zbss)
    *(.zbss.*)
    *(.gnu.linkonce.zb.*)
    *(.bbss)
    *(.bbss.*)
    . = ALIGN(8) ;
    ZBSS_END = ABSOLUTE(.) ;
  } > int_sram

  /* make sure, that zbss is placed at an absolute addressable memory region */
  _. = ASSERT(((ZBSS_BASE & 0x0FFFC000) == 0) &&
              ((ZBSS_END & 0x0FFFC000) == 0) &&
              ((ZBSS_BASE & 0xF0000000) == (ZBSS_END & 0xF0000000)),
              "zbss section must be inside an absolute addressable memory region!");

}


/* Locate all small data and bss sections */

SECTIONS
{

  /* small data and bss section, addressed by global register A3 */
  .sdata4 :
  {
    *(.sdata.stw_bios)
    *(.sdata.stw_bios.*)
    . = ALIGN(8) ;
  } > int_sram AT>int_crom

  .sbss4 (NOLOAD) :
  {
    *(.sbss.stw_bios)
    *(.sbss.stw_bios.*)
    . = ALIGN(8) ;
  } > int_sram

  /* small rodata section in for STW BIOS, addressed by global register A2 */
  .sdata3 :
  {
    SEC_STW_BIOS_SDATA_RODAT_START = ABSOLUTE(.);
    *(.sdata.stw_bios_rodata)
    *(.sdata.stw_bios_rodata.*)
    SEC_STW_BIOS_SDATA_RODAT_END = ABSOLUTE(.);
    . = ALIGN(8);
  } > int_crom


  /* The sdata2 section should be used for small rodata */
  .sdata2 :
  {
    *(.sdata.rodata)
    *(.sdata.rodata.*)
    . = ALIGN(8);
  } > int_crom


  /* small data and bss section, addressed by global register A0 */
  /* This .sdata/sbss set can be used by the application         */
  .sdata :
  {
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
  } > ext_dram AT> int_crom

  .sbss (NOLOAD) :
  {
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    . = ALIGN(8);
  } > ext_dram
}


SECTIONS
{
  .sram :
  {
    SEC_STW_BIOS_SRAM_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.sram*))
    SEC_STW_BIOS_SRAM_END = ABSOLUTE(.);
    *(.sram)
    *(.sram_*)
    *(.sram.data)
    . = ALIGN(8);
  } > int_sram AT> int_crom


  /*
   * allocate interrupt and user hardware stack at the beginning of LDRAM
   */
  .stack (NOLOAD) :
  {
    /* istack starts with start address of DRAM. We don't need protect it with the MPU */
    . = ALIGN(8);
    MPU_EXPORT_ISTACK_START = ABSOLUTE (.);
    __ISTACK_START = ABSOLUTE(.);
    . += __ISTACK_SIZE;
    /* ISTACK must be 64 Bit aligned */
    .  = ALIGN(8);
    __ISTACK = ABSOLUTE(.);
    . = ALIGN(8);
    MPU_EXPORT_ISTACK_END = ABSOLUTE(.);
    /* Add an 32 Byte gap for the MPU. This is needed to protect the ISTACK from USTACK overflow */
    . += 32;
    MPU_EXPORT_USTACK_START = ABSOLUTE(.);
    __USTACK_START = ABSOLUTE(.);
    . += __USTACK_SIZE;
    /* USTACK must be 64 Bit aligned */
    .  = ALIGN(8);
    __USTACK = ABSOLUTE(.);
    MPU_EXPORT_USTACK_END = ABSOLUTE(.);
    /* Add an 32 Byte gap for the MPU to make a USTACK underflow better detectable */
    . += 32;
    /* Emitt MPU signal for next data section after USTACK */
    MPU_EXPORT_USTACK_NEXT = ABSOLUTE(.);
    /* add 8 padding bytes after MPU marker because of MPU 64 bit protection issue */
    . += 8;
  } > int_dram

  _. = ASSERT (__ISTACK_START == (MEM_INT_DRAM_START), "__ISTACK_START must start with first dram address") ;

  /*
   * allocate user data inside LDRAM after stack
   */
  .dram :
  {
    . = ALIGN(8);
    SEC_STW_BIOS_DRAM_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.dram*))
    SEC_STW_BIOS_DRAM_END = ABSOLUTE(.);
    KEEP(*(.dram*))
  } > int_dram AT> int_crom


  /*
   * Locate Tricore dual-ported RAM
   */
  .dpram :
  {
    SEC_STW_BIOS_DPRAM_START = ABSOLUTE(.);
    KEEP(*(*.stw_bios.dpram*))
    SEC_STW_BIOS_DPRAM_END = ABSOLUTE(.);

    KEEP(*(.dpram))
    . = ALIGN(4) ;
  } > int_dpram AT> int_crom


  /*
   * Locate Tricore standby RAM
   */
  .sbram :
  {
    SEC_STW_DIAG_RAM_START = ABSOLUTE(.);
    KEEP(*(.diag_ram*))
    . = ALIGN(4);
    SEC_STW_DIAG_RAM_END = ABSOLUTE(.);
    KEEP(*(.sbram*))
    . = ALIGN(4);
  } > int_sbram AT> int_crom
}

/*
 * Emit definition of interrupt and trap table sizes and base addresses for startup code
 */
SECTIONS
{
  __INTVECT_SIZE = SIZEOF(.ivect);
  __TRAPVECT_SIZE = SIZEOF(.tvect);

  __INTVECT_BASE = (0 + ADDR(.ivect));
  __TRAPVECT_BASE = (0 + ADDR(.tvect));
}


/*
 * Statistic variables (must be declared after all sections has been filled with static data)
 */
SECTIONS
{
  /* set marker for end of used int_crom*/
  .int_crom_stat :
  {
    /* end of used internal rom will be exported as uint32 to the application and should be aligned */
    . = ALIGN(4);
    MEM_INT_CROM_USED_END = ABSOLUTE(.);
  } > int_crom

  /* set marker for end of used ext_crom */
  .ext_crom_stat :
  {
    /* end of used external rom will be exported as uint32 to the application and should be aligned */
    MEM_EXT_CROM_USED_END = ABSOLUTE(ALIGN(4));
  } > ext_crom


  /* define end of ext_dram data; All memory left after this marker will be used for std. HEAP */
  .ext_dram_stat :
  {
    MEM_EXT_DRAM_USED_END = ABSOLUTE(.) ;
  } > ext_dram

  /* set marker for end of used ext_cram */
  .ext_cram_stat :
  {
    MEM_EXT_CRAM_USED_END = ABSOLUTE(.);
  } > ext_cram

  /* set marker for end of used int_sram; All memory left after this marker will be used for system HEAP */
  .int_sram_stat :
  {
    MEM_INT_SRAM_USED_END = ABSOLUTE(.);
  } >int_sram

  /* set marker for end of used int_sbram */
  .int_sbram_stat :
  {
    MEM_INT_SBRAM_USED_END = ABSOLUTE(.);
  } >int_sbram

  /* set marker for end of used int_dram */
  .int_dram_stat :
  {
    MEM_INT_DRAM_USED_END = ABSOLUTE(.);
    MEM_INT_DSPR_USED_END = ABSOLUTE(.);
  } >int_dram

  /* set marker for end of used int_dpram */
  .int_dpram_stat :
  {
    MEM_INT_DPRAM_USED_END = ABSOLUTE(.);
  } >int_dpram

  /* set marker for end of used int_fcram */
  .int_fcam_stat :
  {
    MEM_INT_FCRAM_USED_END = ABSOLUTE(.);
    MEM_INT_PSPR_USED_END  = ABSOLUTE(.);
  } >int_fcram

  /* set marker for end of used pcp_data */
  .pcp_data_stat :
  {
    MEM_PCP_DATA_USED_END = ABSOLUTE(.);
  } >pcp_data

  /* set marker for end of used pcp_text */
  .pcp_text_stat :
  {
    MEM_PCP_TEXT_USED_END = ABSOLUTE(.);
  } >pcp_data
}


/*
 * Static data statistics have been set.
 * Now we use the rest of the remaining memory for dynamic data. (Heap and CSA)
 */
SECTIONS
{

  .dram_csa :
  {
    /* CSA starts after DRAM end address */
    __CSA_BEGIN = ABSOLUTE(ALIGN(0x40));
  } >int_dram


  .ext_dram_heap :
  {
    /* locate space for heap behind last external RAM section */
    /* symbols edata and end are used by newlib malloc function */
     . = ALIGN(8);
    __HEAP = ABSOLUTE(.);
    PROVIDE(edata = MEM_EXT_DRAM_USED_END);
    . = MEM_EXT_DRAM_END - MEM_EXT_DRAM_USED_END;
    __HEAP_END = ABSOLUTE(.);
    __HEAP_SIZE = __HEAP_END - __HEAP;
    PROVIDE(end = __HEAP_END);
  } >ext_dram

  /* Make sure enough memory is available for heap.  */
  _. = ASSERT ((__HEAP & 7) == 0 , "HEAP not doubleword aligned") ;
  _. = ASSERT ((__HEAP_END - __HEAP) >= __HEAP_MIN , "not enough memory for HEAP") ;

  .int_sram_heap :
  {
      /* locate space for SYSTEM heap behind last SRAM section */
     . = ALIGN(8);
     __HEAP_SYS_INTERN = ABSOLUTE(.) ;

    /* move location pointer to the end of the int_sram memory to prevent any
       static data to be placed into the HEAP area */
    . = MEM_INT_SRAM_END - MEM_INT_SRAM_USED_END;
    __HEAP_SYS_INTERN_END = ABSOLUTE(.);
    __HEAP_SYS_INTERN_SIZE = __HEAP_SYS_INTERN_END - __HEAP_SYS_INTERN;
  } >int_sram

  /* Make sure enough memory is available for SRAM heap.  */
  _. = ASSERT ((__HEAP_SYS_INTERN & 7) == 0 , "SRAM HEAP not doubleword aligned") ;
  _. = ASSERT ((__HEAP_SYS_INTERN_END - __HEAP_SYS_INTERN) >= __HEAP_SYS_INTERN_MIN , "not enough memory for SRAM HEAP") ;
}


/*
 * All relocatable sections have been defined. We can now terminate the clear and copy table
 */
SECTIONS
{
  .clear_sec :
  {
    LONG(-1);                 LONG(-1);
    . = ALIGN(8);
  } > int_crom

  .copy_sec :
  {
    LONG(-1);                 LONG(-1);                  LONG(-1);
    . = ALIGN(8);
  } > int_crom
}


/*
 * DWARF debug sections.
 * Symbols in the DWARF debugging sections are relative to the
 * beginning of the section, so we begin them at 0.
 */
SECTIONS
{
  /*
   * DWARF 1
   */
  .comment         0 : { *(.comment) }
  .debug           0 : { *(.debug) }
  .line            0 : { *(.line) }
  /*
   * GNU DWARF 1 extensions
   */
  .debug_srcinfo   0 : { *(.debug_srcinfo) }
  .debug_sfnames   0 : { *(.debug_sfnames) }
  /*
   * DWARF 1.1 and DWARF 2
   */
  .debug_aranges   0 : { *(.debug_aranges) }
  .debug_pubnames  0 : { *(.debug_pubnames) }
  /*
   * DWARF 2
   */
  .debug_info      0 : { *(.debug_info) }
  .debug_abbrev    0 : { *(.debug_abbrev) }
  .debug_line      0 : { *(.debug_line) }
  .debug_frame     0 : { *(.debug_frame) }
  .debug_str       0 : { *(.debug_str) }
  .debug_loc       0 : { *(.debug_loc) }
  .debug_macinfo   0 : { *(.debug_macinfo) }
  .debug_ranges    0 : { *(.debug_ranges) }
  /*
   * SGI/MIPS DWARF 2 extensions
   */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /*
   * Optional sections that may only appear when relocating.
   */
  /*
   * Optional sections that may appear regardless of relocating.
   */
  .version_info    0 : { *(.version_info) }
  .boffs           0 : { KEEP (*(.boffs)) }
}
