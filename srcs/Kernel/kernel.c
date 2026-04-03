/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:55:58 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/03 19:11:53 by jdelsol-         ###   ########.fr       */
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

enum e_arrow_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT	
};

enum e_page_cursor
{
	PG_UP,
	PG_DOWN,
	HOME,
	END	
};

static void ft_arrows(int *col,  int *row, int direction)
{
	switch (direction)
	{
	case UP:
		if (*row > 0)
			(*row)--;
		break;
		
	case DOWN:
		if (*row < VGA_HEIGHT - 1)
			(*row)++;
		break;
		
	case LEFT:
		if (*col > 0)
			(*col)--;
		break;
		
	case RIGHT:
		if  (*col < VGA_WIDTH - 1)
			(*col)++;
		break;
				
	default:
		break;
	}	
}

static void ft_page_cursor(int *col,  int *row, int direction)
{
	switch (direction)
	{
	case PG_UP:
		(*row) = 0;
		break;
		
	case PG_DOWN:
		(*row) = VGA_HEIGHT - 1;
		break;
		
	case HOME:
		(*col) = 0;
		break;
		
	case END:
		(*col) = VGA_WIDTH - 1;
		break;
				
	default:
		break;
	}	
}

static bool ft_Numlock(bool shift, bool numlock, uint8_t scancode, t_general_struct *data)
{
	if (!numlock || shift)
	{
		switch (scancode)
		{
		case NUM_7:
			ft_page_cursor(&data->col, &data->row, HOME);
			break;
		case NUM_8:
			ft_arrows(&data->col, &data->row, UP);
			break;
		case NUM_9:
			ft_page_cursor(&data->col, &data->row, PG_UP);
			break;
		case NUM_4:
			ft_arrows(&data->col, &data->row, LEFT);
			break;
		case NUM_6:
			ft_arrows(&data->col, &data->row, RIGHT);
			break;
		case NUM_1:
			ft_page_cursor(&data->col, &data->row, END);
			break;
		case NUM_2:
			ft_arrows(&data->col, &data->row, DOWN);
			break;
		case NUM_3:
			ft_page_cursor(&data->col, &data->row, PG_DOWN);
			break;
		case NUM_DOT:
			term_putchar('\b');
			break;

		default:
			break;
		}
		update_cursor();
		return true;
	}
	return false;
}

static void ft_E0_KEY(uint8_t scancode, t_general_struct *data)
{
	switch (scancode)
	{
	case NUM_7:
		ft_page_cursor(&data->col, &data->row, HOME);
		break;
	case NUM_8:
		ft_arrows(&data->col, &data->row, UP);
		break;
	case NUM_9:
		ft_page_cursor(&data->col, &data->row, PG_UP);
		break;
	case NUM_4:
		ft_arrows(&data->col, &data->row, LEFT);
		break;
	case NUM_6:
		ft_arrows(&data->col, &data->row, RIGHT);
		break;
	case NUM_1:
		ft_page_cursor(&data->col, &data->row, END);
		break;
	case NUM_2:
		ft_arrows(&data->col, &data->row, DOWN);
		break;
	case NUM_3:
		ft_page_cursor(&data->col, &data->row, PG_DOWN);
		break;
	case NUM_DOT:
		term_putchar('\b');
		break;
	case 0x1C:
		term_putchar('/');
		break;
	case 0x35:
		term_putchar('\n');
		break;

	default:
		break;
	}
	update_cursor();
}

void kernel_main()
{
	t_general_struct data;
	bool shift1 = false;
	bool shift2 = false;
	bool capslock = false;
	bool numlock = false;
	bool E0 = false;


	get_data(&data);
	term_init(&data);
	update_cursor(&data);
	// base tests
	term_write("42", 2);
	update_cursor();
	// for (size_t i = 0; i < (size_t)1; i++)
	// {
	// 	term_putchar("4"[i]);
	// }
	// term_write_all(STRING, "42");
	// term_write_all(STRING, (void *)"lol");
	// term_write_all(INTEGER, (void *)42);
	// term_write_all(HEXADECIMAL, (void *)0x00);
	// term_write_all(STRING, "\n");
	// ft_printf("test str : %s", "lol");
	// ft_printf("test pointeur : %p\n", upper_base_keymap);
	// ft_printf("test int : %p\n", upper_base_keymap + 2);
	// ft_printf("test int : %i\n", *(upper_base_keymap + 2));
	// term_write_all(STRING, "\n");
	// term_write_all(STRING, "42");


	// keyboard and multi-screen support
	while (true)
	{
		
		uint8_t scancode = keyboard_read_input();
		
			// ft_printf("%p\n", scancode);
			// ft_printf("test int : %i\n", 42);

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
			E0 == true;
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
			// ft_printf("char : %i", keymap[scancode]);
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
