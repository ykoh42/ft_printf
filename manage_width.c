/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 23:32:04 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 02:09:05 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	wcstrlen(const wchar_t *s, ssize_t nbyte)
{
	int	ret;
	int	len;

	ret = 0;
	while (*s)
	{
		len = get_wchar_byte(*s);
		nbyte -= len;
		if (nbyte >= 0)
			ret += len;
		s++;
	}
	return (ret);
}

static int	manage_width_s(t_fs *fs)
{
	int	cnt;

	cnt = 0;
	if (fs->s.none)
		cnt = (fs->precision == -1 ||
				fs->precision > (int)ft_strlen(fs->s.none)) ?
		fs->width - ft_strlen(fs->s.none) : fs->width - fs->precision;
	else
	{
		cnt = (fs->precision == -1 ||
				fs->precision > (int)ft_wcsbyte(fs->s.l)) ?
		fs->width - ft_wcsbyte(fs->s.l) :
		fs->width - wcstrlen(fs->s.l, fs->precision);
	}
	return (cnt);
}

void		manage_width(t_fs *fs)
{
	int	cnt;

	cnt = 0;
	if (fs->specifier == 'n')
		return ;
	else if (fs->specifier == 'c')
	{
		if (fs->c.none)
			cnt = fs->width - 1;
		else
			cnt = fs->width - get_wchar_byte(fs->c.l);
	}
	else if (fs->specifier == 's')
		cnt = manage_width_s(fs);
	else if (fs->specifier == '%')
		cnt = fs->width - 1;
	else
		cnt = fs->width - (ft_strlen(fs->num.sign) + ft_strlen(fs->num.hash)
						+ ft_strlen(fs->num.num));
	fs->padding = (cnt > 0) ? cnt : 0;
}
