ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 4M
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 4M
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);

        KEEP(*(.isr_vector))

        *(.text*)
        *(.rodata*)

        . = ALIGN(4);

        _etext = .;
    } > FLASH


    .data :
    {
        . = ALIGN(4);

        _sdata = .;

        *(.data*)

        . = ALIGN(4);

        _edata = .;
    } > RAM AT > FLASH

    _sidata = LOADADDR(.data);


    .bss :
    {
        . = ALIGN(4);

        _sbss = .;

        *(.bss*)
        *(COMMON)

        . = ALIGN(4);

        _ebss = .;
    } > RAM
}
