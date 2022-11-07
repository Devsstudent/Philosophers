/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:53:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/07 16:26:39 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	unlock_fork(t_philo *philo, t_sem_info *sem)
{
	(void) philo;

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
		return (false);
	if (!display(philo, sem, _FORK))
		return (false);
	return (true);
}
