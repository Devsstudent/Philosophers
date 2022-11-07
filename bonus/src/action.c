/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:52:13 by odessein          #+#    #+#             */
/*   Updated: 2022/11/07 16:32:09 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	eating(t_philo *philo, t_sem_info *sem)
{
	//display_eating
	if (!display(philo, sem, _EAT))
		return (false);
	philo->time_last_eat = get_actual_time();
	if (!sleep_loop(philo->info.t_to_eat, philo, sem))
		return (false);
	(philo->eat_turn)++;
	if (!unlock_fork(philo, sem))
		return (false);
	return (true);
}

bool	sleeping(t_philo *philo, t_sem_info *sem)
{
	//display sleep
	if (!display(philo, sem, _SLEEP))
		return (false);
	if (!sleep_loop(philo->info.t_to_sleep, philo, sem))
		return (false);
	return (true);
}

bool	thinking(t_philo *philo, t_sem_info *sem)
{
	long long	think;
	if (!display(philo, sem, _THINK))
		return (false);
	think = philo->info.t_to_die - philo->info.t_to_sleep - philo->info.t_to_eat - 17;
	if (think > 0)
		if (!sleep_loop(philo->info.t_to_sleep, philo, sem))
			return (false);
	//display think
	return (true);
}
