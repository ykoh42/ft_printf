/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 02:12:08 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/30 22:14:24 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	manage_precision_zero(t_fs *fs)
{
	if (ft_strncmp(fs->num.num, "0", 2) == 0)
	{
		if (fs->specifier == 'o' && fs->hash == '#')
			return ;
		if (fs->specifier != 'p')
			fs->hash = 0;
		if (fs->precision == 0)
		{
			free(fs->num.num);
			fs->num.num = ft_strdup("");
		}
	}
}

void		manage_precision(t_fs *fs)
{
	int		cnt;
	char	*tmp[2];

	if (fs->specifier == 'c' || fs->specifier == '%' || fs->specifier == 'n' ||
		fs->specifier == 's' || fs->specifier == 'e' || fs->specifier == 'f' ||
		fs->specifier == 'g')
		return ;
	manage_precision_zero(fs);
	if ((cnt = fs->precision - ft_strlen(fs->num.num)) > 0)
	{
		tmp[0] = ft_calloc(cnt + 1, sizeof(char));
		ft_memset(tmp[0], '0', cnt);
		tmp[1] = fs->num.num;
		fs->num.num = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
	}
}
