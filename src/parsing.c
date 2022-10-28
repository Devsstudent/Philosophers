/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:32:35 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 21:26:13 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	ph_fill_info(int ac, char **av, t_input *input, t_info *info)
{
	input->number_of_philo = ph_atoi(av[1]);
	input->time_to_die = ph_atoi(av[2]);
	input->time_to_eat = ph_atoi(av[3]);
	input->time_to_sleep = ph_atoi(av[4]);
	input->start_time = get_actual_time();
	if (input->start_time < 0)
		return (false);
	if (ac == 6)
		input->time_must_eat = ph_atoi(av[5]);
	else
		input->time_must_eat = -1;
	info->die = false;
	info->start = false;
	info->i_fail = 0;
	if (pthread_mutex_init(&info->mutex_dead, NULL) != 0)
	{
		write(2, "Error init mutex\n", 17);
		return (false);
	}
	if (pthread_mutex_init(&info->mutex_start, NULL) != 0)
	{
		write(2, "Error init mutex\n", 17);
		return (false);
	}
	if (pthread_mutex_init(&info->mutex_write, NULL) != 0)
	{
		write(2, "Error init mutex\n", 17);
		if (pthread_mutex_destroy(&info->mutex_dead) != 0)
			write(2, "Error destroying the mutex\n", 27);
		return (false);
	}
	return (true);
}

//check int input + not too long and enough arg
bool	ph_parse(int ac, char **av, t_info *info, t_input *input)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (false);
	i = 1;
	while (i < ac - 1)
	{
		j = 0;
		while (av[i][j] != 0)
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (false);
			j++;
		}
		if (j > 9)
			return (false);
		i++;
	}
	if (!ph_fill_info(ac, av, input, info))
		return (false);
	return (true);
}
