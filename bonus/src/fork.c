/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:53:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/09 16:30:57 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	unlock_fork(t_sem_info *sem)
{
	if (sem_post(sem->bowl) != 0)
	{
		write(2, "error post sem\n", 15);
		return (false);
	}
	if (sem_post(sem->bowl) != 0)
	{
		write(2, "error post sem\n", 15);
		return (false);
	}
	return (true);
}

bool	take_fork(t_philo *philo, t_sem_info *sem)
{
	if (sem_wait(sem->bowl) != 0)
	{
		write(2, "error wait sem\n", 15);
		return (false);
	}
	if (sem_wait(sem->bowl) != 0)
	{
		write(2, "error wait sem\n", 15);
		return (false);
	}
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
