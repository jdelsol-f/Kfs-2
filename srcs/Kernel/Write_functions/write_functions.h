/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:50:43 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 18:06:46 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_FUNCTIONS_H
# define WRITE_FUNCTIONS_H

#include "../kernel.h"

enum write_switch
{
	STRING = 42,
	INTEGER = 43,
	HEXADECIMAL = 44
};

/* FUNCS */
void term_write_all(int type, void* things);
void term_writehex(unsigned hexa);
static void term_writehex_rec(unsigned hexa);
static char get_hexa_from_unity(unsigned nb);
void term_writeint(int nb);
void term_writestring(const char* data);
void term_write(const char* data, size_t size);
size_t strlen(const char* str);
void term_putchar(char c);
void term_putentryat(char c, uint8_t color, size_t col, size_t row);

#endif