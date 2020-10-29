/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:36:58 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 17:39:11 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

float		number(const char *str, int neg)
{
	int		i;
	float	res;
	int		j;

	i = 0;
	res = 0;
	j = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = res + (str[i] - 48) * pow(10, -j);
			j++;
			i++;
		}
	}
	return (res * neg);
}

float		ft_atof(char *str)
{
	int		i;
	int		neg;
	float	res;

	i = 0;
	neg = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	res = number(str + i, neg);
	return (res);
}
