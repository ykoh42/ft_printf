/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:42:03 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 02:25:21 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*get_str_f(union u_double std,
						int integer[], int fractional[], int precision)
{
	char	*tmp[2];
	char	*ret;

	rounding(integer, fractional, precision);
	tmp[0] = get_integer(integer);
	ret = (std.ieee.negative) ? ft_strjoin("-", tmp[0]) :
								ft_strjoin("", tmp[0]);
	free(tmp[0]);
	tmp[0] = ret;
	tmp[1] = get_fractional(fractional, precision);
	ret = (ft_strlen(tmp[1])) ? ft_strjoin(".", tmp[1]) :
								ft_strdup("");
	free(tmp[1]);
	tmp[1] = ret;
	ret = ft_strjoin(tmp[0], tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	return (ret);
}

static char	*get_str_g(union u_double std,
					int integer[], int fractional[], int precision)
{
	int		exp;
	char	*ret;

	ret = (precision < 1) ? ft_dtoa(std.d, 0, 'e') :
							ft_dtoa(std.d, precision - 1, 'e');
	exp = ft_atoi(ft_strchr(ret, 'e') + 1);
	free(ret);
	precision = (precision == 0) ? 1 : precision;
	if (exp >= -4 && exp < precision)
		ret = get_str_f(std, integer, fractional, precision - 1 - exp);
	else
		ret = get_str_e(std, integer, fractional, precision - 1);
	return (ret);
}

static void	set_frac(union u_double std, int frac[])
{
	int	i;

	i = 19;
	while (i >= 0)
	{
		frac[20 - i] = (1 & std.ieee.mantissa0 >> i);
		i--;
	}
	i = 31;
	while (i >= 0)
	{
		frac[52 - i] = (1 & std.ieee.mantissa1 >> i);
		i--;
	}
	frac[0] = 1;
}

char		*ft_dtoa(double d, int precision, char specifier)
{
	union u_double	std;
	int				frac[53];
	int				integer[309];
	int				fractional[1023];

	std.d = d;
	if (std.ieee.exponent == 0x7FF &&
		!(std.ieee.mantissa0 == 0x0 && std.ieee.mantissa1 == 0x0))
		return (ft_strdup("nan"));
	if (std.ieee.exponent == 0x7FF &&
		(std.ieee.mantissa0 == 0x0 && std.ieee.mantissa1 == 0x0))
		return ((std.ieee.negative) ? ft_strdup("-inf") : ft_strdup("inf"));
	ft_bzero(frac, sizeof(frac));
	set_frac(std, frac);
	ft_bzero(integer, sizeof(integer));
	ft_bzero(fractional, sizeof(fractional));
	set_integer(integer, std.ieee.exponent - BIAS, frac);
	set_fractional(fractional, std.ieee.exponent - BIAS, frac);
	precision = (precision < 0) ? 6 : precision;
	if (specifier == 'g')
		return (get_str_g(std, integer, fractional, precision));
	else if (specifier == 'e')
		return (get_str_e(std, integer, fractional, precision));
	else
		return (get_str_f(std, integer, fractional, precision));
}
