/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:53:51 by lflandri          #+#    #+#             */
/*   Updated: 2026/04/27 14:40:51 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console.h"
#include "../Write_functions/write_functions.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*s1_bis;
	char	*s2_bis;

	s1_bis = (char *) s1;
	s2_bis = (char *) s2;
	if (n-- == 0)
		return (0);
	while (*s1_bis == *s2_bis && *s1_bis && n)
	{
		s1_bis++;
		s2_bis++;
		n--;
	}
	return (*(unsigned char *)s1_bis - *(unsigned char *)s2_bis);
}

void	updatePromptPos(t_general_struct *data)
{
	data->term_prompt.col = data->col;
	data->term_prompt.row = data->row;
}

static void convertColortextToNoColorText(int startX, int startY, char *buffer)
{
	int buffer_index = 0;
	char *reading_start = TERM_BUFFER;

	for (size_t i = ((VGA_WIDTH * startY) + startX) * 2 ; i < (80 * 25 * 2); i+=2)
	{
		buffer[buffer_index] = reading_start[i];
		buffer_index++;
	}
	for (size_t i = buffer_index - 1; i >= 0; i--)
	{
		if (buffer[i] != ' ')
			break;
		buffer[i] = '\0';
	}
}

void	execute_command(t_general_struct *data)
{
	char buffer[2125];
	convertColortextToNoColorText(data->term_prompt.col, data->term_prompt.row, buffer);
	term_putchar('\n');
	if (!ft_strncmp("clear", buffer, 5) && (buffer[5] == '\0' || buffer[5] == ' '))
		clear(data);
	else if (!ft_strncmp("getgdt", buffer, 6) && (buffer[6] == '\0' || buffer[6] == ' '))
		getgdt(data);
	else if (!ft_strncmp("echo", buffer, 4) && (buffer[4] == '\0' || buffer[4] == ' '))
		echo(data, buffer);
	else
		ft_printf("Unknow command, please try again.\n");
	
	setpromptready(data);
}

void	setpromptready(t_general_struct *data)
{
	term_writestring(CONSOLEPROMT);
	update_cursor();
	updatePromptPos(data);
}