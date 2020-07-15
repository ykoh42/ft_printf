/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:44:51 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/16 05:19:40 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_exp(char *ret, size_t i, size_t end)
{
	int	exp;

	exp = 0;
	if (i < end)
	{
		while (i < end)
		{
			ft_swap(&ret[i], &ret[i + 1]);
			exp--;
			i++;
		}
	}
	else if (i > end)
	{
		while (i > end + 1)
		{
			ft_swap(&ret[i - 1], &ret[i]);
			exp++;
			i--;
		}
	}
	return (exp);
}

static char	*convert_scientific(char *ret, int precision, int exp)
{
	char	*tmp;

	if ((!ft_strchr(ret, '.') && ft_strnstr(ret, "10", 3)))
	{
		ret[ft_strlen(ret) - 1] = '\0';
		exp++;
	}
	tmp = (ft_abs(exp) > 9) ? ft_itoa(ft_abs(exp)) :
		ft_strjoin_free(ft_strdup("0"), ft_itoa(ft_abs(exp)));
	ret = (exp >= 0) ? ft_strjoin_free(ret, ft_strdup("e+")) :
						ft_strjoin_free(ret, ft_strdup("e-"));
	ret = ft_strjoin_free(ret, tmp);
	if (ft_strchr(ret, '.') &&
		precision + 1 < ft_strchr(ret, 'e') - ft_strchr(ret, '.'))
	{
		tmp = ft_strdup(ft_strchr(ret, 'e'));
		ret = ft_round(ret, precision);
		ret = ft_strjoin_free(ret, tmp);
	}
	ret = e_correction(ret, precision, 'e');
	return (ret);
}

static char	*reset_ret_if_exp_minus(int precision, char *ret,
									char *tmp, int neg)
{
	tmp = ft_strndup(tmp - 1, precision + 309);
	tmp = ft_round(tmp, precision);
	free(ret);
	ret = (neg) ? ft_strjoin_free(ft_strdup("-"), tmp) : tmp;
	return (ret);
}

static char	*reset_ret_if_exp_plus(int precision, char *ret,
									char *tmp, int neg)
{
	tmp = ft_strndup(ft_strchr(ret, '.') - 1, precision + 309);
	tmp = ft_round(tmp, precision);
	free(ret);
	ret = (neg) ? ft_strjoin_free(ft_strdup("-"), tmp) : tmp;
	return (ret);
}

char		*ft_dtoa_scientific(long double n, int precision, char *ret)
{
	int			exp;
	char		*tmp;
	size_t		i;
	size_t		end;
	const int	neg = (*ret == '-') ? 1 : 0;

	tmp = ret;
	i = ft_strchr(ret, '.') - ret;
	while (*tmp == '-' || *tmp == '0' || *tmp == '.')
		tmp++;
	end = tmp - ret;
	if (n == 0.0)
	{
		i = (precision == 0) ? i - 1 : i;
		tmp = ft_strndup(ret, i + precision + 1);
		free(ret);
		ret = tmp;
		i = end;
	}
	exp = count_exp(ret, i, end);
	if (i < end)
		ret = reset_ret_if_exp_minus(precision, ret, tmp, neg);
	else if (i > end)
		ret = reset_ret_if_exp_plus(precision, ret, tmp, neg);
	return (convert_scientific(ret, precision, exp));
}
