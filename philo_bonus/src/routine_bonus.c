/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:08:27 by odessein          #+#    #+#             */
/*   Updated: 2022/11/18 12:06:24 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	loop_life(t_sem_info *sem, t_philo *philo)
{
	while (1)
	{
		if (philo->info.nb_philo == 1)
			if (!sleep_loop(philo->info.t_to_die + 2, philo))
				break ;
		if (!take_fork(philo, sem))
			break ;
		if (!eating(philo, sem))
			break ;
		if (philo->eat_turn == philo->info.t_eat_max
			&& philo->info.t_eat_max > -1)
		{
			if (sem_post(sem->max) != 0)
				write(2, "fail sem post\n", 11);
		}
		if (!sleeping(philo, sem))
			break ;
		if (!thinking(philo, sem))
			break ;
	}
}

void	routine(t_sem_info *sem, t_philo *philo)
{
	if (philo->eat_turn >= philo->info.t_eat_max && philo->info.t_eat_max > -1)
	{
		if (sem_post(sem->max) != 0)
			write(2, "fail sem post\n", 11);
		return ;
	}
	if (philo->id % 2 == 0)
		if (!sleep_loop(philo->info.t_to_eat - 1, philo))
			return ;
	loop_life(sem, philo);
}
