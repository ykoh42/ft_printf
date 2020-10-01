/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 19:43:57 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/14 23:56:01 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	move_index(int integer[], int fractional[], int exp)
{
	int i;

	if (exp >= 0)
	{
		ft_memmove(fractional, fractional + exp, sizeof(int) * (1023 - exp));
		ft_memmove(fractional + (1023 - exp), integer, sizeof(int) * (exp));
		integer[0] = integer[exp];
		i = exp;
		while (i > 0)
			integer[i--] = 0;
	}
	else
	{
		integer[0] = fractional[1023 + exp];
		ft_memmove(fractional - exp, fractional, sizeof(int) * (1023 + exp));
		ft_bzero(fractional, sizeof(int) * -exp);
	}
}

static int	get_exp(int integer[], int fractional[])
{
	int	i;

	i = 308;
	while (i >= 0)
	{
		if (integer[i])
			break ;
		i--;
	}
	if (i != -1)
		return (i);
	i = 1022;
	while (i >= 0)
	{
		if (fractional[i])
			break ;
		i--;
	}
	if (i != -1)
		return (i - 1023);
	return (0);
}

static int	e_conversion(int integer[], int fractional[], int precision)
{
	int		exp;

	exp = get_exp(integer, fractional);
	move_index(integer, fractional, exp);
	rounding(integer, fractional, precision);
	while (get_exp(integer, fractional))
	{
		move_index(integer, fractional, get_exp(integer, fractional));
		rounding(integer, fractional, precision);
		exp++;
	}
	return (exp);
}

char		*get_str_e(union u_double std,
					int integer[], int fractional[], int precision)
{
	char	*tmp[10];
	int		exp;
	int		i;

	exp = e_conversion(integer, fractional, precision);
	tmp[0] = get_integer(integer);
	tmp[1] = (std.ieee.negative) ? ft_strjoin("-", tmp[0]) :
									ft_strjoin("", tmp[0]);
	tmp[2] = get_fractional(fractional, precision);
	tmp[3] = (ft_strlen(tmp[2])) ? ft_strjoin(".", tmp[2]) :
								ft_strdup("");
	tmp[4] = ft_strjoin(tmp[1], tmp[3]);
	tmp[5] = ft_strjoin(tmp[4], "e");
	tmp[6] = (exp < 0) ? ft_strjoin(tmp[5], "-") : ft_strjoin(tmp[5], "+");
	exp = (exp < 0) ? -exp : exp;
	tmp[7] = (exp < 10) ? ft_strjoin(tmp[6], "0") : ft_strjoin(tmp[6], "");
	tmp[8] = ft_itoa(exp);
	tmp[9] = ft_strjoin(tmp[7], tmp[8]);
	i = 0;
	while (i < 9)
	{
		free(tmp[i]);
		i++;
	}
	return (tmp[9]);
}
