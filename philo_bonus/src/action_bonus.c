/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:52:13 by odessein          #+#    #+#             */
/*   Updated: 2022/11/16 22:03:29 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	eating(t_philo *philo, t_sem_info *sem)
{
	if (!display(philo, sem, _EAT))
		return (false);
	if (sem_wait(philo->sem_eat) != 0)
	{
		philo->time_last_eat = get_actual_time();
		sem_post(philo->sem_eat);
	}
	if (!sleep_loop(philo->info.t_to_eat, philo))
	{
		unlock_fork(sem);
		return (false);
	}
	(philo->eat_turn)++;
	if (!unlock_fork(sem))
		return (false);
	return (true);
}

bool	sleeping(t_philo *philo, t_sem_info *sem)
{
	if (!display(philo, sem, _SLEEP))
		return (false);
	if (!sleep_loop(philo->info.t_to_sleep, philo))
		return (false);
	return (true);
}

bool	thinking(t_philo *philo, t_sem_info *sem)
{
	long long	think;

	if (!display(philo, sem, _THINK))
		return (false);
	//Value non arbitraire
	think = philo->info.t_to_die - philo->info.t_to_sleep
		- philo->info.t_to_eat - 17;
	if (think > 0)
		if (!sleep_loop(philo->info.t_to_sleep, philo))
			return (false);
	return (true);
}
