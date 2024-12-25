VECTOR_BASE                        = 0x00000000;

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00000400;
CSTACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x00000800;

MEMORY
{
  FLASH (xr) : ORIGIN = 0x00000000, LENGTH = 0x00200000
  RAM0 (xrw) : ORIGIN = 0x1ffe0000, LENGTH = 0x00020000
  RAM1 (xrw) : ORIGIN = 0x20000000, LENGTH = 0x00020000

}

/* Entry Point */
ENTRY(Reset_Handler)


/* Sections Definitions */

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.intvec))     /* Startup code */
        . = ALIGN(4);
    } > FLASH

    .rom : ALIGN(4)
    {
        . = ALIGN(4);
        *(.text)                 /* .text sections (code) */
        *(.text*)                /* .text* sections (code) */
        *(.rodata)               /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
        *(.glue_7)               /* glue arm to thumb code */
        *(.glue_7t)              /* glue thumb to arm code */
        *(.eh_frame)
        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(4);
    } > FLASH
    
    .ARM.exidx :
    {
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
    } > FLASH

    __TEXT_END = .;    /* global symbol at end of code */
    __DATA_ROM = .; /* Symbol used for startup for data initialization */

    .data : AT(__DATA_ROM)
    {
        . = ALIGN(4);
        __DATA_RAM = .;
        __data_start__ = .;      /* create a global symbol at data start */
        *(.data)                 /* .data sections */
        *(.data*)                /* .data* sections */
        *(.code_ram)          /*Custom section for storing code in SRAM*/
        KEEP(*(.jcr*))
        . = ALIGN(4);
        __data_end__ = .;        /* define a global symbol at data end */
    } > RAM1

    __DATA_END = __DATA_ROM + SIZEOF(.data);
    ASSERT(__DATA_END <= (ORIGIN(FLASH) + LENGTH(FLASH)), "region m_text overflowed with text and data")

    .bss :
    {
        /* This is used by the startup in order to initialize the .bss section */
        . = ALIGN(4);
        __START_BSS = .;
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
        __END_BSS = .;
    } > RAM1

    .heap :
    {
        . = ALIGN(8);
        __end__ = .;
        PROVIDE(end = .);
        __HeapBase = .;
        . += HEAP_SIZE;
        __HeapLimit = .;
    } > RAM1
    
    /* Initializes stack on the end of block */
    __StackTop   = ORIGIN(RAM1) + LENGTH(RAM1);
    __StackLimit = __StackTop - CSTACK_SIZE;
    PROVIDE(CSTACK = __StackTop);

    .stack __StackLimit :
    {
        . = ALIGN(8);
        __stack_start__ = .;
        . += CSTACK_SIZE;
        __stack_end__ = .;
    } > RAM1

    __RAM_START = ORIGIN(RAM0);
    __RAM_END = __StackTop - 1;
}
