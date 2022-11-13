/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:32:38 by odessein          #+#    #+#             */
/*   Updated: 2022/11/12 20:46:37 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	loop_check_dead(t_mem_shared *mem_shared, int i)
{
	while (++i < mem_shared->philo[0].info.nb_philo)
	{
		pthread_mutex_lock(&mem_shared->mutex_eat);
		if (mem_shared->philo[i].eat_turn != mem_shared->philo[i].info.t_eat_max
			&& get_actual_time() - mem_shared->philo[i].time_last_eat
			> mem_shared->philo[i].info.t_to_die)
		{
			pthread_mutex_unlock(&mem_shared->mutex_eat);
			pthread_mutex_lock(&mem_shared->mutex_dead);
			mem_shared->die = true;
			pthread_mutex_unlock(&mem_shared->mutex_dead);
			pthread_mutex_lock(&mem_shared->mutex_write);
			pthread_mutex_lock(&mem_shared->mutex_start);
			print_str(_DIE, timestamp(mem_shared->philo[i].info.t_start),
				mem_shared->philo[i].id);
			pthread_mutex_unlock(&mem_shared->mutex_start);
			pthread_mutex_unlock(&mem_shared->mutex_write);
			unlock_fork(&mem_shared->philo[i], mem_shared);
			return (true);
		}
		pthread_mutex_unlock(&mem_shared->mutex_eat);
	}
	return (false);
}

static bool	check_max_eat(t_mem_shared *mem_shared, int nb_philo)
{
	pthread_mutex_lock(&mem_shared->mutex_eat);
	if (mem_shared->end_by_eat == nb_philo)
	{
		pthread_mutex_unlock(&mem_shared->mutex_eat);
		return (true);
	}
	pthread_mutex_unlock(&mem_shared->mutex_eat);
	return (false);
}

bool	check_dead(t_mem_shared *mem_shared, int nb_philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&mem_shared->mutex_eat);
	if (mem_shared->end_by_eat == nb_philo)
	{
		pthread_mutex_unlock(&mem_shared->mutex_eat);
		return (true);
	}
	pthread_mutex_unlock(&mem_shared->mutex_eat);
	pthread_mutex_lock(&mem_shared->mutex_dead);
	if (mem_shared->die)
	{
		pthread_mutex_unlock(&mem_shared->mutex_dead);
		return (true);
	}
	if (check_max_eat(mem_shared, nb_philo))
	{
		pthread_mutex_unlock(&mem_shared->mutex_dead);
		return (true);
	}
	pthread_mutex_unlock(&mem_shared->mutex_dead);
	if (loop_check_dead(mem_shared, i))
		return (true);
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
