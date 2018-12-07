/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnt_digits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:54:55 by ccodiga           #+#    #+#             */
/*   Updated: 2018/12/05 16:55:12 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		cnt_digits(long long i, char *base)
{
	int		cnt;
	int		basenbr;

	basenbr = 0;
	while (base[basenbr])
		basenbr++;
	cnt = 0;
	while (i != 0)
	{
		i = i / basenbr;
		cnt++;
	}
	return (cnt);
}
