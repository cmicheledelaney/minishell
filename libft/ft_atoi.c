/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:54:47 by ccodiga           #+#    #+#             */
/*   Updated: 2018/10/25 13:02:22 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			neg;
	long long	number;

	number = 0;
	neg = 1;
	while ((*str == '\t' || *str == '\n' || *str == '\f' || *str == '\v' ||
		*str == '\r' || *str == ' ') && *str)
		str++;
	(*str == '-') ? (neg = -1) : (0);
	(*str == '-' || *str == '+') ? (str++) : (0);
	while (ft_isdigit(*str))
	{
		number += (*str - 48);
		(ft_isdigit(*(str + 1))) ? (number *= 10) : (0);
		str++;
	}
	return (neg * number);
}
