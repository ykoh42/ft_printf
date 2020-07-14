/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:44:51 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/13 02:11:54 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_dtoa_process(long double n, int precision, char *ret)
{
	int			m;
	int			digit;
	long double	weight;

	m = ft_log10(n);
	weight = ft_pow(10, m);
	while (m + 1 != -precision || m >= 0)
	{
		weight = ft_pow(10, m);
		if (!ft_isinf(weight) && weight > 0)
		{
			digit = (int)(n / weight);
			n -= (digit * weight);
			ret = ft_strjoin_free(ret, ft_itoa(digit));
			if (m == 0 && n >= 0 && precision != 0)
				ret = ft_strjoin_free(ret, ft_strdup("."));
		}
		m--;
	}
	return (ret);
}

static char	*ft_dtoa_exception(double n)
{
	if (ft_isinf(n))
		return (ft_strdup("inf"));
	if (ft_isnan(n))
		return (ft_strdup("nan"));
	return (NULL);
}

char		*ft_dtoa(double n, int precision, char specifier)
{
	char		*ret;
	char		*ret_scientific;

	ret = (ft_isneg_dbl(n)) ? ft_strdup("-") : ft_strdup("");
	if (ft_isinf(n) || ft_isnan(n))
		return (ft_strjoin_free(ret, ft_dtoa_exception(n)));
	n = (ft_isneg_dbl(n)) ? -n : n;
	precision = (precision < 0) ? 6 : precision;
	ret = ft_dtoa_process(n, precision + 20, ret);
	if (specifier == 'e')
		return (ft_dtoa_scientific(n, precision, ret));
	else if (specifier == 'f')
		return (ft_round(ret, precision));
	else if (specifier == 'g')
	{
		ret_scientific = ft_dtoa_scientific(n, precision, ft_strdup(ret));
		ret = ft_round(ret, precision);
		if (ft_strlen(ret_scientific) > ft_strlen(ret))
		{
			free(ret);
			return (ret_scientific);
		}
		free(ret_scientific);
	}
	return (ret);
}
