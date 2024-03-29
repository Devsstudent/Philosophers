/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:11:59 by odessein          #+#    #+#             */
/*   Updated: 2022/11/10 14:55:35 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int ac, char **av)
{
	t_mem_shared	mem_shared;
	t_info			info;

	if (!parse_input(ac, av, &info, &mem_shared))
		return (1);
	if (!philo(&mem_shared, &info))
	{
		clean_end(&mem_shared);
		return (2);
	}
	if (!clean_end(&mem_shared))
		return (3);
}
