/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:59:16 by odessein          #+#    #+#             */
/*   Updated: 2022/11/03 11:46:28 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	eating(t_philo *philo, t_mem_shared *mem_shared)
{
	pthread_mutex_lock(&mem_shared->mutex_process);
	philo->process = EATING;
	pthread_mutex_unlock(&mem_shared->mutex_process);
	if (!display(philo, mem_shared, _EAT))
		return (false);
	philo->eat_turn++;
	pthread_mutex_lock(&mem_shared->mutex_eat);
	philo->time_last_eat = get_actual_time();
	pthread_mutex_unlock(&mem_shared->mutex_eat);
	if (!sleep_loop(philo->info.t_to_eat, mem_shared, philo))
	{
		unlock_fork(philo, mem_shared);
		return (false);
	}
	unlock_fork(philo, mem_shared);
	return (true);
}

bool	sleeping(t_philo *philo, t_mem_shared *mem_shared)
{
	pthread_mutex_lock(&mem_shared->mutex_process);
	philo->process = SLEEPING;
	pthread_mutex_unlock(&mem_shared->mutex_process);
	if (!display(philo, mem_shared, _SLEEP))
		return (false);
	if (!sleep_loop(philo->info.t_to_sleep, mem_shared, philo))
		return (false);
	return (true);
}

bool	thinking(t_philo *philo, t_mem_shared *mem_shared)
{
	pthread_mutex_lock(&mem_shared->mutex_process);
	philo->process = THINKING;
	pthread_mutex_unlock(&mem_shared->mutex_process);
	if (!display(philo, mem_shared, _THINK))
		return (false);
	if ((philo->info.nb_philo % 2) != 0 && (philo->id == philo->info.nb_philo))
	{
		if (!sleep_loop(philo->info.t_to_eat - 10, mem_shared, philo))
			return (false);
	}
	return (true);
}
