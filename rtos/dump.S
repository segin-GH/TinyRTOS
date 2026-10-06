
kernel.elf:     file format elf32-littlearm


Disassembly of section .text:

00000000 <Reset_Handler-0x40>:
   0:	20400000 	.word	0x20400000
   4:	00000041 	.word	0x00000041
   8:	00000085 	.word	0x00000085
   c:	00000085 	.word	0x00000085
  10:	00000085 	.word	0x00000085
  14:	00000085 	.word	0x00000085
  18:	00000085 	.word	0x00000085
  1c:	00000085 	.word	0x00000085
  20:	00000085 	.word	0x00000085
  24:	00000085 	.word	0x00000085
  28:	00000085 	.word	0x00000085
  2c:	00000085 	.word	0x00000085
  30:	00000085 	.word	0x00000085
  34:	00000085 	.word	0x00000085
  38:	00000085 	.word	0x00000085
  3c:	00000085 	.word	0x00000085

00000040 <Reset_Handler>:
.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:

    ldr r0, =_sidata
  40:	480b      	ldr	r0, [pc, #44]	@ (70 <hang+0x4>)
    ldr r1, =_sdata
  42:	490c      	ldr	r1, [pc, #48]	@ (74 <hang+0x8>)
    ldr r2, =_edata
  44:	4a0c      	ldr	r2, [pc, #48]	@ (78 <hang+0xc>)

00000046 <copy_data>:

copy_data:
    cmp r1, r2
  46:	4291      	cmp	r1, r2
    bcc copy_data_loop
  48:	d300      	bcc.n	4c <copy_data_loop>
    b clear_bss
  4a:	e004      	b.n	56 <clear_bss>

0000004c <copy_data_loop>:

copy_data_loop:
    ldr r3, [r0]
  4c:	6803      	ldr	r3, [r0, #0]
    str r3, [r1]
  4e:	600b      	str	r3, [r1, #0]

    adds r0, r0, #4
  50:	3004      	adds	r0, #4
    adds r1, r1, #4
  52:	3104      	adds	r1, #4

    b copy_data
  54:	e7f7      	b.n	46 <copy_data>

00000056 <clear_bss>:


clear_bss:

    ldr r1, =_sbss
  56:	4909      	ldr	r1, [pc, #36]	@ (7c <hang+0x10>)
    ldr r2, =_ebss
  58:	4a09      	ldr	r2, [pc, #36]	@ (80 <hang+0x14>)
    movs r3, #0
  5a:	2300      	movs	r3, #0

0000005c <clear_bss_loop>:

clear_bss_loop:

    cmp r1, r2
  5c:	4291      	cmp	r1, r2
    bcc clear_bss_do
  5e:	d300      	bcc.n	62 <clear_bss_do>

    b call_main
  60:	e002      	b.n	68 <call_main>

00000062 <clear_bss_do>:

clear_bss_do:

    str r3, [r1]
  62:	600b      	str	r3, [r1, #0]

    adds r1, r1, #4
  64:	3104      	adds	r1, #4

    b clear_bss_loop
  66:	e7f9      	b.n	5c <clear_bss_loop>

00000068 <call_main>:


call_main:

    bl main
  68:	f000 f80e 	bl	88 <main>

0000006c <hang>:

hang:

    b hang
  6c:	e7fe      	b.n	6c <hang>
  6e:	0000      	.short	0x0000
    ldr r0, =_sidata
  70:	00000090 	.word	0x00000090
    ldr r1, =_sdata
  74:	20000000 	.word	0x20000000
    ldr r2, =_edata
  78:	20000004 	.word	0x20000004
    ldr r1, =_sbss
  7c:	20000004 	.word	0x20000004
    ldr r2, =_ebss
  80:	20000008 	.word	0x20000008

00000084 <Default_Handler>:
.section .text.Default_Handler
.type Default_Handler, %function

Default_Handler:

    b Default_Handler
  84:	f7ff bffe 	b.w	84 <Default_Handler>

00000088 <main>:

int varx = 7;
int vary;

int main(void)
{
  88:	b480      	push	{r7}
  8a:	af00      	add	r7, sp, #0
    while (1)
  8c:	e7fe      	b.n	8c <main+0x4>
	...
