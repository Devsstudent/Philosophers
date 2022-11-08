/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:09:06 by odessein          #+#    #+#             */
/*   Updated: 2022/11/08 15:47:55 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	semaphore(t_sem_info *sem, t_info info)
{
	sem_unlink("bowl");
	sem_unlink("write");
	sem_unlink("max");
	sem->bowl = sem_open("bowl", O_CREAT, S_IRWXU, info.nb_philo);
	if (sem->bowl == SEM_FAILED)
	{
		write(2, "Error opening semaphore\n", 24);
		return (false);
	}
	sem->max = sem_open("max", O_CREAT, S_IRWXU, 0);
	if (sem->max == SEM_FAILED)
	{
		write(2, "Error opening semaphore\n", 24);
		return (false);
	}
	sem->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	if (sem->write == SEM_FAILED)
	{
		write(2, "Error opening semaphore\n", 24);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_sem_info	sem;
	t_philo		*philo;

	if (!parse_input(ac, av, &info))
		return (1);
	philo = malloc(sizeof(t_philo) * info.nb_philo);
	if (!philo)
	{
		write(2, "Malloc failed\n", 14);
		free(philo);
		return (2);
	}
	if (!semaphore(&sem, info))
	{
		free(philo);
		return (3);
	}
	if (!philo_a(info, &sem, philo))
	{
		free(philo);
		return (4);
	}
	free(philo);
}
