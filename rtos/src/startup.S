.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global Default_Handler

.section .isr_vector, "a", %progbits

.word _estack
.word Reset_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler


.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:

    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

copy_data:
    cmp r1, r2
    bcc copy_data_loop
    b clear_bss

copy_data_loop:
    ldr r3, [r0]
    str r3, [r1]

    adds r0, r0, #4
    adds r1, r1, #4

    b copy_data


clear_bss:

    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0

clear_bss_loop:

    cmp r1, r2
    bcc clear_bss_do

    b call_main

clear_bss_do:

    str r3, [r1]

    adds r1, r1, #4

    b clear_bss_loop


call_main:

    bl main

hang:

    b hang


.section .text.Default_Handler
.type Default_Handler, %function

Default_Handler:

    b Default_Handler
