/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:33:16 by jdelsol-          #+#    #+#             */
/*   Updated: 2026/04/17 16:28:31 by jdelsol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static unsigned int	ft_strlen(const char *str)
{
	unsigned int	i;

	str = (char *) str;
	i = 0;
	while (*str != 0)
	{
		i++;
		str++;
	}
	return (i);
}

static int	ft_z_case(void)
{
    term_writestring("0");
	return (1);
}

static int	ft_hexa(unsigned long long nb, char low)
{
	char	unit;
	int		count;

	if (!nb)
		return (0);
	unit = nb % 16;
	count = ft_hexa(nb / 16, low) + 1;
	if (unit > 9)
		unit = unit + 55 + (low * 32);
	else
		unit = unit + 48;
	term_putchar(unit);
	return (count);
}

static int	ft_deci(long long int nb)
{
	char	unit;
	int		count;

	if (!nb)
		return (0);
	unit = nb % 10 + 48;
	count = ft_deci(nb / 10) + 1;
	term_putchar(unit);
	return (count);
}


static int	ft_write_nb(char str, va_list *parameter)
{
	unsigned int	ui;
	long int		i;

	if (str == 'u')
	{
		ui = (unsigned int) va_arg(*parameter, unsigned int);
		if (!ui)
			return (ft_z_case());
		return (ft_deci(ui));
	}
	else
	{
		i = (int) va_arg(*parameter, int);
		if (!i)
			return (ft_z_case());
		else if (i < 0)
		{
			term_writestring("-");
			return (ft_deci(i * -1) + 1);
		}
		return (ft_deci(i));
	}
}

static int	ft_write_char(va_list *parameter)
{
	int	c;

	c = (int) va_arg(*parameter, int);
	term_putchar(c);
	return (1);
}

static int	ft_write_str(va_list *parameter)
{
	char	*c;

	c = (char *) va_arg(*parameter, char *);
	if (!c)
    {
        term_writestring("(null)");
        return (6);
    }
	term_writestring(c);
	return (ft_strlen(c));
}

static int	ft_write_hexa(char str, va_list *parameter)
{
	unsigned long long	ui;

	ui = (unsigned long) va_arg(*parameter, unsigned long);
	if (str == 'p')
	{
		if (!ui)
        {
            term_writestring("(nil)"); 
            return (5);
        }
		term_writestring("0x");
		return (ft_hexa(ui, 1) + 2);
	}
	else if (str == 'h')
	{
		if (!(unsigned short)ui)
			return (ft_z_case());
		return (ft_hexa((unsigned short) ui, 1));
	}
	else
	{
		if (!(unsigned int)ui)
			return (ft_z_case());
		if (str == 'x')
			return (ft_hexa((unsigned int) ui, 1));
		return (ft_hexa((unsigned int) ui, 0));
	}
}

static int	ft_parameter_analysis_system(const char *str, va_list *parameter)
{
	if (*str == '%')
	{
		term_writestring(str);
		return (1);
	}
	else if (*str == 'u' || *str == 'd' || *str == 'i')
		return (ft_write_nb(*str, parameter));
	else if (*str == 'c')
		return (ft_write_char(parameter));
	else if (*str == 's')
		return (ft_write_str(parameter));
	else if (*str == 'x' || *str == 'X' || *str == 'p' || *str == 'h')
		return (ft_write_hexa(*str, parameter));
	else
	{
		term_putchar('%');
		term_putchar(*str);
		return (2);
	}
}

static int	ft_printfbis(const char *str, int i, int count, va_list *parameter)
{
	int	ret;

	while (str[i])
	{
		if (str[i] == '%')
		{
			ret = ft_parameter_analysis_system(str + i + 1, parameter);
			if (ret < 0)
				return (-1);
			count += ret;
			i = i + 2;
		}
		else
		{
		term_putchar(*(str + i));
		i++;
		count++;
		}
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	parameter;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(parameter, str);
	count = ft_printfbis(str, i, count, &parameter);
	va_end(parameter);
    update_cursor(NULL);
	return (count);
}