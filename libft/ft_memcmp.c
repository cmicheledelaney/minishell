/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:03:01 by ccodiga           #+#    #+#             */
/*   Updated: 2018/10/25 11:43:01 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (--n && *((unsigned char *)s1) == *((unsigned char *)s2))
	{
		s1++;
		s2++;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}
