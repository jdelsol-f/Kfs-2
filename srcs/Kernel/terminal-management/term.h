/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:36:39 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/03/28 18:10:18 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  TERM_H
# define TERM_H

#include "../kernel.h"

/* INIT */
void term_init();
void *ft_chrset(uint16_t *s, uint16_t c, size_t n);
void *ft_chrcpy(uint16_t *dest, const uint16_t *src, size_t n);
/* SCOLLING */
void term_scrolling();

#endif 