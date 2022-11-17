/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:26 by odessein          #+#    #+#             */
/*   Updated: 2022/11/17 19:08:56 by odessein         ###   ########.fr       */
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

//fork -> check_dead + free + set_dead

//dead -> set dead to true to each process
//kill -> join fork + kill id correspondant

static bool	create_philo(t_info info, t_sem_info *sem, t_philo *philo, t_info_thread *info_thread)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		//write(2, "AH\n", 3);
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			pthread_create(&philo[i].thread_fork, NULL, routine_fork, &info_thread[i]);
			pthread_create(&philo[i].thread_dead, NULL, routine_dead, &info_thread[i]);
			routine(sem, &philo[i]);
			pthread_join(philo[i].thread_fork, NULL);
			pthread_join(philo[i].thread_dead, NULL);
			if (sem_close(sem->max) != 0)
				write(2, "Error closing sem max\n", 22);
			if (sem_close(sem->write) != 0)
				write(2, "Error closing sem write\n", 24);
			if (sem_close(sem->end) != 0)
				write(2, "Error closing sem end\n", 22);
			if (sem_close(philo[i].sem_eat) != 0)
				write(2, "Error closing sem eat\n", 22);
			printf("id :%i\n", philo[i].id);
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
		//join_here dead && free
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

	info_thread = malloc(sizeof(t_info_thread) * info.nb_philo);
	if (!info_thread)
		return (false);
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
	//memset(&info_thread, 0 ,sizeof(info_thread));
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
