
MEMORY
{
  FLASH (xr) : ORIGIN = 0x00000000, LENGTH = 0x00080000
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 0x00010000
}

/* Sections Definitions */

SECTIONS
{
    HEAP_SIZE   = isdefined(__heap_size__)  ? __heap_size__  : 0x00000400;
    CSTACK_SIZE = isdefined(__stack_size__) ? __stack_size__ : 0x00000800;
    VECTOR_BASE                        = 0x00000000;
    .isr_vector :
    {
        . = ALIGN(4);
        "*(.intvec)"     /* Startup code */
        . = ALIGN(4);
    } > FLASH

    .rom :
    {
        . = ALIGN(4);
        "*(.text)"                 /* .text sections (code) */
        "*(.text*)"                /* .text* sections (code) */
        "*(.rodata)"               /* .rodata sections (constants, strings, etc.) */
        "*(.rodata*)"              /* .rodata* sections (constants, strings, etc.) */
        "*(.glue_7)"               /* glue arm to thumb code */
        "*(.glue_7t)"              /* glue thumb to arm code */
        "*(.syscall)"              /* for libsys.a*/
        . = ALIGN(4);
    } > FLASH
    
    __TEXT_END = .;    /* global symbol at end of code */
    __DATA_ROM = .; /* Symbol used for startup for data initialization */

    .data : AT(__DATA_ROM)
    {
        . = ALIGN(4);
        __DATA_RAM = .;
        __data_start__ = .;      /* create a global symbol at data start */
        "*(.data)"                 /* .data sections */
        "*(.data*)"                /* .data* sections */
        "*(.code_ram)"          /*Custom section for storing code in SRAM*/
        "*(.jcr*)"
        . = ALIGN(4);
        __data_end__ = .;        /* define a global symbol at data end */
    } > RAM

    __DATA_END = __DATA_ROM + SIZEOF(.data);

    .bss :
    {
        /* This is used by the startup in order to initialize the .bss section */
        . = ALIGN(4);
        __START_BSS = .;
        __bss_start__ = .;
        "*(.bss)"
        "*(.bss*)"
        "*(COMMON)"
        . = ALIGN(4);
        __bss_end__ = .;
        __END_BSS = .;
    } > RAM

    .heap :
    {
        . = ALIGN(8);
        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . += HEAP_SIZE;
        __HeapLimit = .;
    } > RAM


    
    /* Initializes stack on the end of block */
    __StackTop   = addr(RAM) + sizeof(RAM);
    __StackLimit = __StackTop - CSTACK_SIZE;
    PROVIDE(CSTACK = __StackTop);

    .stack __StackLimit :
    {
        . = ALIGN(8);
        __stack_start__ = .;
        . += CSTACK_SIZE;
        __stack_end__ = .;
    } > RAM

    __RAM_START = addr(RAM);
    __RAM_END = __StackTop - 1;
}
