
 
global start
 
%define MB_MAGIC 0x1BADB002 
%define MB_FLAGS (1 << 0) | (1 << 1)
%define MB_CHECKSUM (0 - (MB_MAGIC + MB_FLAGS))
 
section .multiboot
	align 4
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECKSUM
 

section .bss
	
	align 16
	stack_bottom:
		resb 4096 
	stack_top:

section .text
	
	start:
		mov esp, stack_top 
 		extern kernel_main
		call kernel_main
 
		hang:
			cli
			hlt
			jmp hang
