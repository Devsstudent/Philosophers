/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:41:51 by odessein          #+#    #+#             */
/*   Updated: 2022/11/11 15:54:00 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	init_philo(int ind, t_philo *philo, t_info *info)
{
	philo->id = ind + 1;
	philo->info.nb_philo = info->nb_philo;
	philo->info.t_to_die = info->t_to_die;
	philo->info.t_to_sleep = info->t_to_sleep;
	philo->info.t_to_eat = info->t_to_eat;
	philo->info.t_start = info->t_start;
	philo->info.t_eat_max = info->t_eat_max;
	philo->time_last_eat = info->t_start;
	philo->created = false;
	if (pthread_mutex_init(&philo->mutex_fork, NULL) != 0)
		return (error_msg("fail init mutex\n"));
	philo->right = &philo->mutex_fork;
	philo->process = UNDEF;
	return (true);
}

static	bool	init_each_philo(t_info *info, t_mem_shared *mem_shared)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < info->nb_philo)
	{
		mem_shared->philo[i].mem_shared = mem_shared;
		if (!init_philo(i, &mem_shared->philo[i], info))
			return (false);
	}
	i = -1;
	while (++i < info->nb_philo)
	{
		philo = &mem_shared->philo[i];
		if (philo->id != philo->info.nb_philo)
			philo->left = &mem_shared->philo[mem_shared
				->philo[i].id].mutex_fork;
		else
			philo->left = &mem_shared->philo[0].mutex_fork;
	}
	return (true);
}

static bool	create_philo(t_info *info, t_mem_shared *mem_shared)
{
	int	i;

	i = -1;
	if (!init_each_philo(info, mem_shared))
		return (false);
	while (++i < info->nb_philo)
	{
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

bool	philo(t_mem_shared *mem_shared, t_info *info)
{
	if (info->t_eat_max == 0)
		return (true);
	mem_shared->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!mem_shared->philo)
		if (clean_philo_fork(mem_shared, info))
			return (false);
	if (!create_philo(info, mem_shared))
	{
		clean_philo_fork(mem_shared, info);
		free(mem_shared->philo);
		return (false);
	}
	while (!check_dead(mem_shared, info->nb_philo))
	{
	}
	if (!wait_thread(mem_shared, info->nb_philo))
	{
		clean_philo_fork(mem_shared, info);
		free(mem_shared->philo);
		return (false);
	}
	if (!clean_philo_fork(mem_shared, info))
		return (false);
	free(mem_shared->philo);
	return (true);
}
