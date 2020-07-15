/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:44:51 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/15 23:57:11 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_exp(char *ret, size_t i, size_t end)
{
	int	exp;
//	printf("ret ; %s\n", ret);
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

static char	*convert_scientific(char *ret, int exp)
{
	char	*tmp;

	if (ft_strnstr(ret, "10.", 4))
	{
		ft_swap(ft_strchr(ret, '.') - 1, ft_strchr(ret, '.'));
		*(ret + ft_strlen(ret) - 1) = '\0';
		(exp)++;
	}
	if ((!ft_strchr(ret, '.') && ft_strnstr(ret, "10", 3)))
	{
		ret[ft_strlen(ret) - 1] = '\0';
		(exp)++;
	}
//	printf("\n%s, %d\n", ret, exp);
	tmp = (ft_abs(exp) > 9) ? ft_itoa(ft_abs(exp)) :
		ft_strjoin_free(ft_strdup("0"), ft_itoa(ft_abs(exp)));
	ret = (exp >= 0) ? ft_strjoin_free(ret, ft_strdup("e+")) :
						ft_strjoin_free(ret, ft_strdup("e-"));
	ret = ft_strjoin_free(ret, tmp);
//	printf("\n%s%d\n", ret, exp);
	return (ret);
}

static char	*reset_ret_if_exp_minus(int precision, char *ret,
									char *tmp, int neg)
{
//	printf("\nret-   : %s\n", ret);
//	tmp = ft_strndup(tmp - 1, (size_t)precision + 4);
	tmp = ft_strndup(tmp - 1, precision + 309);
//	printf("\ntmp : %s\n", tmp);
	tmp = ft_round(tmp, precision + 1);
//	printf("\ntmp : %s\n", tmp);
	free(ret);
	ret = (neg) ? ft_strjoin_free(ft_strdup("-"), tmp) : tmp;
	return (ret);
}

static char	*reset_ret_if_exp_plus(int precision, char *ret,
									char *tmp, int neg)
{
//	printf("\nret+ : %s\n", ret);
//	tmp = ft_strndup(ft_strchr(ret, '.') - 1, (size_t)precision + 4);
	tmp = ft_strndup(ft_strchr(ret, '.') - 1, precision + 309);
//	printf("\ntmp : %s\n", tmp);
	tmp = ft_round(tmp, precision);
//	printf("\ntmp : %s\n", tmp);
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
//	printf("\nretin : %s\n", ret);
	if (i < end)
		ret = reset_ret_if_exp_minus(precision, ret, tmp, neg);
	else if (i > end)
		ret = reset_ret_if_exp_plus(precision, ret, tmp, neg);
//	printf("\nret : %s\n", ret);
	return (convert_scientific(ret, exp));
}
