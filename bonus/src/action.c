/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:52:13 by odessein          #+#    #+#             */
/*   Updated: 2022/11/04 15:59:14 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	eating(t_philo *philo, t_sem_info *sem)
{
	//display_eating
	write(2, "test", 4);
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
	if (!display(philo, sem, _THINK))
		return (false);
	//display think
	return (true);
}
