/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_integer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:37:41 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 00:14:34 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	set_integer_process(int bit[], int integer[], int power_of_two[])
{
	int	i;
	int j;

	i = 0;
	while (i < 1024)
	{
		if (bit[i++])
		{
			j = 308;
			while (j >= 0)
			{
				if ((integer[j] += power_of_two[j]) > 9)
					set_carry(integer, j);
				j--;
			}
		}
		j = 308;
		while (j >= 0)
		{
			if ((power_of_two[j] *= 2) > 9)
				set_carry(power_of_two, j);
			j--;
		}
	}
}

void		set_integer(int integer[], int exp, int frac[])
{
	int		power_of_two[309];
	int		bit[1024];
	int		i;
	int		j;

	if (exp < 0)
		return ;
	ft_bzero(power_of_two, sizeof(power_of_two));
	ft_bzero(bit, sizeof(bit));
	i = 0;
	j = 0;
	while (i < 53)
	{
		if (j > exp)
			break ;
		bit[exp - j++] = frac[i++];
	}
	power_of_two[0] = 1;
	set_integer_process(bit, integer, power_of_two);
	set_carry_integer(integer);
}

char		*get_integer(int integer[])
{
	char	*ret;
	int		i;
	int		j;

	i = 308;
	while (i >= 0)
	{
		if (integer[i] != 0)
			break ;
		i--;
	}
	if (i == -1)
		i = 0;
	ret = ft_calloc(i + 2, sizeof(char));
	j = 0;
	while (i >= 0)
		ret[j++] = integer[i--] + '0';
	return (ret);
}
