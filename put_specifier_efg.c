/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_efg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/16 04:55:15 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_efg(t_meta *fs, char *efg)
{
	t_write	func;
	int		ret;
	size_t	efg_len;

	if (*efg == '-')
		efg++;
	efg_len = ft_strlen(efg);
	func = (fs->minus) ? write : without_write;
	ret = 0;
	ret += func(1, efg, efg_len);
	return (ret);
}

static char	*set_hash_flag(t_meta *fs, char *efg)
{
	char	*tmp[2];

	if (fs->specifier == 'f' && fs->hash && !ft_strchr(efg, '.'))
		efg = ft_strjoin_free(efg, ft_strdup("."));
	else if (fs->specifier == 'e' && fs->hash && !ft_strchr(efg, '.'))
	{
		tmp[0] = ft_calloc(ft_strchr(efg, 'e') - efg + 2, sizeof(char));
		ft_strlcat(tmp[0], efg, ft_strchr(efg, 'e') - efg + 1);
		tmp[0][ft_strlen(tmp[0])] = '.';
		tmp[1] = ft_strdup(ft_strchr(efg, 'e'));
		free(efg);
		efg = ft_strjoin_free(tmp[0], tmp[1]);
	}
	return (efg);
}

static int	put_specifier_efg_process(t_meta *fs, long long *cnt, char *efg)
{
	int		width_cnt;

	efg = set_hash_flag(fs, efg);
	if (fs->minus)
	{
		width_cnt = put_sign(fs, efg) + put_efg(fs, efg);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = put_sign(fs, efg) + put_efg(fs, efg);
		fs->minus = '-';
		if (fs->width && fs->width > width_cnt)
			*cnt += (fs->zero &&
			!((ft_strnstr(efg, "inf", 4)) || (ft_strnstr(efg, "nan", 4)))) ?
				put_sign(fs, efg) + put_zero_n(fs->width - width_cnt) :
				put_space_n(fs->width - width_cnt) + put_sign(fs, efg);
		else
			*cnt += put_sign(fs, efg);
		*cnt += put_efg(fs, efg);
	}
	free(efg);
	return (*cnt);
}

int			put_specifier_efg(va_list ap, t_meta *fs, long long *cnt)
{
	char	*efg;

	if (fs->specifier == 'f' || fs->specifier == 'e')
	{
		if (!(efg = ft_dtoa(va_arg(ap, double), fs->precision, fs->specifier)))
			return (-1);
	}
	else
	{
		if (!(efg = (char *)select_ret(ap, fs)))
			return (-1);
	}
	return (put_specifier_efg_process(fs, cnt, efg));
}
