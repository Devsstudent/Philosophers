/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:53:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/17 17:49:29 by odessein         ###   ########.fr       */
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
	if (does_im_dead(philo))
		return (false);
	
//	long	time;
//	time = get_actual_time();
	while (1)
	{
		//if (sem_wait(sem->catch_fork))
		//	return (error_msg("error post sem\n"));
		//printf("AHAH");
		if (sem->bowl->__align >= 2)
		{
			if (sem_post(sem->catch_fork) != 0)
				return (error_msg("error post sem\n"));
			break ;
		}
	//	if (sem_post(sem->catch_fork) != 0)
	//		return (error_msg("error post sem\n"));
	}
//	if (get_actual_time() - time > 5)
//		printf("time waited to take fork %li\n", get_actual_time() - time);
	if (sem_wait(sem->bowl) != 0)
		return (error_msg("error wait sem\n"));
	if (sem_wait(sem->bowl) != 0)
		return (error_msg("error wait sem\n"));
	if (!display(philo, sem, _FORK))
	{
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
