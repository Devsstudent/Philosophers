/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:26 by odessein          #+#    #+#             */
/*   Updated: 2022/11/08 15:35:49 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	_close(sem_t *sem, char *name)
{
	if (sem_close(sem) != 0)
	{
		write(2, "Error closing sem\n", 18);
		return (false);
	}
	if (sem_unlink(name) != 0)
	{
		write(2, "Error unlinking sem\n", 21);
		return (false);
	}
	return (true);
}

bool	close_sem(t_sem_info *sem)
{
	if (!_close(sem->write, "write"))
		return (false);
	if (!_close(sem->max, "max"))
		return (false);
	if (!_close(sem->bowl, "bowl"))
		return (false);
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
	philo->process = UNDEF;
	philo->time_last_eat = philo->info.t_start;
}

bool	create_philo(t_info info, t_sem_info *sem, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		cpy_info(info, &philo[i], i);
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			routine(sem, &philo[i]);
			return (false);
		}
		else
			continue ;
	}
	return (true);
}

bool	wait_philo(t_info info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info.nb_philo)
	{
		kill(philo[i].pid, SIGTERM);
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
	while (!check_dead(sem, info))
	{
	}
	if (!wait_philo(info, philo))
	{
		close_sem(sem);
		return (false);
	}
	if (!close_sem(sem))
		return (false);
	return (true);
}
