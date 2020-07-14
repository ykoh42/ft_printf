/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_meta_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:50:31 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/12 16:50:33 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_positional(char **str)
{
	const char	*positional = ft_strchr(*str, '$');

	if (positional)
		*str = (char *)positional;
}

void	set_flag(char **str, t_meta *fs)
{
	while (ft_strchr("-+ #0", **str))
	{
		if (**str == '-')
			fs->minus = '-';
		if (**str == '+')
			fs->plus = '+';
		if (**str == ' ')
			fs->space = ' ';
		if (**str == '#')
			fs->hash = '#';
		if (**str == '0')
			fs->zero = '0';
		(*str)++;
	}
}

void	set_width(char **str, va_list ap, t_meta *fs)
{
	while (ft_strchr("*0123456789", **str))
	{
		if (**str == '*')
			fs->width = va_arg(ap, int);
		if (fs->width < 0)
		{
			fs->minus = '-';
			fs->width = -fs->width;
		}
		if (ft_isdigit(**str))
		{
			fs->width = ft_atoi(*str);
			while (ft_isdigit(**str))
				(*str)++;
			return ;
		}
		(*str)++;
	}
}

void	set_precision(char **str, va_list ap, t_meta *fs)
{
	if (**str == '.')
	{
		(*str)++;
		while (ft_strchr("*0123456789", **str))
		{
			if (**str == '*')
			{
				fs->precision = va_arg(ap, int);
				fs->precision = (fs->precision < 0) ? -1 : fs->precision;
			}
			if (ft_isdigit(**str))
			{
				fs->precision = ft_atoi(*str);
				while (ft_isdigit(**str))
					(*str)++;
				return ;
			}
			(*str)++;
		}
	}
	else
		fs->precision = -1;
}

void	set_length(char **str, t_meta *fs)
{
	if (ft_strnstr(*str, "ll", 2))
	{
		fs->length = "ll";
		*str += 2;
	}
	else if (**str == 'l')
	{
		fs->length = "l";
		*str += 1;
	}
	else if (ft_strnstr(*str, "hh", 2))
	{
		fs->length = "hh";
		*str += 2;
	}
	else if (**str == 'h')
	{
		fs->length = "h";
		*str += 1;
	}
}
