/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:36:31 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 21:42:18 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	init_philo(t_info *info, t_input *input, t_philo *philo, int ind)
{
	philo->info = info;
	philo->id = ind + 1;
	philo->eat_turn = 0;
	philo->input.time_to_sleep = input->time_to_sleep;
	philo->input.time_to_eat = input->time_to_eat;
	philo->input.time_to_die = input->time_to_die;
	philo->input.number_of_philo = input->number_of_philo;
	philo->input.start_time = input->start_time;
	if (pthread_mutex_init(&philo->mutex_fork, NULL) != 0)
	{
		write(2, "fail init mut\n", 14);
		return (false);
	}
	philo->time_last_eat = get_actual_time();
	pthread_mutex_lock(&info->mutex_process);
	philo->process = UNDEF;
	pthread_mutex_unlock(&info->mutex_process);
	return (true);
}

static bool	wait_thread(t_info *info, t_input *input)
{
	int	i;

	i = 0;	
	while (i < input->number_of_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
		{
			write(2, "fail join thread\n", 17);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_destroy(&info->mutex_write) != 0)
	{
		write(2, "fail destroy mut_write\n", 23);
		return (false);
	}
	if (pthread_mutex_destroy(&info->mutex_dead) != 0)
	{
		write(2, "fail destroy mut_dead\n", 22);
		return (false);
	}
	return (true);
}

static bool	create_philo(t_info *info, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->number_of_philo)
	{
	//	printf("%i %i\n", i, input->number_of_philo);
		if (!init_philo(info, input, &info->philo[i], i))
			return (false);
		if (pthread_create(&info->philo[i].thread, NULL, routine, &info->philo[i])!= 0)
		{
			write(2, "fail create philo\n", 18);
			return (false);
		}
	//	printf("%i %i", i, input->number_of_philo);
		i++;
	}
	return (true);
}

bool	philo(t_info *info, t_input *input)
{
	info->philo = malloc(sizeof(t_philo) * input->number_of_philo);
	if (!info->philo)
		return (false);
	if (!create_philo(info, input))
		return (false);
	while (!check_dead(info));
	if (!wait_thread(info, input))
		return (false);
	return (true);
}
