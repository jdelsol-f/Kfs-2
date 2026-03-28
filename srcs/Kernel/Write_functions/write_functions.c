/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write-functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:57:48 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 17:52:47 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_functions.h"

void term_putentryat(char c, uint8_t color, size_t col, size_t row) 
{
	const size_t index = row * VGA_WIDTH + col;
	term_buffer[index] = vga_entry(c, color);
}

void term_putchar(char c) 
{
	term_putentryat(c, term_color, term_col, term_row);
	term_col++;
	if (term_col >= VGA_WIDTH || c == '\n') {
		term_col = 0;
		term_row++;

		if (term_row == VGA_HEIGHT)
		{
			// term_row = 0;
			term_scrolling();
			term_row--;
			//note to add, for the multi-screen, multi-buffer for each screen that works as extention of the last one
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
	update_cursor(term_col, term_row);
}