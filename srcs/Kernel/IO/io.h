/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:57:13 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/03 18:51:39 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  IO_H
# define IO_H

#include "../terminal-management/term.h"

/*keyboard keys*/
extern const char lower_base_keymap[89];
extern const char upper_base_keymap[89];

/* INPUTS & OUTPUTS */
uint8_t inb(uint16_t port);
void    outb(uint16_t port, uint8_t value);
uint8_t keyboard_read_input();

/* CURSOR */
void    enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void    disable_cursor();
void    update_cursor();
uint16_t get_cursor_position(void);

enum keys_values{
    CTRL = 0x1D,
    LEFT_SHIFT = 0x2A,
    RIGHT_SHIFT = 0x36,
    LEFT_ALT = 0x38,
    CAPSLOCK = 0x3A,
    F1 = 0x3B, F2, F3, F4, F5, F6, F7, F8, F9, F10,
    NUMLOCK = 0x45,
    SCROLl_LOCK = 0x46,
    F11 = 0x57, F12,
    LEFT_SHIFT_RELEASE = 0xAA,
    RIGHT_SHIFT_RELEASE = 0xB6,
    NUM_7  = 0x47,
    NUM_8  = 0x48,
    NUM_9  = 0x49,

    NUM_4  = 0x4B,
    NUM_5  = 0x4C,
    NUM_6  = 0x4D,
    
    NUM_1  = 0x4F,
    NUM_2  = 0x50,
    NUM_3  = 0x51,
    NUM_0  = 0x52,
    NUM_DOT  = 0x53
    
};


// char keymap[] = 
// {
//     [0x00] = '\0',
//     [0x01] = ' ' /* ESCAPE */,
//     [0x02] = '1',
// 	[0x03] = '2',
// 	[0x04] = '3',
//     [0x05] = '4',
//     [0x06] = '5',
//     [0x07] = '6',
// 	[0x08] = '7',
//     [0x09] = '8',
//     [0x0A] = '9',
//     [0x0B] = '0',
// 	[0x0C] = '-',
//     [0x0D] = '=',
//     [0x0E] = '\b',
//     [0x0F] = '\t',
// 	[0x10] = 'q',
//     [0x11] = 'w',
//     [0x12] = 'e',
//     [0x13] = 'r',
// 	[0x14] = 't',
//     [0x15] = 'y',
//     [0x16] = 'u',
//     [0x17] = 'i',
// 	[0x18] = 'o',
//     [0x19] = 'p',
//     [0x1A] = '[',
//     [0x1B] = ']',
//     [0x1C] = '\n',
//     [0x1D] = ' ', // left ctrl
//     [0x1E] = 'a',
//     [0x1F] = 's',
//     [0x20] = 'd',
//     [0x21] = 'f',
// 	[0x22] = 'g',
// 	[0x23] = 'h',
// 	[0x24] = 'j',
// 	[0x25] = 'k',
// 	[0x26] = 'l',
// 	[0x27] = ';',
// 	[0x28] = '\'',
// 	[0x29] = '`',
// 	[0x2A] = ' ', //shift in
// 	[0x2B] = '\\',
// 	[0x2C] = 'z',
// 	[0x2D] = 'x',
// 	[0x2E] = 'c',
// 	[0x2F] = 'v',
// 	[0x30] = 'b',
// 	[0x31] = 'n',
// 	[0x32] = 'm',
// 	[0x33] = ',',
// 	[0x34] = '.',
// 	[0x35] = '/',
// 	[0x36] = ' ',// right shift
// 	[0x37] = '*',
// 	[0x38] = ' ',// left alt
// 	[0x39] = ' ',// space
// 	[0x3A] = ' ',// capslocks in
// 	[0x3B] = ' ',// F1
// 	[0x3C] = ' ',// F2
// 	[0x3D] = ' ',// F3
// 	[0x3E] = ' ',// F4
// 	[0x3F] = ' ',// F5
// 	[0x40] = ' ',// F6
// 	[0x41] = ' ',// F7
// 	[0x42] = ' ',// F8
// 	[0x43] = ' ',// F9
// 	[0x44] = ' ',// F10
// 	[0x45] = ' ',// number lock
// 	[0x46] = ' ',//  scroll lock
// 	[0x47] = '7',
// 	[0x48] = '8',
// 	[0x49] = '9', 
// 	[0x4A] = '-',
// 	[0x4B] = '4',
// 	[0x4C] = '5',
// 	[0x4D] = '6',
// 	[0x4E] = '+',
// 	[0x4F] = '1',
// 	[0x50] = '2',
// 	[0x51] = '3',
// 	[0x52] = '0',
// 	[0x53] = '.',
// 	[0x54] = ' ',// None
// 	[0x55] = ' ',// None
// 	[0x56] = '.',// None
// 	[0x57] = ' ',// F11
// 	[0x58] = ' ',// F12
// };

#endif