/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:53:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/18 10:43:28 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	check_two_fork_available(t_sem_info *sem)
{
	while (1)
	{
		if (sem->bowl->__align >= 2)
		{
			if (sem_post(sem->catch_fork) != 0)
				return (error_msg("error post sem\n"));
			break ;
		}
	}
	return (true);
}

bool	unlock_fork(t_sem_info *sem)
{
	if (sem_post(sem->bowl) != 0)
		return (error_msg("error post sem\n"));
	if (sem_post(sem->bowl) != 0)
		return (error_msg("error post sem\n"));
	return (true);
}

bool	take_fork(t_philo *philo, t_sem_info *sem)
{
	if (does_im_dead(philo))
		return (false);
	if (!check_two_fork_available(sem))
		return (false);
	if (sem_wait(sem->bowl) != 0)
		return (error_msg("error wait sem\n"));
	if (sem_wait(sem->bowl) != 0)
		return (error_msg("error wait sem\n"));
	if (!display(philo, sem, _FORK))
	{
		unlock_fork(sem);
		return (false);
	}
	if (!display(philo, sem, _FORK))
	{
		unlock_fork(sem);
		return (false);
	}
	return (true);
}
