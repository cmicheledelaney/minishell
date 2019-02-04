/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:05:55 by ccodiga           #+#    #+#             */
/*   Updated: 2018/12/07 13:07:08 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H

# include <stdlib.h>
# define BUFF_SIZE 10
# define FD_LIMIT 4865
# define NULL_CHECK(x) (x != 0)

int				get_next_line(const int fd, char **line);

#endif
