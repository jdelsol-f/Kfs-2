/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_scrolling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:33:31 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 17:39:21 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

#include "terminal.h"

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



#endif