/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:27:45 by odessein          #+#    #+#             */
/*   Updated: 2022/11/17 22:40:41 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	init_sem_in_philo(t_philo *philo)
{
	char	*name;
	char	*name2;

	name = ft_itoa(philo->id);
	name2 = ft_strjoin(name, "_eat");
	philo->sem_eat = sem_open(name2, O_CREAT, S_IRWXU, 1);
	free(name2);
	name2 = ft_strjoin(name, "_dead");
	philo->sem_dead = sem_open(name2, O_CREAT, S_IRWXU, 1);
	free(name2);
	free(name);
	if (philo->sem_dead == SEM_FAILED)
		return (false);
	if (philo->sem_eat == SEM_FAILED)
		return (false);
	return (true);
}

void	*routine_fork(void *content)
{
	t_info_thread	*info;
	long			value;
	long			time_grab_write_sem;

	info = (t_info_thread *) content;
	while (42)
	{
		//if (info->sem->end->__align >= 1 && info->sem->end->__align < 200)
		//	return (0);
		if (does_im_dead(info->philo))
			return (0);
		if (sem_wait(info->philo->sem_eat) > 0)
		{
			write(2, "Error sem_waiting\n", 17);
			return (0);
		}
		value = info->sem->max->__align;
		if (get_actual_time() - info->philo->time_last_eat
			>= info->philo->info.t_to_die)
		{
			if (sem_wait(info->sem->write) != 0)
			{
				write(2, "Error sem_waiting\n", 17);
				return (0);
			}
			if (does_im_dead(info->philo))
			{
				if (sem_post(info->philo->sem_eat) != 0)
					write(2, "Error sem_posting\n", 17);
				if (sem_post(info->sem->end) != 0)
				{
					write(2, "Error sem_posting\n", 17);
					return (0);
				}
				if (sem_post(info->sem->write) != 0)
				{
					write(2, "Error sem_posting\n", 17);
					return (0);
				}
				return (0);
			}
			print_str(_DIE, timestamp(info->philo->info.t_start),
				info->philo->id);
			if (sem_post(info->sem->end) != 0)
			{
				write(2, "Error sem_posting\n", 17);
				return (0);
			}
			break ;
		}
		else if (value == info->philo->info.nb_philo)
		{
			//MARCHE PAS
			if (sem_post(info->sem->end) != 0)
			{
				write(2, "Error sem_posting\n", 17);
				return (0);
			}
			break ;
		}
		if (sem_post(info->philo->sem_eat) != 0)
			write(2, "Error sem_posting\n", 17);
		usleep(500);
	}
	sem_post(info->philo->sem_eat);
	time_grab_write_sem = info->philo->info.nb_philo * 500;
	usleep(time_grab_write_sem);
	if (sem_post(info->sem->write) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
	return (0);
}

void	*routine_dead(void *content)
{
	t_info_thread	*info;

	info = (t_info_thread *) content;
	if (sem_wait(info->sem->end) != 0)
	{
		write(2, "Error sem_waiting\n", 17);
		return (0);
	}
	if (sem_wait(info->philo->sem_dead) != 0)
	{
		write(2, "Error sem_waiting\n", 17);
		return (0);
	}
	info->philo->die = true;
	if (sem_post(info->philo->sem_dead) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
	if (sem_post(info->sem->end) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
	return (0);
}
