/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:38:25 by odessein          #+#    #+#             */
/*   Updated: 2022/10/28 21:39:04 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include "sys/time.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "stdbool.h"
# include "stdlib.h"

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define FORK "has taken a fork\n"
# define DIE "died\n"

typedef struct s_philo t_philo;

typedef enum e_disp{
	_EAT,
	_SLEEP,
	_THINK,
	_FORK_LEFT,
	_FORK_RIGHT,
	_DIE
}	t_disp;

typedef enum e_process{
	EATING,
	SLEEPING,
	THINKING,
	FORKING,
	UNDEF
}	t_process;

typedef struct s_input{
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	time_must_eat;
	int			number_of_philo;
	long int	start_time;
}				t_input;

typedef struct s_info {
	t_philo	*philo;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_start;
	bool		die;
	bool		start;
	int			i_fail;
}	t_info;

typedef struct s_philo {
	pthread_t	thread;
	t_info		*info;
	int			id;
	int			eat_turn;
	bool		created;
	pthread_mutex_t	mutex_fork;
	t_process	process;
	long int	time_last_eat;
	t_input		input;
}	t_philo;
//routine.c
void	*routine(void *philoo);

//fork.c
void	unlock_fork(t_philo *philo, t_info *info);
bool	take_fork(t_philo *philo, t_info *info);

//philo.c
bool	philo(t_info *info, t_input *input);


//time.c
long int	timestamp(unsigned long start_time);
long int	get_actual_time(void);
bool		sleep_loop(unsigned long ms, t_info *info, t_philo *philo);

//dead.c
bool	check_dead(t_info *info);
bool	does_im_dead(t_philo *philo, t_info *info);

//utils.c
int		ph_atoi(const char *nptr);
bool	ph_isdigit(int c);

//parsing.c
bool	ph_parse(int ac, char **av, t_info *info, t_input *input);

//action.c
bool	sleeping(t_philo *philo, t_info *info);
bool	eating(t_philo *philo, t_info *info);
bool	thinking(t_philo *philo, t_info *info);

//display.c
bool	display(t_philo *philo, t_info *info, t_disp state);
#endif
