/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetup_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:26 by odessein          #+#    #+#             */
/*   Updated: 2022/11/18 12:12:53 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	end_routine(t_philo *philo, t_sem_info *sem)
{
	if (sem_close(sem->max) != 0)
		return (error_msg("Error closing sem max\n"));
	if (sem_close(sem->bowl) != 0)
		return (error_msg("Error closing sem bowl\n"));
	if (sem_close(sem->write) != 0)
		return (error_msg("Error closing sem write\n"));
	if (sem_close(sem->end) != 0)
		return (error_msg("Error closing sem end\n"));
	if (sem_close(sem->catch_fork) != 0)
		return (error_msg("Error closing sem end\n"));
	if (sem_close(philo->sem_eat) != 0)
		return (error_msg("Error closing sem eat\n"));
	if (sem_close(philo->sem_dead) != 0)
		return (error_msg("Error closing sem dead\n"));
	return (true);
}

bool	close_usless_sem(t_philo *philo, int ind)
{
	int	i;

	i = -1;
	while (++i < philo[0].info.nb_philo)
	{
		if (i == ind)
			continue ;
		sem_close(philo[i].sem_dead);
		sem_close(philo[i].sem_eat);
	}
	return (false);
}

bool	wait_philo(t_info info, t_philo *philo, t_info_thread *info_thread)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		if (waitpid(philo[i].pid, NULL, 0) == -1)
		{
			write(2, "Fail on waiting\n", 16);
			return (false);
		}
	}
	free(info_thread);
	return (true);
}
