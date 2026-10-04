ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 4M
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 4M
}

SECTIONS
{
    /*
     * Code and read-only data
     */
    .text :
    {
        . = ALIGN(4);

        KEEP(*(.isr_vector))

        *(.text*)
        *(.rodata*)

        . = ALIGN(4);

        _etext = .;
    } > FLASH


    /*
     * Initialized data
     *
     * The data lives in RAM at runtime,
     * but its initial values are stored in FLASH.
     */
    .data :
    {
        . = ALIGN(4);

        _sdata = .;

        *(.data*)

        . = ALIGN(4);

        _edata = .;
    } > RAM AT > FLASH

    /*
     * Address in FLASH where the initial
     * .data values are stored.
     */
    _sidata = LOADADDR(.data);


    /*
     * Uninitialized data
     *
     * This gets cleared to zero during
     * Reset_Handler.
     */
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
