/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:32:35 by odessein          #+#    #+#             */
/*   Updated: 2022/07/25 21:36:26 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	ph_parse(int ac, char **av, t_input *input)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (false);
	i = 1;
	//check int input + not too long
	while (i < ac - 1)
	{
		j = 0;
		while (av[j] != 0)
		{
			if (av[j] < '0' || av[j] > '9')
				return (FALSE);
			j++;
		}
		if (j > 9)
			return (FALSE);
		i++;
	}
	ph_fill_input(ac, av, input);
	return (TRUE);
}

void	ph_fill_input(int ac, char **av, t_input *input)
{
	input->nb_philo = ph_atoi(av[1]);
	if (input->nb_philo > 1)
		input->fork = nb_philo / 2;
	else
		input->fork = 1;
	input->time_to_die = ph_atoi(av[2]);
	input->time_to_eat = ph_atoi(av[3]);
	input->time_to_sleep = ph_atoi(av[4]);
	if (ac == 6)
		input->eat_max_bp = ph_atoi(av[5]);
	else
		input->eat_max_bp = -1;
}
