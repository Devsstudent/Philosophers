/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:32:38 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 19:54:26 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	check_dead(t_info *info)
{
	pthread_mutex_lock(&info->mutex_write);
	pthread_mutex_lock(&info->mutex_dead);
	if (info->die)
	{
		pthread_mutex_unlock(&info->mutex_dead);
//		usleep(10000);
		pthread_mutex_unlock(&info->mutex_write);
		return (true);
	}
	pthread_mutex_unlock(&info->mutex_dead);
	pthread_mutex_unlock(&info->mutex_write);
	return (false);
}

bool	does_im_dead(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->mutex_dead);
	if (info->die)
	{
		pthread_mutex_unlock(&info->mutex_dead);
		return (false);
	}
	pthread_mutex_unlock(&info->mutex_dead);
	if (get_actual_time() - philo->time_last_eat > 500)
		printf("value :%li\n", get_actual_time() - philo->time_last_eat);
	if (get_actual_time() - philo->time_last_eat > philo->input.time_to_die)
	{
		printf("value :%li\n", get_actual_time() - philo->time_last_eat);
		pthread_mutex_lock(&info->mutex_dead);
		info->die = true;
		pthread_mutex_unlock(&info->mutex_dead);
		pthread_mutex_lock(&info->mutex_write);
		printf("%li %i died\n",timestamp(philo->input.start_time), philo->id);
		pthread_mutex_unlock(&info->mutex_write);
	}
	return (info->die);
}
