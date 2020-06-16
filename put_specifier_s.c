/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:30:28 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/23 17:45:43 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			put_specifier_s(va_list ap, t_meta *fs, long long *cnt)
{
	int		s_len;
	void	*s;

	if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		s = va_arg(ap, wchar_t *);
	else
		s = va_arg(ap, char *);
	if (fs->minus)
	{
		s_len = 0;
		s_len += (fs->precision == -1 || (size_t)fs->precision > ft_strlen(s)) ?
				write(1, s, ft_strlen(s)) : write(1, s, fs->precision);
		if (fs->width && fs->width > s_len)
			*cnt += put_space_n(fs->width - s_len);
		*cnt += s_len;
	}
	else
	{
		s_len = (fs->precision == -1 || (size_t)fs->precision > ft_strlen(s)) ?
				ft_strlen(s) : fs->precision;
		if (fs->width && fs->width > s_len)
			*cnt += put_space_n(fs->width - s_len);
		*cnt += write(1, s, s_len);
	}
	return (*cnt);
}
