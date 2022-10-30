/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:59:28 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 19:54:08 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	unlock_fork(t_philo *philo, t_info *info)
{
	pthread_mutex_unlock(&philo->mutex_fork);
	if (philo->id != philo->input.number_of_philo)
		pthread_mutex_unlock(&info->philo[(philo->id - 1) + 1].mutex_fork);
	else
		pthread_mutex_unlock(&info->philo[0].mutex_fork);
}

bool	next_using_fork(t_philo *philo, t_philo *philo_next, t_info *info)
{
	long long time_still;

	pthread_mutex_lock(&info->mutex_process);
	if (philo_next->process == EATING)
	{
		pthread_mutex_unlock(&info->mutex_process);
		pthread_mutex_lock(&info->mutex_eat);
		time_still = philo->input.time_to_eat - get_actual_time() - philo_next->time_last_eat;
		pthread_mutex_unlock(&info->mutex_eat);
		if (timestamp(philo->input.start_time) + get_actual_time() + time_still > philo->input.time_to_die)
		{
			usleep(((philo->input.time_to_die - timestamp(philo->input.start_time)) % philo->input.time_to_die) * 1000);
			pthread_mutex_lock(&info->mutex_dead);
			if (info->die)
			{
				pthread_mutex_unlock(&info->mutex_dead);
				return (true);
			}
			info->die = true;
			pthread_mutex_unlock(&info->mutex_dead);
			pthread_mutex_lock(&info->mutex_write);
			printf("%li %i died", timestamp(philo->input.start_time), philo->id);
			pthread_mutex_unlock(&info->mutex_write);
			return (true);
		}
	}
	pthread_mutex_unlock(&info->mutex_process);
	return (false);
	
}

bool	prev_using_fork(t_philo *philo, t_philo *philo_prev, t_info *info)
{
	long long time_still;

	pthread_mutex_lock(&info->mutex_process);
	if (philo_prev->process == EATING)
	{
		pthread_mutex_unlock(&info->mutex_process);
		pthread_mutex_lock(&info->mutex_eat);
		time_still = philo->input.time_to_eat - get_actual_time() - philo_prev->time_last_eat;
		pthread_mutex_unlock(&info->mutex_eat);
	//	printf("%li\n", philo->input.time_to_die - (timestamp(philo->input.start_time) % philo->input.time_to_die));
//		printf("%lli\n", timestamp(philo->input.start_time) + get_actual_time() + time_still);
		if (timestamp(philo->input.start_time) + get_actual_time() + time_still > philo->input.time_to_die)
		{
			pthread_mutex_lock(&info->mutex_write);
			printf("1 : %li ah : %li\n", get_actual_time(), (philo->input.time_to_die - (timestamp(philo->input.start_time) % philo->input.time_to_die)));
			pthread_mutex_unlock(&info->mutex_write);
			
			usleep(((philo->input.time_to_die - timestamp(philo->input.start_time)) % philo->input.time_to_die) * 1000);
			pthread_mutex_lock(&info->mutex_write);
			printf("2 : %li\n", get_actual_time());
			pthread_mutex_unlock(&info->mutex_write);
			pthread_mutex_lock(&info->mutex_dead);
			if (info->die)
			{
				pthread_mutex_unlock(&info->mutex_dead);
				return (true);
			}
			info->die = true;
			pthread_mutex_unlock(&info->mutex_dead);
			pthread_mutex_lock(&info->mutex_write);
			printf("%li %i died bruh", timestamp(philo->input.start_time), philo->id);
			pthread_mutex_unlock(&info->mutex_write);
			return (true);
		}
	}
	pthread_mutex_unlock(&info->mutex_process);
	return (false);
}

bool	can_i_grab_fork(t_philo *philo, t_info *info)
{
	//process precedent using our fork
	if (philo->id == 0)
	{
		if (prev_using_fork(philo, &info->philo[philo->input.number_of_philo], info))
			return (true);
	}
	else
	{
		if (prev_using_fork(philo, &info->philo[philo->id -1 - 1], info))
			return (true);
	}
	//process suivant using his fork
	if (philo->id == philo->input.number_of_philo)
	{
		if (prev_using_fork(philo, &info->philo[0], info))
			return (true);
	}
	else
	{
		if (info->philo[philo->id - 1 + 1].process == EATING)
		{
			if (prev_using_fork(philo, &info->philo[philo->id - 1 + 1], info))
				return (true);
		}
	}
	//2 check return un temps 

	//le temps
	return (false);
}

bool	take_fork(t_philo *philo, t_info *info)
{
//	printf("id %i\n", philo->id);
	if (can_i_grab_fork(philo, info))
		return (false);
	if (!pthread_mutex_lock(&philo->mutex_fork))
	{
		if (!display(philo, info, _FORK_RIGHT))
			return (false);
	}
	if (philo->id != philo->input.number_of_philo)
	{
		if (!pthread_mutex_lock(&info->philo[(philo->id - 1) + 1].mutex_fork))
		{
			if (!display(philo, info, _FORK_LEFT))
				return (false);
		}
	}
	else
	{
		if (!pthread_mutex_lock(&info->philo[0].mutex_fork))
			if (!display(philo, info, _FORK_LEFT))
				return (false);
	}
	return (true);
}
