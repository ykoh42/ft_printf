/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 23:32:04 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/30 22:16:53 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	manage_plus_space(t_fs *fs)
{
	if (fs->plus)
	{
		if (ft_strncmp(fs->num.num, "nan", 3) == 0)
			return ;
		if (ft_strncmp(fs->num.sign, "", 2) == 0)
			fs->num.sign = "+";
	}
	if (fs->space)
	{
		if (ft_strncmp(fs->num.num, "nan", 3) == 0)
			return ;
		if (ft_strncmp(fs->num.sign, "", 2) == 0)
			fs->num.sign = " ";
	}
}

static void	manage_hash_g(t_fs *fs)
{
	int		i;
	char	*tmp[2];

	tmp[1] = ft_strchr(fs->num.num, 'e');
	i = (tmp[1]) ? tmp[1] - fs->num.num - 1 : ft_strlen(fs->num.num) - 1;
	while (i > 0 && fs->num.num[i] == '0')
		i--;
	if (tmp[1])
	{
		tmp[0] = ft_strndup(fs->num.num, i + 1);
		tmp[0][i] = (tmp[0][i] == '.') ? '\0' : tmp[0][i];
		tmp[1] = ft_strdup(tmp[1]);
		free(fs->num.num);
		fs->num.num = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
	}
	else
	{
		if (ft_strchr(fs->num.num, '.'))
			fs->num.num[i + 1] = '\0';
		fs->num.num[i] = (fs->num.num[i] == '.') ? '\0' : fs->num.num[i];
	}
}

static void	manage_hash_e(t_fs *fs)
{
	char	*tmp[2];

	if (!ft_strchr(fs->num.num, '.'))
	{
		tmp[0] = ft_strndup(fs->num.num,
							ft_strchr(fs->num.num, 'e') - fs->num.num);
		tmp[1] = ft_strdup(ft_strchr(fs->num.num, 'e'));
		free(fs->num.num);
		fs->num.num = ft_strjoin(tmp[0], ".");
		free(tmp[0]);
		tmp[0] = fs->num.num;
		fs->num.num = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
	}
}

static void	manage_hash(t_fs *fs)
{
	char	*tmp[2];

	if (fs->specifier == 'o' && fs->num.num[0] != '0')
		fs->num.hash = "0";
	else if (fs->specifier == 'x' || fs->specifier == 'p')
		fs->num.hash = "0x";
	else if (fs->specifier == 'X')
		fs->num.hash = "0X";
	else if (fs->specifier == 'f' || fs->specifier == 'g')
	{
		if (!ft_strchr(fs->num.num, '.'))
		{
			tmp[0] = fs->num.num;
			fs->num.num = ft_strjoin(fs->num.num, ".");
			free(tmp[0]);
		}
	}
	else if (fs->specifier == 'e')
		manage_hash_e(fs);
}

void		manage_flags(t_fs *fs)
{
	if (fs->specifier == 'n' || fs->specifier == '%' || fs->specifier == 'c' ||
		fs->specifier == 's')
		return ;
	if (fs->hash)
		manage_hash(fs);
	if (!fs->hash && fs->specifier == 'g')
		manage_hash_g(fs);
	if (fs->plus)
		manage_plus_space(fs);
	if (fs->space)
		manage_plus_space(fs);
}
