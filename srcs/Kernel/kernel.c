// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include "kernel.h"

char keymap[] = 
{
    [0x00] = '\0',
    [0x01] = '~',
    [0x02] = '1',
	[0x03] = '2',
	[0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
	[0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x0B] = '0',
	[0x0C] = '-',
    [0x0D] = '=',
    [0x0E] = '\b',
    [0x0F] = '\t',
	[0x10] = 'q',
    [0x11] = 'w',
    [0x12] = 'e',
    [0x13] = 'r',
	[0x14] = 't',
    [0x15] = 'y',
    [0x16] = 'u',
    [0x17] = 'i',
	[0x18] = 'o',
    [0x19] = 'p',
    [0x1A] = '[',
    [0x1B] = ']',
    [0x1C] = '\\',
    [0x1D] = ' ', //ctrl
    [0x1E] = 'a',
    [0x1F] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
	[0x22] = 'g',
	[0x23] = 'h',
	[0x24] = 'j',
	[0x25] = 'k',
	[0x26] = 'l',
	[0x27] = ';',
	[0x28] = '\'',
	[0x29] = '\n',
	[0x2A] = ' ', //shift in
	[0x2B] = '\\',
	[0x2C] = 'z',
	[0x2D] = 'x',
	[0x2E] = 'c',
	[0x2F] = 'v',
	[0x30] = 'b',
	[0x31] = 'n',
	[0x32] = 'm',
	[0x33] = ',',
	[0x34] = '.',
	[0x35] = '/',
	[0x36] = ' ',
	[0x37] = ' ',
	[0x38] = ' ', //alt
	[0x39] = ' ',
	[0x3A] = ' ', //capslocks in
};

void kernel_main()
{
	t_general_struct data;
	get_data(&data);
	term_init(&data);
	update_cursor(&data);

	// base tests
	term_write_all(STRING, "42");
	term_write_all(STRING, (void *)"lol");
	term_write_all(INTEGER, (void *)42);
	term_write_all(HEXADECIMAL, (void *)(TERM_BUFFER));
	term_write_all(STRING, "\n");
	ft_printf("test str : %s", "lol");
	ft_printf("test int : %i", 42);
	ft_printf("test pointeur : %p", (TERM_BUFFER));
	term_write_all(STRING, "\n");

	// keyboard and multi-screen support
	while (true)
	{
		uint8_t scancode = keyboard_read_input();
		if (scancode == 0x1D)
		{
			if (data.buff_indicator)
			{
				ft_chrcpy(data.term_two.buffer, TERM_BUFFER, VGA_COLS * VGA_ROWS);
				data.term_two.col = data.col;
				data.term_two.row = data.row;
				ft_chrcpy(TERM_BUFFER, data.term_one.buffer, VGA_COLS * VGA_ROWS);
				data.row = data.term_one.row;
				data.col = data.term_one.col;
			}
			else
			{
				ft_chrcpy(data.term_one.buffer, TERM_BUFFER, VGA_COLS * VGA_ROWS);
				data.term_one.col = data.col;
				data.term_one.row = data.row;
				ft_chrcpy(TERM_BUFFER, data.term_two.buffer, VGA_COLS * VGA_ROWS);
				data.row = data.term_two.row;
				data.col = data.term_two.col;
			}
			data.buff_indicator = !data.buff_indicator;
			update_cursor(NULL);
		}
		else
		{
			ft_printf("%p", scancode);
			ft_printf("char : %i", keymap[scancode]);
			term_putchar( keymap[scancode]);
			term_putchar('q');
			term_write_all(STRING, "\n");
		}
	}
}