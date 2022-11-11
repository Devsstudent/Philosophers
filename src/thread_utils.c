/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:56:32 by odessein          #+#    #+#             */
/*   Updated: 2022/11/10 14:54:07 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	clean_end(t_mem_shared *mem_shared)
{
	if (pthread_mutex_destroy(&mem_shared->mutex_eat) != 0)
		return (error_msg("Error destroying mutex\n"));
	if (pthread_mutex_destroy(&mem_shared->mutex_write) != 0)
		return (error_msg("Error destroying mutex\n"));
	if (pthread_mutex_destroy(&mem_shared->mutex_process) != 0)
		return (error_msg("Error destroying mutex\n"));
	if (pthread_mutex_destroy(&mem_shared->mutex_dead) != 0)
		return (error_msg("Error destroying mutex\n"));
	if (pthread_mutex_destroy(&mem_shared->mutex_data) != 0)
		return (error_msg("Error destroying mutex\n"));
	if (pthread_mutex_destroy(&mem_shared->mutex_start) != 0)
		return (error_msg("Error destroying mutex\n"));
	return (true);
}

bool	clean_philo_fork(t_mem_shared *mem_shared, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (pthread_mutex_destroy(&mem_shared->philo[i].mutex_fork) != 0)
			return (error_msg("Error destroying mutex\n"));
	}
	return (true);
}

bool	wait_thread(t_mem_shared *mem_shared, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_join(mem_shared->philo[i].thread, NULL) != 0)
			return (error_msg("fail join thread\n"));
	}
	return (true);
}
