/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numpad_SCK.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:56:26 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/27 15:00:08 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "../Write_functions/write_functions.h"
#include "../Console/console.h"

void ft_arrows(int *col,  int *row, int direction, t_prompt *prompt)
{
	switch (direction)
	{
	case UP:
		if (*row == prompt->row + 1 && prompt->col >= *col)
			*col = prompt->col;
		if (*row > prompt->row)
			(*row)--;
		break;
		
	case DOWN:
		if (*row < VGA_HEIGHT - 1)
			(*row)++;
		break;
		
	case LEFT:
		if (*row == prompt->row && prompt->col == *col)
			break;
		if (*col > 0)
			(*col)--;
		break;
		
	case RIGHT:
		if  (*col < VGA_WIDTH - 1)
			(*col)++;
		break;
				
	default:
		break;
	}	
}

void ft_page_cursor(int *col,  int *row, int direction, t_prompt *prompt)
{
	switch (direction)
	{
	case PG_UP:
		(*row) = prompt->row;
		if (prompt->col >= *col)
			*col = prompt->col;
		break;
		
	case PG_DOWN:
		(*row) = VGA_HEIGHT - 1;
		break;
		
	case HOME:
		if (*row == prompt->row)
			(*col) = prompt->col;
		else
			(*col) = 0;
		break;
		
	case END:
		(*col) = VGA_WIDTH - 1;
		break;
				
	default:
		break;
	}	
}

bool ft_Numlock(bool shift, bool numlock, uint8_t scancode, t_general_struct *data)
{
	if (!numlock || shift)
	{
		switch (scancode)
		{
		case NUM_7:
			ft_page_cursor(&data->col, &data->row, HOME, &data->term_prompt);
			break;
		case NUM_8:
			ft_arrows(&data->col, &data->row, UP, &data->term_prompt);
			break;
		case NUM_9:
			ft_page_cursor(&data->col, &data->row, PG_UP, &data->term_prompt);
			break;
		case NUM_4:
			ft_arrows(&data->col, &data->row, LEFT, &data->term_prompt);
			break;
		case NUM_6:
			ft_arrows(&data->col, &data->row, RIGHT, &data->term_prompt);
			break;
		case NUM_1:
			ft_page_cursor(&data->col, &data->row, END, &data->term_prompt);
			break;
		case NUM_2:
			ft_arrows(&data->col, &data->row, DOWN, &data->term_prompt);
			break;
		case NUM_3:
			ft_page_cursor(&data->col, &data->row, PG_DOWN, &data->term_prompt);
			break;
		case NUM_DOT:
			term_putchar('\b');
			break;

		default:
			break;
		}
		update_cursor();
		return true;
	}
	return false;
}

void ft_E0_KEY(uint8_t scancode, t_general_struct *data)
{
	switch (scancode)
	{
	case K_HOME:
		ft_page_cursor(&data->col, &data->row, HOME, &data->term_prompt);
		break;
	case K_ARROW_UP:
		ft_arrows(&data->col, &data->row, UP, &data->term_prompt);
		break;
	case K_PG_UP:
		ft_page_cursor(&data->col, &data->row, PG_UP, &data->term_prompt);
		break;
	case K_ARROW_LEFT:
		ft_arrows(&data->col, &data->row, LEFT, &data->term_prompt);
		break;
	case K_ARROW_RIGHT:
		ft_arrows(&data->col, &data->row, RIGHT, &data->term_prompt);
		break;
	case K_END:
		ft_page_cursor(&data->col, &data->row, END, &data->term_prompt);
		break;
	case K_ARROW_DOWN:
		ft_arrows(&data->col, &data->row, DOWN, &data->term_prompt);
		break;
	case K_PG_DOWN:
		ft_page_cursor(&data->col, &data->row, PG_DOWN, &data->term_prompt);
		break;
	case K_PAD_DELETE:
		term_putchar('\b');
		break;
	case K_PAD_SLASH:
		term_putchar('/');
		break;
	case K_PAD_PAD_ENTER:
		execute_command(data);
		break;

	default:
		break;
	}
	update_cursor();
}
