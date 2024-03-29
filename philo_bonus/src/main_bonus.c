/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:09:06 by odessein          #+#    #+#             */
/*   Updated: 2022/11/08 17:42:13 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

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
