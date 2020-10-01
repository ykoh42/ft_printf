/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 17:20:18 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 02:26:08 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		set_carry(int num[], int i)
{
	num[i] -= 10;
	num[i + 1] += 1;
}

void		set_carry_integer(int integer[])
{
	int i;

	i = 0;
	while (i < 309)
	{
		if (integer[i] > 9)
			set_carry(integer, i);
		i++;
	}
}

void		set_carry_fractional(int fractional[])
{
	int i;

	i = 0;
	while (i < 1022)
	{
		if (fractional[i] > 9)
			set_carry(fractional, i);
		i++;
	}
}

static void	rounding_process(int i, int j, int integer[], int fractional[])
{
	if (j == -1)
	{
		if (i == 1022)
			integer[0] += (integer[0] % 2) ? 1 : 0;
		else
			fractional[i + 1] += (fractional[i] % 2) ? 1 : 0;
	}
	else
	{
		if (i == 1022)
			integer[0] += 1;
		else
			fractional[i + 1] += 1;
	}
}

void		rounding(int integer[], int fractional[], int precision)
{
	int	i;
	int	j;

	i = 1022 - precision;
	if (fractional[i] >= 5)
	{
		j = i - 1;
		while (j >= 0 && fractional[j] == 0)
			j--;
		rounding_process(i, j, integer, fractional);
		set_carry_fractional(fractional);
		if (fractional[1022] > 9)
		{
			fractional[1022] -= 10;
			integer[0] += 1;
		}
		set_carry_integer(integer);
	}
}
