/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:47:39 by ccodiga           #+#    #+#             */
/*   Updated: 2018/10/25 13:09:53 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		*((unsigned char *)dst) = *((unsigned char *)src);
		if (*((unsigned char *)src) == (unsigned char)c)
			return (++dst);
		dst++;
		src++;
	}
	return (NULL);
}
