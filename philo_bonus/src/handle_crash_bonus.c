/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_crash_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:21:41 by odessein          #+#    #+#             */
/*   Updated: 2022/11/18 13:00:10 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	handle_crash_create_fork(int i, t_philo *philo)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		pthread_detach(philo[i].thread_dead);
		pthread_detach(philo[i].thread_fork);
		kill(philo[i].pid, SIGKILL);
	}
}

void	handle_crash_join(int i, t_philo *philo)
{
	while (++i < philo[0].info.nb_philo)
	{
		pthread_detach(philo[i].thread_dead);
		pthread_detach(philo[i].thread_fork);
		kill(philo[i].pid, SIGKILL);
	}
}
