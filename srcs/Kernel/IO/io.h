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

typedef struct  e_key
{
    c,
    is_unprintable,
    *prt
}   t_key;

enum Unprintable_keys_values{
    LEFT_CTRL = 0x1D,
    LEFT_SHIFT = 0x2A,
    RIGHT_SHIFT = 0x36,
    LEFT_ALT = 0x38,
    CAPSLOCK = 0x3A,
    F1 = 0x3B, F2, F3, F4, F5, F6, F7, F8, F9, F10,
    NUMLOCK = 0x45,
    SCROLl_LOCK = 0x46,
    F11 = 0x57, F12,

};

const char lower_base_keymap[] = 
{
    '\0', '~',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-',
    '=',
    '\b',
    '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',  '\n',
    ' ', //ctrl
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	' ', // Left shift
	'\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    ' ', //right shift
    '*' /* numpad '*' */,
	' ', // left alt
	' ', //space
	' ', //capslocks in
    ' ',/*F1*/ ' ',/* F2*/ ' ',/* F3*/ ' ',/* F4*/ ' ',/* F5*/ ' ',/* F6*/ ' ',/* F7*/ ' ',/* F8*/ ' ',/* F9*/ ' ',/* F10*/
    ' ',// number lock ' ',//  scroll lock
    '7', '8', '9',  '-', '4', '5', '6', '+', '1', '2', '3', '0', // all numpad
    '.',
    ' ',// None
    ' ',// None
    ' ',// None
    ' ',// F11
    ' ',// F12
};

const char upper_base_keymap[] = 
{
    '\0', ' ' /* ESCAPE */,
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
	'_',
    '+',
    '\b',
    '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',  '\n',
    ' ', //ctrl
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
	' ', // Left shift
	'|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    ' ', //right shift
    '*' /* numpad '*' */,
	' ', // left alt
	' ',
	' ', //capslocks in
    ' ',/*F1*/ ' ',/* F2*/ ' ',/* F3*/ ' ',/* F4*/ ' ',/* F5*/ ' ',/* F6*/ ' ',/* F7*/ ' ',/* F8*/ ' ',/* F9*/ ' ',/* F10*/
    ' ',// number lock ' ',//  scroll lock
    '7', '8', '9',  '-', '4', '5', '6', '+', '1', '2', '3', '0', // all numpad
    '.',
    ' ',// None
    ' ',// None
    ' ',// None
    ' ',// F11
    ' ',// F12
};

const char capslock_base_keymap[] = 
{
    '\0', '~',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-',
    '=',
    '\b',
    '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']',  '\n',
    ' ', //ctrl
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
	' ', // Left shift
	'\\',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',
    ' ', //right shift
    '*' /* numpad '*' */,
	' ', // left alt
	' ',
	' ', //capslocks in
    ' ',/*F1*/ ' ',/* F2*/ ' ',/* F3*/ ' ',/* F4*/ ' ',/* F5*/ ' ',/* F6*/ ' ',/* F7*/ ' ',/* F8*/ ' ',/* F9*/ ' ',/* F10*/
    ' ',// number lock ' ',//  scroll lock
    '7', '8', '9',  '-', '4', '5', '6', '+', '1', '2', '3', '0', // all numpad
    '.',
    ' ',// None
    ' ',// None
    ' ',// None
    ' ',// F11
    ' ',// F12
};

#endif