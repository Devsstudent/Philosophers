/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:04:41 by odessein          #+#    #+#             */
/*   Updated: 2022/11/09 17:42:36 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	check_if_someone_dead(t_sem_info *sem, long long time)
{
	if (sem_wait(sem->write) != 0)
	{
		write(2, "error post sem", 15);
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
	long long	time;

	time = get_actual_time();
	if (check_if_someone_dead(sem, time))
		return (true);
	if (get_actual_time() - philo->time_last_eat >= philo->info.t_to_die || sem->max->__align == philo->info.nb_philo)
	{
		if (sem_post(sem->dead) != 0)
		{
			write(2, "error post sem", 15);
			return (false);
		}
		if (sem->dead->__align <= 1 && sem->max->__align != philo->info.nb_philo)
			print_str(_DIE, timestamp(philo->info.t_start), philo->id);
		usleep(50000);
		if (!post_write(sem))
			return (false);
		return (true);
	}
	if (!post_write(sem))
		return (false);
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
