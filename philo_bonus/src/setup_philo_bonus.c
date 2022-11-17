/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:26 by odessein          #+#    #+#             */
/*   Updated: 2022/11/17 22:33:44 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

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

static bool	end_routine(t_philo *philo, t_sem_info *sem)
{
	if (sem_close(sem->max) != 0)
		return (error_msg("Error closing sem max\n"));
	if (sem_close(sem->bowl) != 0)
		return (error_msg("Error closing sem bowl\n"));
	if (sem_close(sem->write) != 0)
		return (error_msg("Error closing sem write\n"));
	if (sem_close(sem->end) != 0)
		return (error_msg("Error closing sem end\n"));
	if (sem_close(philo->sem_eat) != 0)
		return (error_msg("Error closing sem eat\n"));
	if (sem_close(philo->sem_dead) != 0)
		return (error_msg("Error closing sem dead\n"));
	return (true);
	//LOOP CLEAN SEMAPHORE EACH PHILO
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
			//HANDLE CRASH pthread create
			pthread_create(&philo[i].thread_fork, NULL, routine_fork,
				&info_thread[i]);
			pthread_create(&philo[i].thread_dead, NULL, routine_dead,
				&info_thread[i]);
			routine(sem, &philo[i]);
			pthread_join(philo[i].thread_dead, NULL);
			pthread_join(philo[i].thread_fork, NULL);
			end_routine(&philo[i], sem);
			free(info_thread);
			return (false);
		}
		else
			continue ;
	}
	return (true);
}

static bool	wait_philo(t_info info, t_philo *philo, t_info_thread *info_thread)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		if (waitpid(philo[i].pid, NULL, 0) == -1)
		{
			write(2, "Fail on waiting\n", 16);
			return (false);
		}
	}
	free(info_thread);
	return (true);
}

bool	philo_a(t_info info, t_sem_info *sem, t_philo *philo)
{
	t_info_thread	*info_thread;
	int				i;

	info_thread = malloc(sizeof(t_info_thread) * info.nb_philo);
	if (!info_thread)
		return (false);
	i = -1;
	while (++i < info.nb_philo)
	{
		cpy_info(info, &philo[i], i);
		if (!init_sem_in_philo(&philo[i]))
			return (false);
		info_thread[i].philo = &philo[i];
		info_thread[i].sem = sem;
	}
	if (!create_philo(info, sem, philo, info_thread))
		return (false);
	if (!wait_philo(info, philo, info_thread))
	{
		close_sem(sem);
		return (false);
	}
	if (!close_sem(sem))
		return (false);
	return (true);
}
