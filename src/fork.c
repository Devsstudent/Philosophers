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

bool	take_fork(t_philo *philo, t_info *info)
{
	if (pthread_mutex_lock(&philo->mutex_fork))
		if (!display(philo, info, _FORK_RIGHT))
			return (false);
	if (philo->id != philo->input.number_of_philo)
	{
		if (pthread_mutex_lock(&info->philo[(philo->id - 1) + 1].mutex_fork))
			if (!display(philo, info, _FORK_LEFT))
				return (false);
	}
	else
	{
		if (pthread_mutex_lock(&info->philo[0].mutex_fork))
			if (!display(philo, info, _FORK_LEFT))
				return (false);
	}
	return (true);
}
