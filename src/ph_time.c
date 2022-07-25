/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:54:09 by odessein          #+#    #+#             */
/*   Updated: 2022/07/26 00:08:55 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

//Get the current time since the process started running in (ms or nano i dont know)
void	ph_get_time(t_input *input)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	input->time = gettimeofday(&current_time, NULL) - input->time;
}
