/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:28:21 by odessein          #+#    #+#             */
/*   Updated: 2022/11/12 21:39:47 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long int	timestamp(unsigned long start_time)
{
	struct timeval	time;
	unsigned long	res;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	res = (time.tv_sec * 1000000 + time.tv_usec) / 1000;
	return (res - start_time);
}

bool	sleep_loop(unsigned long ms, t_philo *philo, t_sem_info *sem)
{
	unsigned long	time;

	time = get_actual_time();
	while (get_actual_time() - time < ms)
	{
		if (does_im_dead(philo, sem))
			return (false);
		usleep(500);
	}
	return (true);
}

long int	get_actual_time(void)
{
	struct timeval	time;
	unsigned long	res;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	res = (time.tv_sec * 1000000 + time.tv_usec) / 1000;
	return (res);
}
