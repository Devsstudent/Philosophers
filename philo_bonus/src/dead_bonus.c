/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:04:41 by odessein          #+#    #+#             */
/*   Updated: 2022/11/14 14:14:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	check_if_someone_dead(t_sem_info *sem, long long time)
{
	if (sem_wait(sem->write) != 0)
	{
		write(2, "error wait sem", 15);
		return (true);
	}
	if (get_actual_time() - time >= 45)
	{
		if (sem_post(sem->write) != 0)
		{
			write(2, "error post sem", 15);
			return (true);
		}
		return (true);
	}
	return (false);
}

bool	post_write(t_sem_info *sem)
{
	if (sem_post(sem->write) != 0)
	{
		write(2, "error post sem", 15);
		return (true);
	}
	return (true);
}

bool	does_im_dead(t_philo *philo, t_sem_info *sem)
{
	if (sem_wait(sem->dead))
	{
		write(2, "error wait sem", 15);
		return (true);
	}
	if (philo->die)
	{
		if (sem_post(sem->dead) != 0)
		{
			write(2, "error post sem", 15);
			return (true);
		}
		return (true);
	}
	if (sem_post(sem->dead) != 0)
	{
		write(2, "error post sem", 15);
		return (true);
	}
	return (false);
}

void	setup_dead(t_sem_info *sem)
{
	if (sem_wait(sem->write) != 0)
		write(2, "error post sem", 15);
	usleep(50000);
	if (sem_post(sem->write) != 0)
		write(2, "error post sem", 15);
}
