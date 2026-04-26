/* The bootloader will start execution at the symbol designated as the entry point. In this case, that's 'start' (defined in start.s) */
ENTRY(start)

/* Tell the linker part of the compiler where the various sections of the kernel will be put in the final kernel executable. */
SECTIONS
{
	/* Begin putting sections at 1 Megabyte (1M), a good place for kernels to be loaded at by the bootloader. */
	/* This is because memory below 1 Megabyte is reserved for other x86-related things, so we can't use it */


	. = 0x100;
	.multiboot : {
		*(.multiboot)
	}

	/* put gdt section at 0x800 */
	. = 0x800;
	.gdt : {
		KEEP(*(.gdt))
	}

	/* text section begin at 0x100000 */
	/* section for executable, read-only */
	. = 0x100000;
	.text : {
		*(.text)

	}

	/* data section begin at 0x500000 */
	/* section for initialized data (variables), read-write */
	. = 0x500000;
	.data : {
		*(.data)
	}

	.bss :
	{
		*(.bss)
	}
}