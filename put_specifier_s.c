/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:30:28 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/21 17:11:54 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			put_specifier_s(va_list ap, t_meta *fs, long long *cnt)
{
	int		ret;
	void	*s;

	if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		s = va_arg(ap, wchar_t *);
	else
		s = va_arg(ap, char *);
	if (fs->minus)
	{
		ret = 0;
		ret += (fs->precision == -1 || (size_t)fs->precision > ft_strlen(s)) ?
				write(1, s, ft_strlen(s)) : write(1, s, fs->precision);
		if (fs->width && fs->width > ret)
			*cnt += put_space_n(fs->width - ret);
		*cnt += ret;
	}
	else
	{
		ret = (fs->precision == -1 || (size_t)fs->precision > ft_strlen(s)) ?
				ft_strlen(s) : fs->precision;
		if (fs->width && fs->width > ret)
			*cnt += put_space_n(fs->width - ret);
		*cnt += write(1, s, ret);
	}
	return (*cnt);
}
