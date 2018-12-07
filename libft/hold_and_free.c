/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:39:57 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/14 17:23:19 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*hold_and_free(char *old, char *addition)
{
	char *message;

	message = ft_strjoin(old, addition);
	(old != NULL) ? (free(old)) : (0);
	return (message);
}
