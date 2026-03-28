/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:29:18 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 18:04:52 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"


volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

int term_col = 0;
int term_row = 0;
uint8_t term_color;
uint16_t* term_buffer = (uint16_t*)VGA_MEMORY;

void term_init()
{
	enable_cursor(0, VGA_ROWS);
    
	term_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);

    //multi screens support
	ft_chrset(term_one.buffer, vga_entry(' ', term_color), VGA_COLS * VGA_ROWS);
	ft_chrset(term_two.buffer, vga_entry(' ', term_color), VGA_COLS * VGA_ROWS);
	term_one.col = 0;
	term_one.row = 0;
	term_two.col = 0;
	term_two.row = 0;

	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			term_buffer[index] = vga_entry(' ', term_color);
		} 
	}
}

void    *ft_chrcpy(uint16_t *dest, const uint16_t *src, size_t n)
{
    uint16_t    *dest_bis;
    uint16_t    *src_bis;

    if (!dest && !src)
        return (dest);
    src_bis = (uint16_t *) src;
    dest_bis = (uint16_t *) dest;
    while (0 != n)
    {
        --n;
        *(dest_bis + n) = *(src_bis + n);
    }
    return (dest);
}

void    *ft_chrset(uint16_t *s, uint16_t c, size_t n)
{
    uint16_t    *s_bis;

    s_bis = s;
    while (0 != n)
    {
        --n;
        *(s_bis + n) = c;
    }
    return (s);
}
