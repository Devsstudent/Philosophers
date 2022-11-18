/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_fork_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:36:57 by odessein          #+#    #+#             */
/*   Updated: 2022/11/18 11:57:26 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static	bool	alive(t_info_thread *info)
{
	if (get_actual_time() - info->philo->time_last_eat
		>= info->philo->info.t_to_die)
	{
		if (sem_wait(info->sem->write) != 0)
			return (error_msg("Error sem_waiting\n"));
		if (does_im_dead(info->philo))
		{
			if (sem_post(info->philo->sem_eat) != 0)
				return (error_msg("Error sem_posting\n"));
			if (sem_post(info->sem->end) != 0)
				return (error_msg("Error sem_posting\n"));
			if (sem_post(info->sem->write) != 0)
				return (error_msg("Error sem_posting\n"));
			return (false);
		}
		print_str(_DIE, timestamp(info->philo->info.t_start),
			info->philo->id);
		if (sem_post(info->sem->end) != 0)
			return (error_msg("Error sem_posting\n"));
		return (false);
	}
	return (true);
}

static bool	need_eating(t_info_thread *info)
{
	if (info->sem->max->__align >= info->philo->info.nb_philo)
	{
		if (sem_post(info->sem->end) != 0)
			return (error_msg("Error sem_posting\n"));
		return (false);
	}
	return (true);
}

static bool	loop_routine_fork(t_info_thread *info)
{
	while (42)
	{
		if (does_im_dead(info->philo))
			return (false);
		if (sem_wait(info->philo->sem_eat) != 0)
		{
			write(2, "Error sem_waiting\n", 17);
			return (false);
		}
		if (!alive(info))
			break ;
		else if (!need_eating(info))
			break ;
		if (sem_post(info->philo->sem_eat) != 0)
			write(2, "Error sem_posting\n", 17);
		usleep(500);
	}
	return (true);
}

void	*routine_fork(void *content)
{
	t_info_thread	*info;
	long			time_grab_write_sem;

	info = (t_info_thread *) content;
	if (!loop_routine_fork(info))
		return (0);
	if (sem_post(info->philo->sem_eat) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
	time_grab_write_sem = info->philo->info.nb_philo * 500;
	usleep(time_grab_write_sem);
	if (sem_post(info->sem->write) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
	return (0);
}
