/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:26 by odessein          #+#    #+#             */
/*   Updated: 2022/11/14 15:49:38 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <string.h>

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
void	*routine_fork(void *content)
{
	t_info_thread	*info;

	info = (t_info_thread *) content;
	printf("%i\n", info->philo->id);
	while (42)
	{
//		printf("%i", get_actual_time() - info->philo->time_last_eat >= info->philo->info.t_to_die);
		sem_wait(info->sem->eat);
		if (get_actual_time() - info->philo->time_last_eat >= info->philo->info.t_to_die)
			break ;
		sem_post(info->sem->eat);
	}
	 //info->sem->max->__align == info->philo->info.nb_philo;
	sem_post(info->sem->eat);
	//if (sem_post(info->sem_each_philo) != 0)
//	{
//		write(2, "Error sem_posting\n", 17);
//		return (0);
//	}
	if (sem_wait(info->sem->write) != 0)
	{
		write(2, "Error sem_waiting\n", 17);
		return (0);
	}
	print_str(_DIE, timestamp(info->philo->info.t_start), info->philo->id);
	if (sem_post(info->sem->write) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
	sem_close(info->sem->dead);
	sem_close(info->sem->write);
	sem_close(info->sem->max);
	sem_close(info->sem->bowl);
	return (0);
}

//dead -> set dead to true to each process
void	*routine_dead(void *content)
{
	t_info_thread *info;

	info = (t_info_thread *) content;
	if (sem_wait(*info->sem_each_philo) != 0)
	{
		write(2, "Error sem_waiting\n", 17);
		return (0);
	}
	//dead ou write ?? Problem les philo peuvent peut etre display
	if (sem_wait(info->sem->dead) != 0)
	{
		write(2, "Error sem_waiting\n", 17);
		return (0);
	}
	info->philo->die = true;
	if (sem_post(info->sem->dead) != 0)
	{
		write(2, "Error sem_posting\n", 17);
		return (0);
	}
//	if (sem_post(info->sem_each_philo) != 0)
//	{
//		write(2, "Error sem_posting\n", 17);
//		return (0);
//	}
	return (0);
}
//kill -> join fork + kill id correspondant
void	*routine_kill(void *content)
{
	t_info_thread *info;

	info = (t_info_thread *) content;
	printf("routine %p\n", *info->sem_each_philo);
	if (sem_wait(*info->sem_each_philo))
	{
		write(2, "Error sem_waiting\n", 17);
		return (0);
	}
	pthread_join(info->thread_fork, NULL);
	kill(info->philo->pid, SIGTERM);
	return (0);
}

static inline bool fill_info_thread(t_info_thread *info, char *name)
{
//	sem_t	**store;

	info->sem_each_philo =  malloc(sizeof(sem_t *));
	*info->sem_each_philo = sem_open(name, O_CREAT, S_IRWXU, 0);
	free(name);
	if (*info->sem_each_philo == SEM_FAILED)
		return (error_msg("fail opening semaphore sem_each_philo"));
	printf("init :%p\n", *info->sem_each_philo);
	return (true);
}

bool	create_philo(t_info info, t_sem_info *sem, t_philo *philo)
{
	int				i;
	pthread_t		thread_fork;
	pthread_t		thread_dead;
	pthread_t		thread_kill;
	t_info_thread	info_thread;

	i = -1;
	memset(&info_thread, 0 ,sizeof(info_thread));
	while (++i < info.nb_philo)
	{
		cpy_info(info, &philo[i], i);
		info_thread.philo = &philo[i];
		info_thread.sem = sem;
		if (!fill_info_thread(&info_thread, ft_itoa(philo[i].id)))
			return (false);
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			pthread_create(&thread_fork, NULL, routine_fork, &info_thread);
			routine(sem, &philo[i]);
			return (false);
		}
		else
		{
			info_thread.thread_fork = thread_fork;
			pthread_create(&thread_dead, NULL, routine_dead, &info_thread);
			pthread_create(&thread_kill, NULL, routine_kill, &info_thread);
			continue ;
		}
	}
	return (true);
}

bool	wait_philo(t_info info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		//pthread_join(thread_dead, NULL)
		//pthread_join(thread_kill, NULL)
		//join_here dead && free
		if (waitpid(philo[i].pid, NULL, 0) == -1)
		{
			write(2, "Fail on waiting\n", 16);
			return (false);
		}
	}
	return (true);
}

bool	philo_a(t_info info, t_sem_info *sem, t_philo *philo)
{
	if (!create_philo(info, sem, philo))
		return (false);
	if (!wait_philo(info, philo))
	{
		close_sem(sem);
		return (false);
	}
	if (!close_sem(sem))
		return (false);
	return (true);
}
