/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/20 21:17:57 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_u(t_meta *fs, char *u)
{
	t_write	f;
	int		ret;
	size_t	u_len;

	if (fs->precision == 0 && *u == '0')
		return (fs->precision);
	u_len = ft_strlen(u);
	f = (fs->minus) ? write : without_write;
	ret = 0;
	if (fs->precision != -1 && (size_t)fs->precision > u_len)
		ret = (fs->minus) ?
			put_zero_n(fs->precision - u_len) : fs->precision - u_len;
	ret += f(1, u, u_len);
	return (ret);
}

static void	*type_new_u(va_list ap, t_meta *fs)
{
	if (fs->length != NULL && ft_strncmp(fs->length, "ll", 2) == 0)
		return (ft_utoa((unsigned long long int)va_arg(ap,
												unsigned long long int)));
	else if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		return (ft_utoa((unsigned long int)va_arg(ap, unsigned long int)));
	else if (fs->length != NULL && ft_strncmp(fs->length, "hh", 2) == 0)
		return (ft_utoa((unsigned char)va_arg(ap, unsigned int)));
	else if (fs->length != NULL && ft_strncmp(fs->length, "h", 2) == 0)
		return (ft_utoa((unsigned short int)va_arg(ap, unsigned int)));
	else
		return (ft_utoa((unsigned int)va_arg(ap, unsigned int)));
}

int			put_specifier_u(va_list ap, t_meta *fs, long long *cnt)
{
	char	*u;
	int		width_cnt;

	if (!(u = type_new_u(ap, fs)))
		return (-1);
	if (fs->minus)
	{
		width_cnt = put_u(fs, u);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = put_u(fs, u);
		if (fs->width && fs->width > width_cnt)
			*cnt += (fs->zero && fs->precision == -1) ?
					put_zero_n(fs->width - width_cnt) :
					put_space_n(fs->width - width_cnt);
		fs->minus = '-';
		*cnt += put_u(fs, u);
	}
	free(u);
	return (*cnt);
}
