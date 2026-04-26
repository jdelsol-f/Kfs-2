

.set MB_MAGIC, 0x1BADB002 
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
mb_header:
	.align 4
	.long MB_MAGIC
	.long MB_FLAGS
	.long MB_CHECKSUM



.extern main

.global start
.global gdt_start



.section .text


lgdt [gdt_ptr]

ljmp $0x08, $.reload_CS
.reload_CS:
	mov %ax, 0x10
	mov	%ds, %ax
	mov %es, %ax
	mov %fs, %ax
	mov %gs, %ax
	mov %ss, %ax
	ret

start:
	mov $stack_top, %esp
	call main
	cli

	hang:
		hlt
		jmp hang


.section .bss
	
	.align 16
	stack_bottom:
		.skip 16384
	stack_top:

.section .gdt
gdt_start:
	.word 0x0
	.word 0x0
	.word 0x0
	.word 0x0

gdt_kernel_code:	
	.word 0xffff	//limit
	.word 0x0		//base
	.byte 0x0		//limit_middle
	.byte 0x9A		//access_byte
	.byte 0xC		//flags
	.byte 0x0		//end_byte for the 32bits format


gdt_kernel_data:
	.word 0xffff	//limit
	.word 0x0		//base
	.byte 0x0		//limit_middle
	.byte 0x92		//access_byte
	.byte 0xC		//flags
	.byte 0x0		//end_byte for the 32bits format

gdt_kernel_stack:
	.word 0xffff	//limit
	.word 0x0		//base
	.byte 0x0		//limit_middle
	.byte 0x82		//access_byte
	.byte 0xC		//flags
	.byte 0x0		//end_byte for the 32bits format

gdt_user_code:
	.word 0xffff	//limit
	.word 0x0		//base
	.byte 0x0		//limit_middle
	.byte 0xFA		//access_byte
	.byte 0xC		//flags
	.byte 0x0		//end_byte for the 32bits format

gdt_user_data:
	.word 0xffff	//limit
	.word 0x0		//base
	.byte 0x0		//limit_middle
	.byte 0xF2 		//access_byte
	.byte 0xC		//flags
	.byte 0x0		//end_byte for the 32bits format

gdt_user_stack:
	.word 0xffff	//limit
	.word 0x0		//base
	.byte 0x0		//limit_middle
	.byte 0xE2		//access_byte
	.byte 0xC		//flags
	.byte 0x0		//end_byte for the 32bits format

gdt_end:

gdt_ptr:
	.word gdt_end - gdt_start - 1
	.long gdt_start

 


