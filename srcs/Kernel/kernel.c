/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:55:58 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/27 14:16:00 by lflandri         ###   ########.fr       */
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

void main()
{
	
	t_general_struct data;
	bool shift1 = false;
	bool shift2 = false;
	bool capslock = false;
	bool numlock = false;
	bool E0 = false;
	bool second_init = false;

	get_data(&data);
	term_init(&data);
	update_cursor(&data);
	GetGdt(&(data.my_gdt));
	// mandatory part
	// ft_printf("%i\n", 42);

	// gdt display
	getgdt(&data);
	//print first prompt :
	
	setpromptready(&data);

	// keyboard and multi-screen support
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
				data.term_two.prompt.col = data.term_prompt.col;
				data.term_two.prompt.row = data.term_prompt.row;

				ft_chrcpy(TERM_BUFFER, data.term_one.buffer, VGA_COLS * VGA_ROWS);
				data.row = data.term_one.row;
				data.col = data.term_one.col;
				data.term_color = data.term_one.term_color;
				data.term_prompt.col = data.term_one.prompt.col;
				data.term_prompt.row = data.term_one.prompt.row;
			}
			else
			{
				ft_chrcpy(data.term_one.buffer, TERM_BUFFER, VGA_COLS * VGA_ROWS);
				data.term_one.col = data.col;
				data.term_one.row = data.row;
				data.term_one.term_color = data.term_color;
				data.term_one.prompt.col = data.term_prompt.col;
				data.term_one.prompt.row = data.term_prompt.row;

				ft_chrcpy(TERM_BUFFER, data.term_two.buffer, VGA_COLS * VGA_ROWS);
				data.row = data.term_two.row;
				data.col = data.term_two.col;
				data.term_color = data.term_two.term_color;
				data.term_prompt.col = data.term_two.prompt.col;
				data.term_prompt.row = data.term_two.prompt.row;
			}
			data.buff_indicator = !data.buff_indicator;
			
			update_cursor();
			if (!second_init)
			{
				second_init = true;
				setpromptready(&data);
			}
			
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

		else if (scancode == 0x1C)
			execute_command(&data);		

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

			if (data.col + 1 >= VGA_WIDTH || c == '\n')
			{
				if (data.row + 1 == VGA_HEIGHT && c != '\b')
				{
					if (data.term_prompt.row <= 0)
						data.term_prompt.col = 0;
					else
						data.term_prompt.row -= 1;
				}
			}
			term_putchar(c);
			update_cursor();
		}
	}
}
