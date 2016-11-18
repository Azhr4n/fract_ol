/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:48:03 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 14:48:08 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_value(const char *str, int i, int neg)
{
	int		ret;

	ret = 0;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		ret *= 10;
		if (ret < 0)
			ret -= str[i] - '0';
		else
			ret += str[i] - '0';
		if (neg && ret)
		{
			ret *= -1;
			neg = 0;
		}
		i++;
	}
	return (ret);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		ret;
	int		neg;

	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	i = 0;
	neg = 0;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	ret = calc_value(str, i, neg);
	return (ret);
}
