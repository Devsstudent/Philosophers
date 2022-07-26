/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:30:40 by odessein          #+#    #+#             */
/*   Updated: 2022/07/26 17:19:21 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int ac, char **av)
{
	t_input	input;

	if (!ph_parse(ac, av, &input))
	{
		printf("Error\n");
		return (1);
	}
	input.time_actual = 0;
	ph_get_time(&input);
}

/*
	printf("time at start %llu\n", input.time_actual);
	usleep(1000000); //1 sec
	ph_get_time(&input);
	printf("tmp ecoulee : %llu\n", input.time_actual);
*/
