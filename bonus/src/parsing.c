/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:54:23 by odessein          #+#    #+#             */
/*   Updated: 2022/11/03 13:50:42 by odessein         ###   ########.fr       */
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
	return (true);
}

static bool	fill_mem_shared(t_mem_shared *mem_shared)
{
	int				i;
	pthread_mutex_t	**arr;

	arr = malloc(sizeof(pthread_mutex_t *) * 6);
	if (!arr)
	{
		write(2, "Malloc fail\n", 12);
		return (false);
	}
	i = 0;
	mem_shared->die = false;
	if (!init_mutex(mem_shared, &i, arr))
		return (false);
	pthread_mutex_lock(&mem_shared->mutex_eat);
	mem_shared->end_by_eat = 0;
	pthread_mutex_unlock(&mem_shared->mutex_eat);
	free(arr);
	return (true);
}

bool	arguments_handle(int ac)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (false);
	}
	return (true);
}

bool	check_content(int ac, char **av, int *j, int *k)
{
	int	i;

	i = 0;
	while (++i < ac - 1)
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

bool	parse_input(int ac, char **av, t_info *info, t_mem_shared *mem_shared)
{
	int	j;
	int	k;

	if (!arguments_handle(ac))
		return (false);
	if (!check_content(ac, av, &j, &k))
		return (false);
	if (!fill_info(ac, av, info))
		return (false);
	if (!fill_mem_shared(mem_shared))
		return (false);
	return (true);
}
