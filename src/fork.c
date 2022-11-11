/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:36:00 by odessein          #+#    #+#             */
/*   Updated: 2022/11/03 11:52:43 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	unlock_fork(t_philo *philo, t_mem_shared *mem_shared)
{
	pthread_mutex_lock(&mem_shared->mutex_data);
	if (philo->right->__data.__lock)
		pthread_mutex_unlock(philo->right);
	if (philo->left->__data.__lock)
		pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&mem_shared->mutex_data);
	return (true);
}

static bool	pair_taking_fork(t_philo *philo, t_mem_shared *mem_shared)
{
	if (philo->id % 2 == 0
		|| (philo->id == philo->info.nb_philo && philo->info.nb_philo % 2 == 0))
	{
		if (!pthread_mutex_lock(philo->right)
			&& !pthread_mutex_lock(philo->left))
		{
			if (does_im_dead(philo, mem_shared))
			{
				unlock_fork(philo, mem_shared);
				return (false);
			}
			if (!(display(philo, mem_shared, _FORK)))
				return (false);
		}
	}
	return (true);
}

bool	take_fork(t_philo *philo, t_mem_shared *mem_shared)
{
	if (!pair_taking_fork(philo, mem_shared))
		return (false);
	if (philo->id % 2 == 1)
	{
		if (!pthread_mutex_lock(philo->left)
			&& !pthread_mutex_lock(philo->right))
		{
			if (does_im_dead(philo, mem_shared))
			{
				unlock_fork(philo, mem_shared);
				return (false);
			}
			if (!(display(philo, mem_shared, _FORK)))
				return (false);
		}
	}
	return (true);
}
