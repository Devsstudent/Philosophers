/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:39:10 by odessein          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:56 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	one_philo(t_mem_shared *mem_shared, t_philo *philo)
{
	if (philo->info.nb_philo == 1)
	{
		if (!sleep_loop(philo->info.t_to_die, mem_shared, philo))
			return (true);
		pthread_mutex_lock(&mem_shared->mutex_dead);
		mem_shared->die = true;
		pthread_mutex_unlock(&mem_shared->mutex_dead);
		if (!does_im_dead(philo, mem_shared))
			return (true);
	}
	return (false);
}

static bool	starting_block(t_mem_shared *mem_shared, t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&mem_shared->mutex_start);
	while (++i < philo->info.nb_philo)
	{
		if (!mem_shared->philo[i].created)
		{
			pthread_mutex_unlock(&mem_shared->mutex_start);
			return (false);
		}
	}
	pthread_mutex_unlock(&mem_shared->mutex_start);
	return (true);
}

static bool	setup_offset(t_philo *philo, t_mem_shared *mem_shared)
{
	long	offset;

	offset = philo->info.t_to_eat;
	if (!display(philo, mem_shared, _THINK))
		return (false);
	if ((philo->id % 2) == 1 && offset > 0)
		if (!sleep_loop(offset, mem_shared, philo))
			return (false);
	return (true);
}

void	loop_life(t_philo *philo, t_mem_shared *mem_shared)
{
	while (1)
	{
		if (one_philo(mem_shared, philo))
			break ;
		if (!take_fork(philo, mem_shared))
			break ;
		if (!eating(philo, mem_shared))
			break ;
		if (!sleeping(philo, mem_shared))
			break ;
		if (!thinking(philo, mem_shared))
			break ;
		if (philo->eat_turn == philo->info.t_eat_max)
		{
			pthread_mutex_lock(&mem_shared->mutex_eat);
			mem_shared->end_by_eat += 1;
			pthread_mutex_unlock(&mem_shared->mutex_eat);
			break ;
		}
	}
}

//Starting block necessary ??
void	*routine(void *philoo)
{
	t_philo			*philo;
	t_mem_shared	*mem_shared;

	philo = (t_philo *) philoo;
	mem_shared = philo->mem_shared;
	pthread_mutex_lock(&mem_shared->mutex_start);
	philo->created = true;
	pthread_mutex_unlock(&mem_shared->mutex_start);
	while (!starting_block(mem_shared, philo))
	{
	}
	philo->info.t_start = get_actual_time();
	philo->time_last_eat = philo->info.t_start;
	if (!setup_offset(philo, mem_shared))
		return (0);
	loop_life(philo, mem_shared);
	return (0);
}
