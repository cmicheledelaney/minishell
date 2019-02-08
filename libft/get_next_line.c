/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:05:13 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/18 09:59:29 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	copy_line(char **line, char **str, int eol)
{
	int		j;
	char	*hold;

	j = 0;
	*line = ft_strnew(eol + 2);
	hold = *str;
	while (**str != '\n' && **str != '\0')
		(*line)[j++] = *(*str)++;
	*str += (**str == '\n') ? (1) : (0);
	*str = ft_strdup(*str);
	free(hold);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*str[FD_LIMIT];
	int				eol;
	int				ret;

	eol = 0;
	if (fd < 0 || read(fd, &buff, 0) < 0 || !line || fd >= FD_LIMIT)
		return (-1);
	while ((ret = read(fd, &buff, BUFF_SIZE)) > -1)
	{
		buff[ret] = '\0';
		str[fd] = hold_and_free(str[fd], buff);
		while (str[fd][eol] != '\n' && str[fd][eol] != '\0')
			eol++;
		if (str[fd][eol] == '\n' || (str[fd][0] != '\0' && ret != BUFF_SIZE))
			return (copy_line(line, &str[fd], eol));
		if (ret == 0)
			return (0);
	}
	return (-1);
}
