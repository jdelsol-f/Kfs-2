/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:57:13 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 19:53:17 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  INPUTS_H
# define INPUTS_H

#include "../terminal-management/term.h"

/*keyboard keys*/



/* INPUTS & OUTPUTS */
uint8_t inb(uint16_t port);
void    outb(uint16_t port, uint8_t value);
uint8_t keyboard_read_input();

/* CURSOR */
void    enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void    disable_cursor();
void    update_cursor();
uint16_t get_cursor_position(void);

#endif