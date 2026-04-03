/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:57:47 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/03 17:43:17 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
};

void outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1" : : "a"(value), "d"(port) : "memory");
};

uint8_t keyboard_read_input()
{
    //if something is on port 0x60
    while(!(inb(0x64) & 1));
    return inb(0x60);
};
