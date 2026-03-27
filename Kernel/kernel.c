// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include "define.h"

// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

void kernel_main()
{
	term_init();

	term_writestring("42");
}