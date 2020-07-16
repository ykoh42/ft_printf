/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 04:18:39 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/16 05:25:14 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static char	*reset_ret(const char *p, const size_t m)
{
	int				exp;
	char			*tmp[2];

	exp = ft_atoi(ft_strchr(p, 'e') + 1);
	exp += m;
	tmp[0] = ft_strndup(p, ft_strchr(p, 'e') - p);
	tmp[1] = (ft_abs(exp) > 9) ? ft_itoa(ft_abs(exp)) :
		ft_strjoin_free(ft_strdup("0"), ft_itoa(ft_abs(exp)));
	tmp[1] = (exp >= 0) ? ft_strjoin_free(ft_strdup("e+"), tmp[1]) :
						ft_strjoin_free(ft_strdup("e-"), tmp[1]);
	free((char *)p);
	return (ft_strjoin_free(tmp[0], tmp[1]));
}

static char	*has_point(char *ret, int precision, char specifier)
{
	const char	*p = ret;
	const char	*e = ft_strchr(p, 'e');
	char		*tmp;

	while (*ret && ((*ret != '0')))
		ret++;
	tmp = ret;
	while (*ret == '0')
		ret++;
	if (*ret != 'e')
		return ((char *)p);
	if (*(ret - 1) == '0' && *(tmp - 1) == '.')
		tmp--;
	if (ft_strchr(p, '.') && specifier == 'e')
		ft_strlcpy(ft_strchr(p, '.') + precision + 1, e, ft_strlen(e) + 2);
	else if (ft_strchr(p, '.') && specifier == 'g')
		ft_strlcpy(tmp, e, ft_strlen(e) + 2);
	ret = (char *)p;
	return (ret);
}


char	*e_correction(char *ret, int precision, char specifier)
{
	const char		*p = ret;
	const char		*e = ft_strchr(p, 'e');
	const size_t	m = (size_t)ft_log10(ft_abs(ft_atoi(p)));

	if (ft_abs(ft_atoi(p)) >= 10)
	{
		while (*ret != '0')
			ret++;
		if (ft_strchr(ret, '.'))
			ft_swap(ret, ft_strchr(ret, '.'));
		ret++;
		while (*ret == '0')
			ret++;
		if (*ret != 'e')
			return ((char *)p);
		if (ft_strchr(p, '.'))
			ft_strlcpy(ft_strchr(p, '.') + precision + 1, e, ft_strlen(e) + 2);
		else
			ft_strlcpy(ret - m, e, ft_strlen(e) + 2);
		ret = reset_ret(p, m);
	}
	else if (ft_strchr(p, '.'))
		ret = has_point(ret, precision, specifier);
	return (ret);
}