/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:40 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/11 20:38:03 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	length_none(va_list ap, t_meta *fs, long long *cnt)
{
	const int	c = va_arg(ap, int);

	if (fs->minus)
	{
		*cnt += write(1, &c, 1);
		if (fs->width)
			*cnt += put_space_n(fs->width - 1);
	}
	else
	{
		if (fs->width)
			*cnt += put_space_n(fs->width - 1);
		*cnt += write(1, &c, 1);
	}
	return (*cnt);
}

static int	length_l(va_list ap, t_meta *fs, long long *cnt)
{
	const wint_t	c = va_arg(ap, wint_t);

	if (fs->minus)
	{
		*cnt += ft_putwchar_fd(c, 1);
		if (fs->width)
			*cnt += put_space_n(fs->width - 1);
	}
	else
	{
		if (fs->width)
			*cnt += put_space_n(fs->width - 1);
		*cnt += ft_putwchar_fd(c, 1);
	}
	return (*cnt);
}

int			put_specifier_c(va_list ap, t_meta *fs, long long *cnt)
{
	if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		return (length_l(ap, fs, cnt));
	else
		return (length_none(ap, fs, cnt));
}
