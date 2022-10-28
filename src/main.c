/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:33:57 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 17:38:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_input	input;

	if (!ph_parse(ac, av, &info, &input))
		return (1);
	if (!philo(&info, &input))
		return (2);
}
