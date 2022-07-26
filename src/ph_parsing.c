/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:32:35 by odessein          #+#    #+#             */
/*   Updated: 2022/07/26 16:23:11 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

//check int input + not too long and enough arg
bool	ph_parse(int ac, char **av, t_input *input)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (false);
	i = 1;
	while (i < ac - 1)
	{
		j = 0;
		while (av[i][j] != 0)
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (false);
			j++;
		}
		if (j > 9)
			return (false);
		i++;
	}
	ph_fill_input(ac, av, input);
	return (true);
}

void	ph_fill_input(int ac, char **av, t_input *input)
{
	input->nb_philo = ph_atoi(av[1]);
	input->time_to_die = ph_atoi(av[2]);
	input->time_to_eat = ph_atoi(av[3]);
	input->time_to_sleep = ph_atoi(av[4]);
	if (ac == 6)
		input->eat_max_bp = ph_atoi(av[5]);
	else
		input->eat_max_bp = -1;
}
