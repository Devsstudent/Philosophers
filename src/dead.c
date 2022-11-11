/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:32:38 by odessein          #+#    #+#             */
/*   Updated: 2022/11/11 16:35:03 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	check_dead(t_mem_shared *mem_shared, int nb_philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&mem_shared->mutex_dead);
	if (mem_shared->die)
	{
		pthread_mutex_unlock(&mem_shared->mutex_dead);
		return (true);
	}
	pthread_mutex_unlock(&mem_shared->mutex_dead);
	while (++i < mem_shared->philo[0].info.nb_philo)
	{
		pthread_mutex_lock(&mem_shared->mutex_eat);
		if (get_actual_time() - mem_shared->philo[i].time_last_eat > mem_shared->philo[i].info.t_to_die)
		{
			pthread_mutex_unlock(&mem_shared->mutex_eat);
			pthread_mutex_lock(&mem_shared->mutex_dead);
			mem_shared->die = true;
			pthread_mutex_unlock(&mem_shared->mutex_dead);
			pthread_mutex_lock(&mem_shared->mutex_write);
			//usleep(500);
			print_str(_DIE, timestamp(mem_shared->philo[i].info.t_start), mem_shared->philo[i].id);
			pthread_mutex_unlock(&mem_shared->mutex_write);
			return (true);
		}
		pthread_mutex_unlock(&mem_shared->mutex_eat);
	}
	pthread_mutex_unlock(&mem_shared->mutex_eat);
	pthread_mutex_lock(&mem_shared->mutex_eat);
	if (mem_shared->end_by_eat == nb_philo)
	{
		pthread_mutex_unlock(&mem_shared->mutex_eat);
		return (true);
	}
	pthread_mutex_unlock(&mem_shared->mutex_eat);
	return (false);
}

static void	handle_solo(t_philo *philo, t_mem_shared *mem_shared)
{
	if (philo->info.nb_philo == 1)
	{
		pthread_mutex_lock(&mem_shared->mutex_write);
		print_str(_DIE, timestamp(philo->info.t_start), philo->id);
		pthread_mutex_unlock(&mem_shared->mutex_write);
	}
}

bool	does_im_dead(t_philo *philo, t_mem_shared *mem_shared)
{
	pthread_mutex_lock(&mem_shared->mutex_dead);
	if (mem_shared->die)
	{
		pthread_mutex_unlock(&mem_shared->mutex_dead);
		handle_solo(philo, mem_shared);
		return (false);
	}
	pthread_mutex_unlock(&mem_shared->mutex_dead);
	return (false);
}
