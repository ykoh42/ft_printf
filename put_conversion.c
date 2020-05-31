#include "ft_printf.h"
/*
int		put_format(va_list ap, t_meta *fs, long long *cnt)
{
	void	(*selector)(va_list, t_meta *, int *);


	return (put_specifier_s(ap, fs, cnt));
}
*/
void	set_meta(const char *restrict *format, va_list ap, t_meta *fs)
{
	set_flag(format, fs);
	set_width(format, ap, fs);
	set_precision(format, ap, fs);
	set_length(format, fs);
	set_specifier(format, fs);
}

void	parse_format(const char *restrict *format, va_list ap, t_meta *fs)
{
	if (**format != '%')
		return ;
	(*format)++;
	set_meta(format, ap, fs);
}

int		put_conversion(const char *restrict *format, va_list ap,
																long long *cnt)
{
	t_meta	*fs;
	int		ret;

	ret = 0;
	if (!(fs = ft_calloc(1, sizeof(t_meta))))
		return (-1);
	parse_format(format, ap, fs);
	if (!fs->specifier)
		return (-1);
	ret = put_format(ap, fs, cnt);
	free(fs);
	return (ret);
}
