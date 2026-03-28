/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:57:43 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 17:24:45 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

uint8_t term_setcolor(uint8_t color) 
{
	uint8_t term_color = color;

    return (term_color);
}
