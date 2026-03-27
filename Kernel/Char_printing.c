/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Char_printing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:57:48 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/27 16:16:12 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

int term_col = 0;
int term_row = 0;
uint8_t term_color;
uint16_t* term_buffer = (uint16_t*)VGA_MEMORY;

void term_init()
{
	term_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
	for (int col = 0; col < VGA_WIDTH; col ++)
	{
		for (int row = 0; row < VGA_HEIGHT; row ++)
		{
			const size_t index = (VGA_WIDTH * row) + col;
			term_buffer[index] = vga_entry(' ', term_color);
		} 
	}
}

void term_scrolling()
{
	term_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
	for (int col = 0; col < VGA_WIDTH; col ++)
	{
		for (int row = 1; row < VGA_HEIGHT; row ++)
		{
			const size_t index1 = (VGA_WIDTH * row) + col;
			const size_t index2 = (VGA_WIDTH * (row - 1)) + col;
			term_buffer[index2] = term_buffer[index1];
		} 
	}
	for (int col = 0; col < VGA_WIDTH; col ++)
	{
			const size_t index = (VGA_WIDTH * (VGA_HEIGHT - 1)) + col;
			term_buffer[index] = vga_entry(' ', term_color);
	}
}

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