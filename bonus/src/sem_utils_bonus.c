/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:41:19 by odessein          #+#    #+#             */
/*   Updated: 2022/11/09 16:49:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	sem_start_unlink(void)
{
	sem_unlink("bowl");
	sem_unlink("write");
	sem_unlink("max");
	sem_unlink("dead");
}

bool	semaphore(t_sem_info *sem, t_info info)
{
	sem_start_unlink();
	sem->bowl = sem_open("bowl", O_CREAT, S_IRWXU, info.nb_philo);
	if (sem->bowl == SEM_FAILED)
		return (error_msg("Error opening semaphore\n"));
	sem->max = sem_open("max", O_CREAT, S_IRWXU, 0);
	if (sem->max == SEM_FAILED)
		return (error_msg("Error opening semaphore\n"));
	sem->dead = sem_open("dead", O_CREAT, S_IRWXU, 0);
	if (sem->dead == SEM_FAILED)
		return (error_msg("Error opening semaphore\n"));
	sem->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	if (sem->write == SEM_FAILED)
		return (error_msg("Error opening semaphore\n"));
	return (true);
}

static bool	_close(sem_t *sem, char *name)
{
	if (sem_close(sem) != 0)
		return (error_msg("Error closing sem\n"));
	if (sem_unlink(name) != 0)
		return (error_msg("Error unlinking sem\n"));
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
	if (!_close(sem->dead, "dead"))
		return (false);
	return (true);
}
