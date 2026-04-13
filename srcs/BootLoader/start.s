.extern main
.extern stack_top
.global start
 
.set MB_MAGIC, 0x1BADB002 
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
	.align 4
	.long MB_MAGIC
	.long MB_FLAGS
	.long MB_CHECKSUM

.section .gdt

lgdt [gdt_register]
reloadSegments:
	ljmp $0x08, $.reload_CS
.reload_CS:
	mov %ax, 0x10
	mov	%ds, %ax
	mov %es, %ax
	mov %fs, %ax
	mov %gs, %ax
	mov %ss, %ax
	ret

gdt_start:
	.word 0x0
	.word 0x0
	.word 0x0
	.word 0x0
gdt_kernel_code:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x9A  
	.byte 0xC
	.byte 0x0

gdt_kernel_data:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x92
	.byte 0xC
	.byte 0x0
gdt_kernel_stack:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x82 	
	.byte 0xC
	.byte 0x0
gdt_user_code:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0xFA	
	.byte 0xC
	.byte 0x0
gdt_user_data:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0xF2 
	.byte 0xC
	.byte 0x0
gdt_user_stack:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0xE2
	.byte 0xC
	.byte 0x0

gdt_end:

gdt_register:
	.word 0
	.long 0


.section .bss
	
	.align 16
	stack_bottom:
		.skip 16384
	stack_top:

.section .text
	
	start:
		mov $stack_top, %esp
 
		call main
 
		hang:
			cli
			hlt
			jmp hang
