/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:01:08 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/25 14:43:45 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_numlen(unsigned long long n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_utoa(unsigned long long n)
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
		rem = n % 10;
		n = n / 10;
		num[i] = "0123456789"[rem];
		i++;
	}
	return (ft_strrev(num));
}
