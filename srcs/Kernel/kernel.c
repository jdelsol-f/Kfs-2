/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:55:58 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/26 13:14:38 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include "kernel.h"

int	ft_isalpha(int c)
{
	if (! ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')))
		return (0);
	return (1);
}

extern void reloadSegments();

void main()
{
	
	t_general_struct data;
	t_gdt	my_gdt;
	bool shift1 = false;
	bool shift2 = false;
	bool capslock = false;
	bool numlock = false;
	bool E0 = false;

	char testtab[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	get_data(&data);
	term_init(&data);
	update_cursor(&data);
	GetGdt(&my_gdt);
	// mandatory part
	// ft_printf("%i\n", 42);

	// gdt display

	ft_printf("GDT(%p):\n\n", my_gdt.addr);	
	ft_printf("start:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.start[0], my_gdt.start[1], my_gdt.start[2], my_gdt.start[3], my_gdt.start[4], my_gdt.start[5], my_gdt.start[6], my_gdt.start[7]);
	ft_printf("kernel code:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.kernel_code[0], my_gdt.kernel_code[1], my_gdt.kernel_code[2], my_gdt.kernel_code[3], my_gdt.kernel_code[4], my_gdt.kernel_code[5], my_gdt.kernel_code[6], my_gdt.kernel_code[7]);
	
	term_putchar(testtab[(my_gdt.kernel_code[0] / 16)]);
	term_putchar(testtab[(my_gdt.kernel_code[0] % 16)]);
	term_putchar('\n');
	update_cursor(&data);
	ft_printf("kerbelcode(%p)\n", my_gdt.kernel_code);	
	// ft_printf("kernel data:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.kernel_data[0], my_gdt.kernel_data[1], my_gdt.kernel_data[2], my_gdt.kernel_data[3], my_gdt.kernel_data[4], my_gdt.kernel_data[5], my_gdt.kernel_data[6], my_gdt.kernel_data[7]);
	// ft_printf("kernel stack:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.kernel_stack[0], my_gdt.kernel_stack[1], my_gdt.kernel_stack[2], my_gdt.kernel_stack[3], my_gdt.kernel_stack[4], my_gdt.kernel_stack[5], my_gdt.kernel_stack[6], my_gdt.kernel_stack[7]);
	// ft_printf("user code:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.user_code[0], my_gdt.user_code[1], my_gdt.user_code[2], my_gdt.user_code[3], my_gdt.user_code[4], my_gdt.user_code[5], my_gdt.user_code[6], my_gdt.user_code[7]);
	// ft_printf("user data:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.user_data[0], my_gdt.user_data[1], my_gdt.user_data[2], my_gdt.user_data[3], my_gdt.user_data[4], my_gdt.user_data[5], my_gdt.user_data[6], my_gdt.user_data[7]);
	// ft_printf("user stack:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", my_gdt.user_stack[0], my_gdt.user_stack[1], my_gdt.user_stack[2], my_gdt.user_stack[3], my_gdt.user_stack[4], my_gdt.user_stack[5], my_gdt.user_stack[6], my_gdt.user_stack[7]);
	
	// keyboard and multi-screen support
	int itest = 0;
	while (true)
	{
		if (my_gdt.kernel_code[itest] != 0)
		{
			ft_printf("test (%i)\n", my_gdt.kernel_code[itest]);
			ft_printf("test addr (%p)\n", &my_gdt.kernel_code[itest]);
			break;
		}
		itest++;
	}
	

	while (true)
	{
		
		uint8_t scancode = keyboard_read_input();
		if (scancode == CTRL)
		{
			if (data.buff_indicator)
			{
				ft_chrcpy(data.term_two.buffer, TERM_BUFFER, VGA_COLS * VGA_ROWS);
				data.term_two.col = data.col;
				data.term_two.row = data.row;
				data.term_two.term_color = data.term_color;

				ft_chrcpy(TERM_BUFFER, data.term_one.buffer, VGA_COLS * VGA_ROWS);
				data.row = data.term_one.row;
				data.col = data.term_one.col;
				data.term_color = data.term_one.term_color;
			}
			else
			{
				ft_chrcpy(data.term_one.buffer, TERM_BUFFER, VGA_COLS * VGA_ROWS);
				data.term_one.col = data.col;
				data.term_one.row = data.row;
				data.term_one.term_color = data.term_color;

				ft_chrcpy(TERM_BUFFER, data.term_two.buffer, VGA_COLS * VGA_ROWS);
				data.row = data.term_two.row;
				data.col = data.term_two.col;
				data.term_color = data.term_two.term_color;
			}
			data.buff_indicator = !data.buff_indicator;
			
			update_cursor();
		}
		else if (E0)
		{
			ft_E0_KEY(scancode, &data);
			E0 = false;
		}
		else if (scancode == 0xE0)
			E0 = true;
			
		else if (scancode == LEFT_SHIFT)
			shift1 = true;

		else if (scancode == RIGHT_SHIFT)
			shift2 = true;

		else if (scancode == LEFT_SHIFT_RELEASE)
			shift1 = false;

		else if (scancode == RIGHT_SHIFT_RELEASE)
			shift2 = false;
			
		else if (scancode == CAPSLOCK)
			capslock = !capslock;
			
		else if (scancode == NUMLOCK)
			numlock = !numlock;
			
		else
		{
			char c;
			if (scancode > 0x58)
				continue;

			if (shift1 || shift2)
			{
				c = upper_base_keymap[scancode];
				if (c == 0)
					continue;
				if (capslock && ft_isalpha(c))
					c += 32;
			}
			
			else
			{
				c = lower_base_keymap[scancode];
				if (c == 0)
					continue;
				if (capslock && ft_isalpha(c))
					c -= 32;
			}
			
			if ( scancode >= 0x47 && scancode <= 0x53 && scancode != 0x4A && scancode != 0x4E)
				if (ft_Numlock(shift1 || shift2, numlock, scancode, &data))	
					continue;

			term_putchar(c);
			update_cursor();
		}
	}
}
