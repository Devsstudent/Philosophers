/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:08:16 by odessein          #+#    #+#             */
/*   Updated: 2022/11/04 15:08:21 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

static void	ft_skip(const char *nptr, int *i, long long *res, int *neg_sign)
{
	*i = 0;
	*res = 0;
	*neg_sign = 1;
	while (nptr[*i] == '\v' || nptr[*i] == '\t' || nptr[*i] == '\r'
		|| nptr[*i] == '\n' || nptr[*i] == '\f' || nptr[*i] == ' ')
		*i = *i + 1;
}

int	ft_atoi(const char *nptr)
{
	int			i;
	long long	res;
	int			neg_sign;

	ft_skip(nptr, &i, &res, &neg_sign);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg_sign = -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] != ' ' && ft_isdigit(nptr[i]))
	{
		if ((long)(res * neg_sign) < -2147483648)
			return (0);
		else if ((long)(res * neg_sign) > 2147483647)
			return (-1);
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	res *= neg_sign;
	return ((int) res);
}
