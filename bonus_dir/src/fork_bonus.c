/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:53:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/12 21:37:31 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	unlock_fork(t_sem_info *sem)
{
	if (sem_post(sem->bowl) != 0)
		return (error_msg("error post sem\n"));
	if (sem_post(sem->bowl) != 0)
		return (error_msg("error post sem\n"));
	return (true);
}

bool	take_fork(t_philo *philo, t_sem_info *sem)
{
	long long	time;
	long long	daa;

	time = get_actual_time()- philo->time_last_eat;
	printf("time 1 : %lli\n", time);
	daa = philo->info.t_to_die - time;
	printf("dead: %lli\n", time);
	if (sem_wait(sem->bowl) != 0)
		return (error_msg("error wait sem\n"));
	if (sem_wait(sem->bowl) != 0)
		return (error_msg("error wait sem\n"));
	if (!display(philo, sem, _FORK))
	{
		if (sem_post(sem->dead) != 0)
		{
			write(2, "error post sem", 15);
			return (false);
		}
		if (sem->dead->__align <= 1
			&& sem->max->__align != philo->info.nb_philo)
		printf("%lli %i died\n", time + daa, philo->id);
		if (!post_write(sem))
			return (false);
		unlock_fork(sem);
		return (false);
	}
	if (!display(philo, sem, _FORK))
	{
		unlock_fork(sem);
		return (false);
	}
	return (true);
}
