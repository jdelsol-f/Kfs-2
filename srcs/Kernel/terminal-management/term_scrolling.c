/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_scrolling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:33:31 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 19:47:24 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

#include "term.h"
#include "../type.h"

void term_scrolling(uint8_t term_color)
{
	for (int col = 0; col < VGA_WIDTH; col ++)
	{
		for (int row = 1; row < VGA_HEIGHT; row ++)
		{
			const size_t index1 = (VGA_WIDTH * row) + col;
			const size_t index2 = (VGA_WIDTH * (row - 1)) + col;
			(TERM_BUFFER)[index2] = (TERM_BUFFER)[index1];
		} 
	}
	for (int col = 0; col < VGA_WIDTH; col ++)
	{
			const size_t index = (VGA_WIDTH * (VGA_HEIGHT - 1)) + col;
			(TERM_BUFFER)[index] = vga_entry(' ', term_color);
	}
}



#endif