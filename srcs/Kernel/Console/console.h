/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:53:54 by lflandri          #+#    #+#             */
/*   Updated: 2026/04/27 15:29:25 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H
# include "../type.h"




//console function
void	updatePromptPos(t_general_struct *data);
void	execute_command(t_general_struct *data);
void	setpromptready(t_general_struct *data);

//command

void clear(t_general_struct *data);
void getgdt(t_general_struct *data);
void echo(t_general_struct *data, char *buffer);
void reboot();
void exit();




#endif