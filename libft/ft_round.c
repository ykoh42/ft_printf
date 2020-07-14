/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:44:51 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/13 17:51:00 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ceil_carry(char *n)
{
	char		*ret;
	const char	*p = n;
	const int	neg = (*n == '-') ? 1 : 0;

	while (!ft_isdigit(*n))
		n++;
	ret = (char *)p;
	if (*n == '0')
	{
		ret = (neg) ? ft_strdup("-") : ft_strdup("");
		ret = ft_strjoin_free(ret, ft_strdup("1"));
		ret = ft_strjoin_free(ret, ft_strdup(n));
		free((char *)p);
	}
	return (ret);
}

char		*ft_ceil(char *n, int precision)
{
	const char	*p = n;
	const int	neg = (*n == '-') ? 1 : 0;
	const char	first_digit = (neg) ? *(p + 1) : *p;

	if (!(n = ft_strchr(n, '.')))
		return ((char *)p);
	n += precision + 1;
	*n-- = '\0';
	while (n != ((neg) ? p : p - 1))
	{
		*n += 1;
		if (*n != ':' && *n != '/')
			break ;
		*n = (*n == ':') ? '0' : '.';
		n--;
	}
	n = (char *)p;
	if (*(n + ft_strlen(n) - 1) == '.')
		*(n + ft_strlen(n) - 1) = '\0';
	if (first_digit == '9')
		return (ft_ceil_carry(n));
	return (n);
}

char		*ft_floor(char *n, int precision)
{
	const char	*p = n;

	if (!(n = ft_strchr(n, '.')))
		return ((char *)p);
	n += precision + 1;
	*n = '\0';
	if (*(n - 1) == '.')
		*(n - 1) = '\0';
	return ((char *)p);
}

static char	*ft_bankers(char *n, int precision)
{
	const char	*p = n;
	char		*even_odd;

	if (!(n = ft_strchr(n, '.')))
		return ((char *)p);
	n += precision + 1;
	if (*n == '5')
	{
		even_odd = n++;
		even_odd--;
		while (*n && *n == '0')
			n++;
		if (*n == '\0')
		{
			while (!ft_isdigit(*even_odd))
				even_odd--;
			return (((*even_odd - '0') % 2) ?
			ft_ceil((char *)p, precision) : ft_floor((char *)p, precision));
		}
	}
	return (ft_ceil((char *)p, precision));
}

char		*ft_round(char *n, int precision)
{
	const char	*p = n;

	if (!(n = ft_strchr(n, '.')))
		return ((char *)p);
	n += precision + 1;
	if (*n > '5')
		return (ft_ceil((char *)p, precision));
	else if (*n < '5')
		return (ft_floor((char *)p, precision));
	else
		return (ft_bankers((char *)p, precision));
}
