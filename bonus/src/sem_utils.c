/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:41:19 by odessein          #+#    #+#             */
/*   Updated: 2022/11/08 17:43:44 by odessein         ###   ########.fr       */
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
