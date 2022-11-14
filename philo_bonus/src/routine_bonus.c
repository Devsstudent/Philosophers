/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:10 by odessein          #+#    #+#             */
/*   Updated: 2022/11/14 15:16:30 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	loop_life(t_sem_info *sem, t_philo *philo)
{
	while (1)
	{
		if (philo->info.nb_philo == 1)
			if (!sleep_loop(philo->info.t_to_die + 2, philo, sem))
				break ;
		if (!take_fork(philo, sem))
			break ;
		if (!eating(philo, sem))
			break ;
		if (philo->eat_turn >= philo->info.t_eat_max
			&& philo->info.t_eat_max > -1)
		{
			if (sem_post(sem->max) != 0)
				write(2, "fail sem post\n", 11);
			break ;
		}
		if (!sleeping(philo, sem))
			break ;
		if (!thinking(philo, sem))
			break ;
	}
	//join_fork
}

void	routine(t_sem_info *sem, t_philo *philo)
{
	//write(2, "test", 4);
	if (philo->eat_turn >= philo->info.t_eat_max && philo->info.t_eat_max > -1)
	{
		if (sem_post(sem->max) != 0)
			write(2, "fail sem post\n", 11);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(philo->info.t_to_eat - 10);
	loop_life(sem, philo);
	if (sem_close(sem->max) != 0)
		write(2, "Error closing sem\n", 18);
	if (sem_close(sem->bowl) != 0)
		write(2, "Error closing sem\n", 18);
	if (sem_close(sem->write) != 0)
		write(2, "Error closing sem\n", 18);
	if (sem_close(sem->dead) != 0)
		write(2, "Error closing sem\n", 18);
}
