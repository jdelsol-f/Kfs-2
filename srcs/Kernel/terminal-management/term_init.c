/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:29:18 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/03 19:19:07 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

t_general_struct* get_data(t_general_struct *data)
{
    static t_general_struct* our_data = NULL;
	if (data)
		our_data = data;
    return our_data;
}

void term_init(t_general_struct *data)
{
	enable_cursor(0, VGA_ROWS);
    
	data->term_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
	data->term_one.term_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
	data->term_two.term_color = vga_entry_color(VGA_COLOR_PINK, VGA_COLOR_YELLOW);

    //multi screens support
	ft_chrset(data->term_one.buffer, vga_entry(' ', data->term_one.term_color), VGA_COLS * VGA_ROWS);
	ft_chrset(data->term_two.buffer, vga_entry(' ', data->term_two.term_color), VGA_COLS * VGA_ROWS);
	data->term_one.col = 0;
	data->term_one.row = 0;
	data->term_two.col = 0;
	data->term_two.row = 0;

	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			(TERM_BUFFER)[index] = vga_entry(' ', data->term_color);
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
