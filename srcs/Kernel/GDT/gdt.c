/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:40:48 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/26 13:21:10 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gdt.h"



void GetGdt(t_gdt *gdt)
{
    extern uint8_t gdt_start;

    gdt->addr =          NULL;
    gdt->start =        NULL;
    gdt->kernel_code =  NULL;
    gdt->kernel_data =  NULL;
    gdt->kernel_stack = NULL;
    gdt->user_code =    NULL;
    gdt->user_data =    NULL;
    gdt->user_stack =   NULL;
    
    gdt->addr =          &gdt_start;
    gdt->start =        gdt->addr;
    gdt->kernel_code =  &gdt->addr[8];
    gdt->kernel_data =  &gdt->addr[16];
    gdt->kernel_stack = &gdt->addr[24];
    gdt->user_code =    &gdt->addr[32];
    gdt->user_data =    &gdt->addr[40];
    gdt->user_stack =   &gdt->addr[48];

    // uint8_t *addr =         &gdt_start;
    // uint16_t *lol =         &gdt_start;
    // uint8_t *start =        &addr[0];
    // uint8_t *kernel_code =  &addr[8];
    // uint8_t *kernel_data =  &addr[16];
    // uint8_t *kernel_stack = &addr[24];
    // uint8_t *user_code =    &addr[32];
    // uint8_t *user_data =    &addr[40];
    // uint8_t *user_stack =   &addr[48];

    // for (int i = 0; i < 48; i++)
    //     ft_printf("- (%x) ", gdt_start[i]);	
	// ft_printf("start:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", start[0], start[1], start[2], start[3], start[4], start[5], start[6], start[7]);
	// ft_printf("kernel code:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", kernel_code[0], kernel_code[1], kernel_code[2], kernel_code[3], kernel_code[4], kernel_code[5], kernel_code[6], kernel_code[7]);
	// ft_printf("kernel data:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", kernel_data[0], kernel_data[1], kernel_data[2], kernel_data[3], kernel_data[4], kernel_data[5], kernel_data[6], kernel_data[7]);
	// ft_printf("kernel stack:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", kernel_stack[0], kernel_stack[1], kernel_stack[2], kernel_stack[3], kernel_stack[4], kernel_stack[5], kernel_stack[6], kernel_stack[7]);
	// ft_printf("user code:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", user_code[0], user_code[1], user_code[2], user_code[3], user_code[4], user_code[5], user_code[6], user_code[7]);
	// ft_printf("user data:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", user_data[0], user_data[1], user_data[2], user_data[3], user_data[4], user_data[5], user_data[6], user_data[7]);
	// ft_printf("user stack:\n    -%h -%h -%h -%h\n    -%h -%h -%h -%h\n", user_stack[0], user_stack[1], user_stack[2], user_stack[3], user_stack[4], user_stack[5], user_stack[6], user_stack[7]);
	
}

