/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:33:22 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 17:33:23 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#include "../kernel.c"

int        ft_printf(const char *str, ...);

typedef __builtin_va_list	va_list;

# define	va_start(ap, last)	__builtin_va_start(ap, last)
# define	va_arg(ap, type)	__builtin_va_arg(ap, type)
# define	va_copy(dest, src)	__builtin_va_copy(dest, src)
# define	va_end(ap)			__builtin_va_end(ap)

#endif