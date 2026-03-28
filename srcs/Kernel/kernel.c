// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include "kernel.h"

// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif


void kernel_main()
{

	term_init();

	// base tests
	term_write_all(STRING, "42");
	term_write_all(STRING, (void *)"lol");
	term_write_all(INTEGER, (void *)42);
	term_write_all(HEXADECIMAL, (void *)vga_buffer);
	term_write_all(STRING, "\n");
	ft_printf("test str : %s", "lol");
	ft_printf("test int : %i", 42);
	ft_printf("test pointeur : %p", vga_buffer);
	term_write_all(STRING, "\n");

	// keyboard and multi-screen support
	while (true)
	{
		uint8_t scancode = keyboard_read_input();
		if (scancode == 0x1D)
		{
			if (buff_indicator)
			{
				ft_chrcpy(term_two.buffer, term_buffer, VGA_COLS * VGA_ROWS);
				term_two.col = term_col;
				term_two.row = term_row;
				ft_chrcpy(term_buffer, term_one.buffer, VGA_COLS * VGA_ROWS);
				term_row = term_one.row;
				term_col = term_one.col;
			}
			else
			{
				ft_chrcpy(term_one.buffer, term_buffer, VGA_COLS * VGA_ROWS);
				term_one.col = term_col;
				term_one.row = term_row;
				ft_chrcpy(term_buffer, term_two.buffer, VGA_COLS * VGA_ROWS);
				term_row = term_two.row;
				term_col = term_two.col;
			}
			buff_indicator = !buff_indicator;
			update_cursor(term_col, term_row);
		}
		else
		{
			term_write_all(HEXADECIMAL, (void *)scancode);
			term_putchar( keymap[scancode]);
			term_write_all(STRING, "\n");
		}
	}
}