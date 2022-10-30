/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:21:52 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 21:41:06 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
/*
static bool	starting_block(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->mutex_start);
	while (!info->start && i < philo->input.number_of_philo)
	{
		if (!&info->philo[i].created)
		{
			pthread_mutex_unlock(&info->mutex_start);
			return (false);
		}
		i++;
	}
	info->start = true;
	pthread_mutex_unlock(&info->mutex_start);
	return (true);
}
*/
static bool	set_offset(t_philo *philo, t_info *info)
{
	long long	offset_time;
	long long	time;

	offset_time = philo->input.time_to_die - (philo->input.time_to_eat + philo->input.time_to_sleep) - 5;
	if (philo->id % 2 == 0)
	{
		if (!display(philo, info, _THINK))
			return (false);
		if (offset_time > 0)
		{
			time = get_actual_time();
			while (get_actual_time() - time > offset_time)
				usleep(500);
		}
	}
	else
	{
		if (!display(philo, info, _THINK))
			return (false);
	}
	return (true);
}

void	*routine(void *philoo)
{
	t_info	*info;
	t_philo	*philo;
//	int	i;

	philo = (t_philo *) philoo;
	info = philo->info;
	philo->created = true;
	//wait all thread before start loop
	//setup the offset
	//while (!starting_block(philo, info))
	//{
	//	i++;
//	}
	if (!set_offset(philo, info))
		return (false);
	while (1)
	{
		if (get_actual_time() - philo->time_last_eat > 450)
			printf("value : %li\n", get_actual_time() - philo->time_last_eat);
		if (!take_fork(philo, info))
			break ;
		if (!eating(philo, info))
			break ;
		if (!sleeping(philo, info))
			break ;
		if (!thinking(philo, info))
			break ;
	}
	return (0);
}
