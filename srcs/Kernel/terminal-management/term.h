/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:36:39 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/03 18:10:52 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  TERM_H
# define TERM_H

# include "../Colors/colors.h"
# include "../IO/io.h"


/* sys vars */



# ifndef TERM_BUFFER
#  define TERM_BUFFER (uint16_t*)VGA_MEMORY
# endif

/* INIT */
t_general_struct* get_data(t_general_struct *data);
void term_init(t_general_struct *data);
void *ft_chrset(uint16_t *s, uint16_t c, size_t n);
void *ft_chrcpy(uint16_t *dest, const uint16_t *src, size_t n);
/* SCOLLING */
void term_scrolling(uint8_t term_color);

#endif 