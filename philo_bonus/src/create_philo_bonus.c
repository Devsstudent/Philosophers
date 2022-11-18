/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:07:24 by odessein          #+#    #+#             */
/*   Updated: 2022/11/18 12:12:00 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"


static void	philo_process(int i, t_sem_info *sem, t_philo *philo,
			t_info_thread *info_thread)
{
	close_usless_sem(philo, i);
	//HANDLE CRASH pthread create
	if (pthread_create(&philo[i].thread_fork, NULL, routine_fork,
			&info_thread[i]) != 0)
		return ;
	if (pthread_create(&philo[i].thread_dead, NULL, routine_dead,
			&info_thread[i]) != 0)
		return ;
	routine(sem, &philo[i]);
	if (pthread_join(philo[i].thread_dead, NULL) != 0)
		return ;
	if (pthread_join(philo[i].thread_fork, NULL) != 0)
		return ;
	end_routine(&philo[i], sem);
	free(info_thread);
}

static bool	create_philo(t_info info, t_sem_info *sem, t_philo *philo,
			t_info_thread *info_thread)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		//HANDLE CRASH FORK
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_process(i, sem, philo, info_thread);
			return (false);
		}
		else
			continue ;
	}
	return (true);
}

static void	cpy_info(t_info info, t_philo *philo, int index)
{
	philo->info.t_to_sleep = info.t_to_sleep;
	philo->info.t_to_eat = info.t_to_eat;
	philo->info.t_to_die = info.t_to_die;
	philo->info.t_eat_max = info.t_eat_max;
	philo->info.nb_philo = info.nb_philo;
	philo->info.t_start = info.t_start;
	philo->id = index + 1;
	philo->eat_turn = 0;
	philo->die = false;
	philo->time_last_eat = philo->info.t_start;
}

static bool	setup_philo_and_info_thread(t_info info, t_sem_info *sem,
			t_philo *philo, t_info_thread *info_thread)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		cpy_info(info, &philo[i], i);
		if (!init_sem_in_philo(&philo[i]))
			return (false);
		info_thread[i].philo = &philo[i];
		info_thread[i].sem = sem;
	}
	return (true);
}

bool	philo_a(t_info info, t_sem_info *sem, t_philo *philo)
{
	t_info_thread	*info_thread;
	int				i;

	info_thread = malloc(sizeof(t_info_thread) * info.nb_philo);
	if (!info_thread)
		return (false);
	if (!setup_philo_and_info_thread(info, sem, philo, info_thread))
		return (false);
	if (!create_philo(info, sem, philo, info_thread))
		return (false);
	i = -1;
	while (++i < info.nb_philo)
	{
		sem_close(philo[i].sem_eat);
		sem_close(philo[i].sem_dead);
	}
	if (!wait_philo(info, philo, info_thread))
	{
		close_sem(sem);
		return (false);
	}
	if (!close_sem(sem))
		return (false);
	return (true);
}
