/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:04:41 by odessein          #+#    #+#             */
/*   Updated: 2022/11/07 17:06:27 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	does_im_dead(t_philo *philo, t_sem_info *sem)
{
	long long	time;

	time = get_actual_time();
	if (sem_wait(sem->write) != 0)
	{
		write(2, "error post sem", 15);
		return (true);
	}
	if (get_actual_time() - time >= 50)
	{
		if (sem_post(sem->write) != 0)
		{
			write(2, "error post sem", 15);
			return (true);
		}
		return (true);
	}
	if (get_actual_time() - philo->time_last_eat >= philo->info.t_to_die)
	{
		print_str(_DIE, timestamp(philo->info.t_start), philo->id);
		usleep(50000);
		if (sem_post(sem->write) != 0)
		{
			write(2, "error post sem", 15);
			return (true);
		}
		return (true);
	}
	if (sem_post(sem->write) != 0)
	{
		write(2, "error post sem", 15);
		return (true);
	}
	return (false);
}
