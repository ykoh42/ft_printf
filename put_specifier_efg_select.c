/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_efg_select.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:41:41 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/15 23:58:31 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *correction(char *ret)
{
	const char	*p = ret;
	char		*tmp[3];
	int			exp;
	const char	*e = ft_strchr(p, 'e');

//	printf("\ninit : %s\n", p);
	if (ft_strchr(p, '.'))
	{
		while (*ret && *ret != '0')
			ret++;
//	printf("\nret : %s\n", ret);
/*		if (*ret == '0')
		{
			ret = ft_strchr(ret, '.') + 1;
			ret = ft_round
		}
*/	
		tmp[1] = ret;
		while (*ret == '0')
			ret++;
		if (*ret != 'e')
			return ((char *)p);
//	printf("\nret : %s\n", ret);
//	printf("\nret-1 : %c\n", *(ret - 1));
		if (*(ret - 1) == '0' && *(tmp[1] - 1) == '.')
			tmp[1]--;
		tmp[0] = ft_strndup(p, tmp[1] - p);
//	printf("\ntmp0 : %s\n", tmp[0]);
		tmp[1] = ft_strdup(e);
//	printf("\ntmp1 : %s\n", tmp[1]);
		free((char *)p);
		ret = ft_strjoin_free(tmp[0], tmp[1]);
	}
/*
	else if (ft_strnstr(p, "10.", 4))
	{
//	printf("\nret : %s\n", ret);
		ft_strlcpy((char *)e - 1, e, ft_strlen(e) + 2);
		exp = ft_atoi(ft_strchr(p, 'e') + 1);
		exp++;
	//	printf("exp : %d\n", exp);
		tmp[0] = ft_strndup(p, ft_strchr(p, 'e') - p);
		tmp[1] = (ft_abs(exp) > 9) ? ft_itoa(ft_abs(exp)) :
			ft_strjoin_free(ft_strdup("0"), ft_itoa(ft_abs(exp)));
		tmp[1] = (exp >= 0) ? ft_strjoin_free(ft_strdup("e+"), tmp[1]) :
							ft_strjoin_free(ft_strdup("e-"), tmp[1]);
		free((char *)p);
		ret = ft_strjoin_free(tmp[0], tmp[1]);
	}

//	priintf("\ncat : %s\n", ret);

//	printf("\nret : %s\n", ret);
*/

	return (ret);
	exp +=0;
}


static char	*select_ret_hash(t_meta *fs, char *ret)
{
	char	*p;

	if (!fs->hash && fs->specifier == 'f')
	{
		p = ret + ft_strlen(ret) - 1;
		while (p != ret && *(p + 1) != '.' && (*p == '0' || *p == '.'))
			p--;
		p = ft_strndup(ret, p - ret + 1);
		free(ret);
		ret = p;
	}
	if (ft_strncmp(ret, "-", 2) == 0)
		ret = ft_strjoin_free(ret, ft_strdup("0"));
	return (ret);
}

static char	*select_ret_process(double n, t_meta *fs, const char *e)
{
	int		exp;
	char	*ret;
	char	*tmp;
	exp = ft_atoi(ft_strchr(e, 'e') + 1);
//	if (ft_strncmp(e, "9.9e", 4) == 0 || ft_strncmp(e, "-9.9e", 5) == 0)
//	{exp++; fs->specifier = 'e';}
	if (exp >= -4 && exp < fs->precision)
	{
		fs->specifier = 'f';
		fs->precision = fs->precision - 1 - exp;
		ret = ft_dtoa(n, fs->precision, fs->specifier);
	}
	else
	{
		fs->specifier = 'e';
		fs->precision = fs->precision - 1;
		ret = ft_dtoa(n, fs->precision, fs->specifier);
		ret = correction(ret);
//		printf("ret : %s\n", ret);
//		printf("%d|%ld|\n",fs->precision, ft_strchr(ret, 'e') - ft_strchr(ret, '.'));
		if (ft_strchr(ret, '.') &&
			fs->precision + 1 < ft_strchr(ret, 'e') - ft_strchr(ret, '.'))
		{
			tmp = ft_strdup(ft_strchr(ret, 'e'));
//			printf("%s|tmp\n", tmp);
			ret = ft_round(ret, fs->precision);
			ret = ft_strjoin_free(ret, tmp);
//			printf("%s|ret\n", ret);
		}
	}
		ret = correction(ret);

	return (ret);
}

const char	*select_ret(va_list ap, t_meta *fs)
{
	const double	n = va_arg(ap, double);
	char		*e;
	e = ft_dtoa(n, fs->precision, 'e');
//	const char		*f;
//	f = ft_dtoa(n, fs->precision, 'f');
	char			*ret;

	if (!e)
		return (0);
	if (fs->precision == 0)
		fs->precision = 1;
	if (fs->precision == -1)
		fs->precision = 6;
	if (ft_strnstr(e, "nan", 4) || ft_strnstr(e, "inf", 4))
	{
//		free((char *)e);
		return (e);
	}
	ret = select_ret_process(n, fs, e);
//	printf("\n%s\n", ret);
	ret = select_ret_hash(fs, ret);
//	printf("\n%s\n", ret);
//	va_free(2, &e, &f);
	free(e);
	return (ret);
}
