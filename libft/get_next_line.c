/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 22:01:51 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/29 01:06:27 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nl(char **line, char **tmpline, char **buf)
{
	const char	*tmp = *tmpline;
	const char	*nl = ft_strchr(*tmpline, '\n');

	if (nl)
	{
		*line = ft_strndup(tmp, nl - tmp);
		*tmpline = ft_strndup(nl + 1, BUFFER_SIZE);
		free((void *)tmp);
		free(*buf);
		return (1);
	}
	*line = (*tmpline) ? *tmpline : ft_strndup("", 1);
	*tmpline = NULL;
	free(*buf);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*tmpline[OPEN_MAX];
	char		*buf;
	char		*nl;
	char		*tmp;
	ssize_t		readcnt;

	if (!line || BUFFER_SIZE <= 0 ||
		!(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((!(nl = ft_strchr(tmpline[fd], '\n')) &&
			(readcnt = read(fd, buf, BUFFER_SIZE)) != 0))
	{
		if (readcnt == -1)
		{
			free(buf);
			return (-1);
		}
		buf[readcnt] = '\0';
		tmp = (tmpline[fd]) ? ft_strjoin(tmpline[fd], buf) :
								ft_strndup(buf, readcnt);
		free(tmpline[fd]);
		tmpline[fd] = tmp;
	}
	return (ft_nl(line, &tmpline[fd], &buf));
}
