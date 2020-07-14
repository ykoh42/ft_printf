/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils_wchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:46:13 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/12 16:03:29 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_wchar_byte(wchar_t c)
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

int				put_wcstr(const wchar_t *s, ssize_t nbyte, t_meta *fs)
{
	int	ret;

	ret = 0;
	if (fs->minus)
	{
		while (*s)
		{
			nbyte -= get_wchar_byte(*s);
			if (nbyte >= 0)
				ret += ft_putwchar_fd(*s, 1);
			s++;
		}
	}
	else
	{
		while (*s)
		{
			nbyte -= get_wchar_byte(*s);
			if (nbyte >= 0)
				ret += get_wchar_byte(*s);
			s++;
		}
	}
	return (ret);
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
