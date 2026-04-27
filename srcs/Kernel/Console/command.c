/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:54:43 by lflandri          #+#    #+#             */
/*   Updated: 2026/04/27 15:40:06 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "../terminal-management/term.h"
#include "../Write_functions/write_functions.h"
#include "../IO/io.h"


void clear(t_general_struct *data)
{
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			(TERM_BUFFER)[index] = vga_entry(' ', data->term_color);
		}
	}

    data->col = 0;
    data->row = 0;
}

void getgdt(t_general_struct *data)
{
	ft_printf("GDT(%p):\n\n", data->my_gdt.addr);	
	ft_printf("start:\n    %h%h   %h%h\n    %h%h   %h%h\n", data->my_gdt.start[0], data->my_gdt.start[1], data->my_gdt.start[2], data->my_gdt.start[3], data->my_gdt.start[4], data->my_gdt.start[5], data->my_gdt.start[6], data->my_gdt.start[7]);
	ft_printf("kernel code:\n    %h%h   %h%h\n    %h %h %h %h\n", data->my_gdt.kernel_code[0], data->my_gdt.kernel_code[1], data->my_gdt.kernel_code[2], data->my_gdt.kernel_code[3], data->my_gdt.kernel_code[4], data->my_gdt.kernel_code[5], data->my_gdt.kernel_code[6], data->my_gdt.kernel_code[7]);
	ft_printf("kernel data:\n    %h%h   %h%h\n    %h %h %h %h\n", data->my_gdt.kernel_data[0], data->my_gdt.kernel_data[1], data->my_gdt.kernel_data[2], data->my_gdt.kernel_data[3], data->my_gdt.kernel_data[4], data->my_gdt.kernel_data[5], data->my_gdt.kernel_data[6], data->my_gdt.kernel_data[7]);
	ft_printf("kernel stack:\n    %h%h   %h%h\n    %h %h %h %h\n", data->my_gdt.kernel_stack[0], data->my_gdt.kernel_stack[1], data->my_gdt.kernel_stack[2], data->my_gdt.kernel_stack[3], data->my_gdt.kernel_stack[4], data->my_gdt.kernel_stack[5], data->my_gdt.kernel_stack[6], data->my_gdt.kernel_stack[7]);
	ft_printf("user code:\n    %h%h   %h%h\n    %h %h %h %h\n", data->my_gdt.user_code[0], data->my_gdt.user_code[1], data->my_gdt.user_code[2], data->my_gdt.user_code[3], data->my_gdt.user_code[4], data->my_gdt.user_code[5], data->my_gdt.user_code[6], data->my_gdt.user_code[7]);
	ft_printf("user data:\n    %h%h   %h%h\n    %h %h %h %h\n", data->my_gdt.user_data[0], data->my_gdt.user_data[1], data->my_gdt.user_data[2], data->my_gdt.user_data[3], data->my_gdt.user_data[4], data->my_gdt.user_data[5], data->my_gdt.user_data[6], data->my_gdt.user_data[7]);
	ft_printf("user stack:\n    %h%h   %h%h\n    %h %h %h %h\n", data->my_gdt.user_stack[0], data->my_gdt.user_stack[1], data->my_gdt.user_stack[2], data->my_gdt.user_stack[3], data->my_gdt.user_stack[4], data->my_gdt.user_stack[5], data->my_gdt.user_stack[6], data->my_gdt.user_stack[7]);
}

void echo(t_general_struct *data, char *buffer)
{
    if (strlen(buffer) <= 5)
    {
        term_putchar('\n');
        return;
    }
    int ind = 5;
    char spe = 0;
    t_bool sep = true;

    while (buffer[ind] != 0)
    {
        if (buffer[ind] == '"')
        {
            if (spe=='"')
                spe = 0;
            else if (spe==0)
                spe = '"';
            else
                term_putchar('"');
            sep = false;
        }
        else if (buffer[ind] == '\'')
        {
            if (spe=='\'')
                spe = 0;
            else if (spe==0)
                spe = '\'';
            else
                term_putchar('\'');
            sep = false;
        }
        else if (buffer[ind] != ' ' || spe)
        {
            sep = false;
            term_putchar(buffer[ind]);
        }
        else if (!sep)
        {
            sep = true;
            term_putchar(' ');
        }
        ind++;
    }
    term_putchar('\n');
}

void reboot()
{
    //launch CPU reset
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    halt();
    
}

void exit()
{
    outw(0x604, 0x2000);    //shutdow emulation qemu
    outw(0x4004, 0x3400);   //shutdow emulation virtualbox
}