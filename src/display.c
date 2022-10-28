/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:27:08 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 21:22:22 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	choose_str(t_disp state, char **str)
{
	if (state == _EAT)
		*str = EAT;
	else if (state == _SLEEP)
		*str = SLEEP;
	else if (state == _THINK)
		*str = THINK;
	else if (state == _FORK_LEFT || state == _FORK_RIGHT)
		*str = FORK;
}

bool	display(t_philo *philo, t_info *info, t_disp state)
{
	long int	timestamp_v;
	char		*str;

	choose_str(state, &str);
	timestamp_v = timestamp(philo->input.start_time);
	if (timestamp_v < 0)
		return (false);
	pthread_mutex_lock(&info->mutex_write);
	pthread_mutex_lock(&info->mutex_dead);
	if (info->die)
	{
		pthread_mutex_unlock(&info->mutex_dead);
		pthread_mutex_unlock(&info->mutex_write);
		if (state == _EAT)
			unlock_fork(philo, info);
		else if (state == _FORK_RIGHT)
			pthread_mutex_unlock(&philo->mutex_fork);
		else if (state == _FORK_LEFT)
			unlock_fork(philo, info);
		return (false);
	}
	pthread_mutex_unlock(&info->mutex_dead);
	printf("%ld %i %s\n", timestamp_v, philo->id, str);
	pthread_mutex_unlock(&info->mutex_write);
	return (true);
}
