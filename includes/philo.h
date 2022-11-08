/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:38:29 by odessein          #+#    #+#             */
/*   Updated: 2022/11/08 18:38:41 by odessein         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef enum e_disp{
	_EAT,
	_SLEEP,
	_THINK,
	_FORK,
	_DIE
}	t_disp;

typedef enum e_process{
	EATING,
	SLEEPING,
	THINKING,
	UNDEF
}	t_process;

//thread qui s'occupe des locks et des unlock :)
typedef struct s_info {
	long int	t_to_sleep;
	long int	t_to_eat;
	long int	t_to_die;
	long int	t_eat_max;
	long int	t_start;
	long int	nb_philo;
}				t_info;

typedef struct s_mem_shared{
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_process;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_data;
	pthread_mutex_t	mutex_start;
	int				end_by_eat;
	t_philo			*philo;
	bool			die;
}					t_mem_shared;

typedef struct s_philo{
	int				id;
	t_info			info;
	bool			created;
	t_mem_shared	*mem_shared;
	pthread_t		thread;
	long int		eat_turn;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	mutex_fork;
	t_process		process;
	long int		time_last_eat;
}					t_philo;

//action.c
bool		eating(t_philo *philo, t_mem_shared *mem_shared);
bool		sleeping(t_philo *philo, t_mem_shared *mem_shared);
bool		thinking(t_philo *philo, t_mem_shared *mem_shared);

//dead.c
bool		check_dead(t_mem_shared *mem_shared, int nb_philo);
bool		does_im_dead(t_philo *philo, t_mem_shared *mem_shared);

//display.c
bool		display(t_philo *philo, t_mem_shared *mem_shared, t_disp state);
bool		unlock_fork(t_philo *philo, t_mem_shared *mem_shared);

//fork.c
bool		can_i_grab(t_philo *philo, t_mem_shared *mem_shared);
bool		take_fork(t_philo *philo, t_mem_shared *mem_shared);

//parsing.c
bool		parse_input(int ac, char **av, t_info *info,
				t_mem_shared *mem_shared);

//routine.c
void		*routine(void *philoo);

//philo.c
bool		philo(t_mem_shared *mem_shared, t_info *info);
bool		clean_end(t_mem_shared *mem_shared, t_info *info);

//time.c
long int	timestamp(unsigned long start_time);
bool		sleep_loop(unsigned long ms, t_mem_shared *mem_shared,
				t_philo *philo);
long int	get_actual_time(void);

//utils.c
int			ft_atoi(const char *nptr);
void		print_str(t_disp action, long long timestamp, int id);

//mutex_init.c
bool		init_mutex(t_mem_shared *mem_shared, int *i, pthread_mutex_t **arr);

#endif
