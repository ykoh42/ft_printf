/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_meta_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:12:21 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/23 19:59:42 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_flag(const char *restrict *format, t_meta *fs)
{
	while (**format && ft_strchr("-+ #0", **format))
	{
		if (**format == '-')
			fs->minus = '-';
		if (**format == '+')
			fs->plus = '+';
		if (**format == ' ')
			fs->space = ' ';
		if (**format == '#')
			fs->hash = '#';
		if (**format == '0')
			fs->zero = '0';
		(*format)++;
	}
}

void	set_width(const char *restrict *format, va_list ap, t_meta *fs)
{
	while (**format && ft_strchr("*0123456789", **format))
	{
		if (**format == '*')
			fs->width = va_arg(ap, int);
		if (ft_isdigit(**format))
		{
			fs->width = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
			return ;
		}
		(*format)++;
	}
}

void	set_precision(const char *restrict *format, va_list ap, t_meta *fs)
{
	if (**format == '.')
	{
		(*format)++;
		while (ft_strchr("*0123456789", **format))
		{
			if (**format == '*')
				fs->precision = va_arg(ap, int);
			if (ft_isdigit(**format))
			{
				fs->precision = ft_atoi(*format);
				while (ft_isdigit(**format))
					(*format)++;
				return ;
			}
			(*format)++;
		}
	}
	else
		fs->precision = -1;
}

void	set_length(const char *restrict *format, t_meta *fs)
{
	while (**format && ft_strchr("lh", **format))
	{
		if (ft_strnstr(*format, "ll", 2))
		{
			fs->length = "ll";
			*format += 2;
			return ;
		}
		if (**format == 'l')
		{
			fs->length = "l";
			*format += 1;
		}
		if (ft_strnstr(*format, "hh", 2))
		{
			fs->length = "hh";
			*format += 2;
			return ;
		}
		if (**format == 'h')
		{
			fs->length = "h";
			*format += 1;
		}
	}
}

void	set_specifier(const char *restrict *format, t_meta *fs)
{
	if (**format && ft_strchr("nfgecspdiuxX%", **format))
		fs->specifier = **format++;
}
