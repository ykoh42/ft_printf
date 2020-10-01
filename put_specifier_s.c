/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:46:13 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/05 00:07:21 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				get_wchar_byte(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x1FFFFF)
		return (4);
	else if (c <= 0x3FFFFFF)
		return (5);
	else
		return (6);
}

int				ft_wcsbyte(const wchar_t *s)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		ret += get_wchar_byte(*s);
		s++;
	}
	return (ret);
}

static int		put_wcstr(const wchar_t *s, ssize_t nbyte)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		nbyte -= get_wchar_byte(*s);
		if (nbyte >= 0)
			ret += ft_putwchar_fd(*s, 1);
		s++;
	}
	return (ret);
}

static void		put_specifier_s_flag_minus(t_fs fs, int *ret)
{
	if (fs.s.none)
	{
		*ret += (fs.precision == -1 ||
				fs.precision > (int)ft_strlen(fs.s.none)) ?
		put_space(fs) + write(1, fs.s.none, ft_strlen(fs.s.none)) :
		put_space(fs) + write(1, fs.s.none, fs.precision);
	}
	else
	{
		*ret += (fs.precision == -1 ||
				fs.precision > (int)ft_wcsbyte(fs.s.l)) ?
		put_space(fs) + put_wcstr(fs.s.l, ft_wcsbyte(fs.s.l)) :
		put_space(fs) + put_wcstr(fs.s.l, fs.precision);
	}
}

int				put_specifier_s(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.minus)
	{
		if (fs.s.none)
		{
			ret += (fs.precision == -1 ||
					fs.precision > (int)ft_strlen(fs.s.none)) ?
			write(1, fs.s.none, ft_strlen(fs.s.none)) + put_space(fs) :
			write(1, fs.s.none, fs.precision) + put_space(fs);
		}
		else
		{
			ret += (fs.precision == -1 ||
					fs.precision > (int)ft_wcsbyte(fs.s.l)) ?
			put_wcstr(fs.s.l, ft_wcsbyte(fs.s.l)) + put_space(fs) :
			put_wcstr(fs.s.l, fs.precision) + put_space(fs);
		}
	}
	else
		put_specifier_s_flag_minus(fs, &ret);
	return (ret);
}
