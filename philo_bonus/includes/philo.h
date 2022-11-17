/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:13:54 by odessein          #+#    #+#             */
/*   Updated: 2022/11/14 14:02:25 by odessein         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include "sys/time.h"
# include "stdio.h"
# include "unistd.h"
# include "pthread.h"
# include "stdbool.h"
# include "stdlib.h"
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>

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

typedef struct s_sem_info {
	sem_t	*bowl;
	sem_t	*write;
	sem_t	*max;
	sem_t	*end;
	sem_t	*catch_fork;
}			t_sem_info;

typedef struct s_info {
	long int	t_to_sleep;
	long int	t_to_eat;
	long int	t_to_die;
	long int	t_eat_max;
	long int	t_start;
	long int	nb_philo;
}				t_info;

typedef struct s_philo{
	int				pid;
	int				id;
	t_info			info;
	long int		eat_turn;
	long int		time_last_eat;
	bool			die;
	pthread_t		thread_fork;
	pthread_t		thread_dead;
	sem_t			*sem_eat;
	sem_t			*sem_dead;
}					t_philo;

typedef struct s_info_thread{
	t_philo		*philo;
	t_sem_info	*sem;
}				t_info_thread;

//action.c
bool		eating(t_philo *philo, t_sem_info *sem);
bool		sleeping(t_philo *philo, t_sem_info *sem);
bool		thinking(t_philo *philo, t_sem_info *sem);

//dead.c
bool		post_write(t_sem_info *sem);
bool		does_im_dead(t_philo *philo);
bool		check_dead(t_sem_info *sem, t_info info);
void		setup_dead(t_sem_info *sem);

//display.c
bool		display(t_philo *philo, t_sem_info *sem, t_disp disp);
void		print_str(t_disp action, long long timestamp, int id);

//fork.c
bool		unlock_fork(t_sem_info *sem);
bool		take_fork(t_philo *philo, t_sem_info *sem);

//parsing.c
bool		parse_input(int ac, char **av, t_info *info);

//routine.c
void		routine(t_sem_info *sem, t_philo *philo);

//setup_philo.c
bool		philo_a(t_info info, t_sem_info *sem, t_philo *philo);

//time.c
long int	timestamp(unsigned long start_time);
long int	get_actual_time(void);
bool		sleep_loop(unsigned long ms, t_philo *philo);

//sem_utils.c
bool		semaphore(t_sem_info *sem, t_info info);
bool		close_sem(t_sem_info *sem);

//utils.c
bool		error_msg(char *str);
void		ft_putnbr(long long n);
int			ft_atoi(const char *nptr);
int			ft_strlen(const char *str);

//ft_itoa.c
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);

//thread_routine.c
bool		init_sem_in_philo(t_philo *philo);
void		*routine_fork(void *content);
void		*routine_dead(void *content);
void		*routine_kill(void *content);

#endif
