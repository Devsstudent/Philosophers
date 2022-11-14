/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:04:44 by odessein          #+#    #+#             */
/*   Updated: 2022/11/03 13:06:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static bool	destroy_all(pthread_mutex_t **arr, int *i)
{
	while ((*i) > -1)
	{
		if (pthread_mutex_destroy(arr[*i]) != 0)
		{
			write(2, "Error destroying mutex OUPPS\n", 29);
			return (false);
		}
		(*i)--;
	}
	return (true);
}

static bool	init_mutex_add_arr(pthread_mutex_t *to_add, int *i,
			pthread_mutex_t **arr)
{
	if (pthread_mutex_init(to_add, NULL) != 0)
	{
		if (!destroy_all(arr, i))
		{
			free(arr);
			return (false);
		}
		free(arr);
		return (false);
	}
	arr[*i] = to_add;
	(*i)++;
	return (true);
}

bool	init_mutex(t_mem_shared *mem_shared, int *i, pthread_mutex_t **arr)
{
	if (!init_mutex_add_arr(&mem_shared->mutex_write, i, arr))
		return (false);
	if (!init_mutex_add_arr(&mem_shared->mutex_eat, i, arr))
		return (false);
	if (!init_mutex_add_arr(&mem_shared->mutex_dead, i, arr))
		return (false);
	if (!init_mutex_add_arr(&mem_shared->mutex_process, i, arr))
		return (false);
	if (!init_mutex_add_arr(&mem_shared->mutex_data, i, arr))
		return (false);
	if (!init_mutex_add_arr(&mem_shared->mutex_start, i, arr))
		return (false);
	return (true);
}
