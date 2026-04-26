/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:41:03 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/26 11:48:15 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GDT_H
# define GDT_H

#include "../type.h"

typedef struct s_gdt
{
    uint8_t *addr;
    uint8_t *start;
    uint8_t *kernel_code;
    uint8_t *kernel_data;
    uint8_t *kernel_stack;
    uint8_t *user_code;
    uint8_t *user_data;
    uint8_t *user_stack;
    
}   t_gdt;



void GetGdt(t_gdt *gdt);

#endif