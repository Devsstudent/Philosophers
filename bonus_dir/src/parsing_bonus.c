/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:54:23 by odessein          #+#    #+#             */
/*   Updated: 2022/11/11 10:15:10 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	fill_info(int ac, char **av, t_info *info)
{
	info->nb_philo = ft_atoi(av[1]);
	info->t_to_die = ft_atoi(av[2]);
	info->t_to_eat = ft_atoi(av[3]);
	info->t_to_sleep = ft_atoi(av[4]);
	info->t_start = get_actual_time();
	if (ac == 6)
		info->t_eat_max = ft_atoi(av[5]);
	else
		info->t_eat_max = -1;
	if (info->nb_philo < -1 || info->t_to_die < -1 || info->t_to_eat < -1
		|| info->t_to_sleep < -1 || info->t_eat_max < -1)
		return (error_msg("Overflow"));
	return (true);
}

static bool	arguments_handle(int ac)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (false);
	}
	return (true);
}

static bool	check_content(int ac, char **av, int *j, int *k)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		*j = 0;
		while (av[i][*j] && av[i][*j] == '0')
			(*j)++;
		*k = *j;
		while (av[i][*j] != 0)
		{
			if (av[i][*j] < '0' || av[i][*j] > '9')
			{
				write(2, "Only accepting digit\n", 21);
				return (false);
			}
			if ((*j)++ - *k > 9)
			{
				write(2, "Too big\n", 8);
				return (false);
			}
		}
	}
	return (true);
}

bool	parse_input(int ac, char **av, t_info *info)
{
	int	j;
	int	k;

	if (!arguments_handle(ac))
		return (false);
	if (!check_content(ac, av, &j, &k))
		return (false);
	if (!fill_info(ac, av, info))
		return (false);
	return (true);
}
