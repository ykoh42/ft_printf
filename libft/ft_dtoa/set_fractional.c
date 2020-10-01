/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fractional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:52:48 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/14 15:52:49 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	set_fractional_process(int bit[], int fractional[],
											int power_of_two[])
{
	int	i;
	int	j;

	i = 1076;
	while (i >= 0)
	{
		if (bit[i--])
		{
			j = 1;
			while (j < 1023)
			{
				if ((fractional[j] += power_of_two[j]) > 9)
					set_carry(fractional, j);
				j++;
			}
		}
		j = 1;
		while (j < 1023)
		{
			if (power_of_two[j] % 2)
				power_of_two[j - 1] += 5;
			power_of_two[j] /= 2;
			j++;
		}
	}
}

void		set_fractional(int fractional[], int exp, int frac[])
{
	int		power_of_two[1023];
	int		bit[1077];
	int		i;
	int		j;

	if (exp > 53 || exp < -1022)
		return ;
	ft_bzero(power_of_two, sizeof(power_of_two));
	ft_bzero(bit, sizeof(bit));
	i = (exp >= 0) ? exp + 1 : 0;
	j = (exp >= 0) ? 0 : -exp - 1;
	while (i < 53)
		bit[1076 - j++] = frac[i++];
	power_of_two[1022] = 5;
	set_fractional_process(bit, fractional, power_of_two);
}

char		*get_fractional(int fractional[], int precision)
{
	char	*ret;
	int		i;
	int		j;
	int		max;

	ret = ft_calloc(precision + 1, sizeof(char));
	max = (precision > 1022) ? 1022 : precision;
	if (max == 0)
		return (ret);
	i = 0;
	j = 0;
	while (i < max)
		ret[j++] = fractional[1022 - i++] + '0';
	while (j < precision)
		ret[j++] = '0';
	return (ret);
}
