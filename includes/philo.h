/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:23:07 by odessein          #+#    #+#             */
/*   Updated: 2022/07/26 00:14:31 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum e_process{
	EATING,
	SLEEPING,
	THINKING
}	t_process;

typedef struct	s_input{
	int	nb_philo;
	int	fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_max_bp;
}		t_input;

typedef struct	s_philo{
	int			id;
	t_process	process;
	int			time_last_eat;
	pthread_t	thread;
	t_input		*info;
	t_bool			fork_right;
	t_bool			fork_left;
}

#endif
