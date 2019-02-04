/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:18:24 by ccodiga           #+#    #+#             */
/*   Updated: 2018/10/25 13:11:16 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	long i;

	i = -1;
	if (s == NULL || f == NULL)
		return ;
	while (s[++i])
		(*f)((unsigned int)i, &s[i]);
}
