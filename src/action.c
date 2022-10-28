/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:29:55 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 19:53:11 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	eating(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->mutex_process);
	philo->process = EATING;
	pthread_mutex_unlock(&info->mutex_process);
	pthread_mutex_lock(&info->mutex_eat);
	philo->time_last_eat = get_actual_time();
	pthread_mutex_unlock(&info->mutex_eat);
	if (!display(philo, info, _EAT))
		return (false);
	if (!sleep_loop(philo->input.time_to_eat, info, philo))
		return (false);
	unlock_fork(philo, info);
	return (true);
}

bool	sleeping(t_philo *philo, t_info *info)
{
	if (!display(philo, info, _SLEEP))
		return (false);
	if (!sleep_loop(philo->input.time_to_sleep, info, philo))
		return (false);
	return (true);
}

bool	thinking(t_philo *philo, t_info *info)
{
	long long	think_time;

	if (!display(philo, info, _THINK))
		return (false);
	think_time = philo->input.time_to_die - (philo->input.time_to_sleep + philo->input.time_to_eat) - 5;
	if (think_time > 0 && (philo->input.number_of_philo ^ 1) == 0)
		if (!sleep_loop(philo->input.time_to_sleep, info, philo))
			return (false);
	return (true);
}
