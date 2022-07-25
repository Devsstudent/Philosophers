/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:36:41 by odessein          #+#    #+#             */
/*   Updated: 2022/07/26 00:28:49 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

//At the start should wait to start process about if it is pair or impair -> if pair 

=>//Idea of time function get_time etc to display it and know from which time the philo eated last time



//Loop create thread for each philo ! Need to store the return value of the pthread_create
//Send the routine function to each thread

//What to put in the routine function 
//Attribution of the fork

//Checking if a philo is dead or not ! 
//Then join them

bool	ph_create_thread(t_philo *philo, t_input *input)
{
	int	i;
	philo = malloc(sizeof(t_philo) * input->nb_philo);
	if (!philo)
		return (false);
	i = 0;
	while (i < input->nb_philo)
	{
		philo[i].id = i + 1;
		if (pthread_create(philo[1].thread, NULL, &(routine_philo), input, philo[i]) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_join(philo[1].thread, NULL) != 0)
			return (false);
		i++;
	}
}

