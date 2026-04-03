/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:57:48 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/03 18:31:59 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_functions.h"

void term_putentryat(char c, uint8_t color, size_t col, size_t row) 
{
	const size_t index = row * VGA_WIDTH + col;
	(TERM_BUFFER)[index] = vga_entry(c, color);
}

static void term_delchar(t_general_struct *data)
{
	if (data->col == 0)
	{
		data->col-=1;
		return;
	}
	for (int col = data->col; col < VGA_HEIGHT * VGA_WIDTH; col ++)
	{
		const size_t index1 = (VGA_WIDTH * data->row) + col;
		const size_t index2 = (VGA_WIDTH * data->row) + (col - 1);
		(TERM_BUFFER)[index2] = (TERM_BUFFER)[index1];
	}
	const size_t index = (VGA_WIDTH * (VGA_HEIGHT - 1)) + VGA_WIDTH - 1;
	(TERM_BUFFER)[index] = vga_entry(' ', data->term_color);
		data->col-=2;
	
}

void term_putchar(char c) 
{
	t_general_struct *data = get_data(NULL);
	if (c == '\b')
		term_delchar(data);
	else if (c != '\n')
		term_putentryat(c, data->term_color, data->col, data->row);
	data->col++;
	if (data->col >= VGA_WIDTH || c == '\n') {
		data->col = 0;
		data->row++;

		if (data->row == VGA_HEIGHT)
		{
			term_scrolling(data->term_color);
			data->row--;
		}
	}
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void term_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		term_putchar(data[i]);
}

void term_writestring(const char* data) 
{
	term_write(data, strlen(data));
}

void term_writeint(int nb)
{
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			term_writestring("-2147483648");
			return ;
		}
		term_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
		term_writeint(nb / 10);
	term_putchar(nb % 10 + '0');

}
 
static char get_hexa_from_unity(unsigned nb)
{
	if ((nb % 16) >= 10)
		return  (char) (nb % 16 - 10 + 'A');
	else
		return  (char) (nb % 16 + '0');
}

static void term_writehex_rec(unsigned hexa)
{
	if (hexa >= 16)
		term_writehex_rec(hexa / 16);
	term_putchar(get_hexa_from_unity(hexa));
}

void term_writehex(unsigned hexa)
{
	term_writestring("0x");
	term_writehex_rec(hexa);
}

void term_write_all(int type, void* things)
{
	// note to add an enum for the switch to make it more readable
	switch (type)
	{
	case STRING:
		term_writestring((char *)things);
		break;
	case INTEGER:
		term_writeint((int)things);
		break;
	case HEXADECIMAL:
		term_writehex((unsigned)things);
		break;
	default:
		break;
	}
	update_cursor();
}