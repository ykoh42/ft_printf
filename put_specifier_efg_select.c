/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_efg_select.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:41:41 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/16 04:58:24 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*select_ret_hash(t_meta *fs, char *ret)
{
	char	*p;

	if (!fs->hash && fs->specifier == 'f')
	{
		p = ret + ft_strlen(ret) - 1;
		while (p != ret && *(p + 1) != '.' && (*p == '0' || *p == '.'))
			p--;
		p = ft_strndup(ret, p - ret + 1);
		free(ret);
		ret = p;
	}
	if (ft_strncmp(ret, "-", 2) == 0)
		ret = ft_strjoin_free(ret, ft_strdup("0"));
	return (ret);
}

static char	*select_ret_process(double n, t_meta *fs, const char *e)
{
	int		exp;
	char	*ret;

	exp = ft_atoi(ft_strchr(e, 'e') + 1);
	if (ft_strncmp(e, "9.9e", 4) == 0 || ft_strncmp(e, "-9.9e", 5) == 0)
	{
		exp++;
		fs->specifier = 'e';
	}
	if (exp >= -4 && exp < fs->precision)
	{
		fs->specifier = 'f';
		fs->precision = fs->precision - 1 - exp;
		ret = ft_dtoa(n, fs->precision, fs->specifier);
	}
	else
	{
		fs->specifier = 'e';
		fs->precision = fs->precision - 1;
		ret = ft_dtoa(n, fs->precision, fs->specifier);
		ret = e_correction(ret, fs->precision, 'g');
	}
	return (ret);
}

const char	*select_ret(va_list ap, t_meta *fs)
{
	const double	n = va_arg(ap, double);
	const char		*e = ft_dtoa(n, fs->precision, 'e');
	char			*ret;

	if (!e)
		return (0);
	if (fs->precision == 0)
		fs->precision = 1;
	if (fs->precision == -1)
		fs->precision = 6;
	if (ft_strnstr(e, "nan", 4) || ft_strnstr(e, "inf", 4))
		return (e);
	ret = select_ret_process(n, fs, e);
	ret = select_ret_hash(fs, ret);
	free((char *)e);
	return (ret);
}
