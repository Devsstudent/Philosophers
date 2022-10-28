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

bool	can_i_grab_fork(t_philo *philo, t_info *info)
{
	//process precedent using our fork
	pthread_mutex_lock(&info->mutex_process);
	if (philo->id == 0)
	{
		if (info->philo[philo->input.number_of_philo].process == EATING)
		{
			long time_still;
			pthread_mutex_unlock(&info->mutex_process);
			pthread_mutex_lock(&info->mutex_eat);
			time_still = philo->input.time_to_eat - get_actual_time() - info->philo[philo->input.number_of_philo].time_last_eat;
			pthread_mutex_unlock(&info->mutex_eat);
			if (get_actual_time() + time_still > philo->input.time_to_die)
			{
				//usleep du temps restant avant la mort 
				usleep(philo->input.time_to_die - (timestamp(philo->input.start_time) % philo->input->time_to_die));
				//print die
				//setup le bail a 1 etc
				
			}
		}
	}
	else
	{
		if (info->philo[philo->id - 1 - 1].process == EATING)
		{
			long time_still;
			pthread_mutex_unlock(&info->mutex_process);
			pthread_mutex_lock(&info->mutex_eat);
			time_still = philo->input.time_to_eat - get_actual_time() - info->philo[philo->id - 1 - 1].time_last_eat;
			pthread_mutex_unlock(&info->mutex_eat);
			if (get_actual_time() + time_still > philo->input.time_to_die)
			{
				//usleep du temps restant avant la mort 
				usleep(philo->input.time_to_die - (timestamp(philo->input.start_time) % philo->input->time_to_die));
				//print die
				//setup le bail a 1 etc
				
			}
		}

	}
	//process suivant using his fork
	if (philo->id == philo->input.number_of_philo)
	{
		if (info->philo[0].process == EATING)
		{
			long time_still;
			pthread_mutex_unlock(&info->mutex_process);
			pthread_mutex_lock(&info->mutex_eat);
			time_still = philo->input.time_to_eat - get_actual_time() - info->philo[0].time_last_eat;
			pthread_mutex_unlock(&info->mutex_eat);
			if (get_actual_time() + time_still > philo->input.time_to_die)
			{
				//usleep du temps restant avant la mort 
				usleep(philo->input.time_to_die - (timestamp(philo->input.start_time) % philo->input->time_to_die));
				//print die
				//setup le bail a 1 etc
				
			}
		}
	}
	else
	if (info->philo[philo->id - 1 + 1].process == EATING)
	{
		long time_still;
		pthread_mutex_unlock(&info->mutex_process);
		pthread_mutex_lock(&info->mutex_eat);
		time_still = philo->input.time_to_eat - get_actual_time() - info->philo[philo->id - 1 + 1].time_last_eat;
		pthread_mutex_unlock(&info->mutex_eat);
		if (get_actual_time() + time_still > philo->input.time_to_die)
		{
			//usleep du temps restant avant la mort 
			usleep(philo->input.time_to_die - (timestamp(philo->input.start_time) % philo->input->time_to_die));
			//print die
			//setup le bail a 1 etc
			
		}
}
	//2 check return un temps 

	//le temps
	return (true);
}

bool	take_fork(t_philo *philo, t_info *info)
{
	long long time;

	time = get_actual_time() - philo->time_last_eat;
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
