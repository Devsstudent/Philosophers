/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:53:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/04 16:45:22 by odessein         ###   ########.fr       */
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
	(void) philo;
	if (sem_wait(sem->bowl) != 0)
	{
		write(2, "error wait sem\n", 15);
		return (false);
	}
//	write(2, "aa\n", 3);
	if (!display(philo, sem, _FORK))
		return (false);
	//write(2, "aa\n", 3);
	if (sem_wait(sem->bowl) != 0)
	{
		write(2, "error wait sem\n", 15);
		return (false);
	}
	if (!display(philo, sem, _FORK))
		return (false);
	//display take fork
	return (true);
}
