/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:01:08 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/25 14:43:12 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_numlen(unsigned long long n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char			*ft_hextoa(unsigned long long n, char specifier)
{
	char			*num;
	int				rem;
	size_t			i;
	const size_t	num_len = ft_numlen(n);

	if (!(num = ft_calloc(num_len + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (i < num_len)
	{
		rem = n % 16;
		n = n / 16;
		if (specifier == 'x')
			num[i] = "0123456789abcdef"[rem];
		else
			num[i] = "0123456789ABCDEF"[rem];
		i++;
	}
	return (ft_strrev(num));
}
