/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:41:51 by odessein          #+#    #+#             */
/*   Updated: 2022/11/08 18:37:54 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	init_philo(int ind, t_philo *philo, t_info *info,
				t_mem_shared *mem_shared)
{
	philo->id = ind + 1;
	philo->info.nb_philo = info->nb_philo;
	philo->info.t_to_die = info->t_to_die;
	philo->info.t_to_sleep = info->t_to_sleep;
	philo->info.t_to_eat = info->t_to_eat;
	philo->info.t_start = info->t_start;
	philo->info.t_eat_max = info->t_eat_max;
	philo->time_last_eat = info->t_start;
	pthread_mutex_lock(&mem_shared->mutex_start);
	philo->created = false;
	pthread_mutex_unlock(&mem_shared->mutex_start);
	if (pthread_mutex_init(&philo->mutex_fork, NULL) != 0)
	{
		write(2, "fail init mutex\n", 16);
		return (false);
	}
	pthread_mutex_lock(&mem_shared->mutex_process);
	philo->process = UNDEF;
	pthread_mutex_unlock(&mem_shared->mutex_process);
	return (true);
}

static bool	wait_thread(t_mem_shared *mem_shared, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_join(mem_shared->philo[i].thread, NULL) != 0)
		{
			write(2, "fail join thread\n", 17);
			return (false);
		}
	}
	return (true);
}

static bool	create_philo(t_info *info, t_mem_shared *mem_shared)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		mem_shared->philo[i].mem_shared = mem_shared;
		if (!init_philo(i, &mem_shared->philo[i], info, mem_shared))
			return (false);
		if (pthread_create(&mem_shared->philo[i].thread, NULL, routine,
				&mem_shared->philo[i]) != 0)
		{
			write(2, "fail create philo\n", 18);
			if (!wait_thread(mem_shared, i))
				return (false);
			return (false);
		}
	}
	return (true);
}

static bool	clean_philo_fork(t_mem_shared *mem_shared, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (pthread_mutex_destroy(&mem_shared->philo[i].mutex_fork) != 0)
		{
			write(2, "Error destroying mutex\n", 23);
			return (false);
		}
	}
	return (true);
}

bool	clean_end(t_mem_shared *mem_shared, t_info *info)
{
	if (!clean_philo_fork(mem_shared, info))
		return (false);
	if (pthread_mutex_destroy(&mem_shared->mutex_eat) != 0)
	{
		write(2, "Error destroying mutex\n", 23);
		return (false);
	}
	if (pthread_mutex_destroy(&mem_shared->mutex_write) != 0)
	{
		write(2, "Error destroying mutex\n", 23);
		return (false);
	}
	if (pthread_mutex_destroy(&mem_shared->mutex_process) != 0)
	{
		write(2, "Error destroying mutex\n", 23);
		return (false);
	}
	if (pthread_mutex_destroy(&mem_shared->mutex_dead) != 0)
	{
		write(2, "Error destroying mutex\n", 23);
		return (false);
	}
	if (pthread_mutex_destroy(&mem_shared->mutex_data) != 0)
	{
		write(2, "Error destroying mutex\n", 23);
		return (false);
	}
	if (pthread_mutex_destroy(&mem_shared->mutex_start) != 0)
	{
		write(2, "Error destroying mutex\n", 23);
		return (false);
	}
	return (true);
}

bool	philo(t_mem_shared *mem_shared, t_info *info)
{
	if (info->t_eat_max == 0)
		return (true);
	mem_shared->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!mem_shared->philo)
	{
		clean_philo_fork(mem_shared, info);
		return (false);
	}
	if (!create_philo(info, mem_shared))
	{
		return (false);
	}
	while (!check_dead(mem_shared, info->nb_philo))
	{
	}
	if (!wait_thread(mem_shared, info->nb_philo))
	{
		free(mem_shared->philo);
		return (false);
	}
	free(mem_shared->philo);
	return (true);
}
