/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:23:07 by odessein          #+#    #+#             */
/*   Updated: 2022/07/27 12:27:30 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

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
	unsigned long long time_actual;
}		t_input;

typedef struct	s_philo{
	int			id;
	t_process	process;
	int			time_last_eat;
	pthread_t	thread;
	t_input		*info;
	bool			fork_right;
	bool			fork_left;
}				t_philo;

void	*routine_philo(void *philo);
bool	ph_create_thread(t_philo *philo, t_input *input);
bool	ph_parse(int ac, char **av, t_input *input);
void	ph_fill_input(int ac, char **av, t_input *input);
int		ph_atoi(const char *nptr);
void	ph_get_time(t_input *input);
bool	ph_isdigit(int c);

#endif
