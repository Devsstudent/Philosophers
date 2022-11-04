/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:11:59 by odessein          #+#    #+#             */
/*   Updated: 2022/11/04 17:21:46 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

bool	close_sem(t_sem_info *sem);
static void	cpy_info(t_info info, t_philo *philo, int index)
{
	philo->info.t_to_sleep = info.t_to_sleep;
	philo->info.t_to_eat = info.t_to_eat;
	philo->info.t_to_die = info.t_to_die;
	philo->info.t_eat_max = info.t_eat_max;
	philo->info.nb_philo = info.nb_philo;
//	philo->info.t_start = get_actual_time();
	philo->info.t_start = info.t_start;
	philo->id = index + 1;
	philo->eat_turn = 0;
	philo->process = UNDEF;
	philo->time_last_eat = philo->info.t_start;
}

void	routine(t_sem_info *sem, t_philo *philo)
{
	while (1)
	{
		if (!take_fork(philo, sem))
			break ;
		if (!eating(philo, sem))
			break ;
		if (!sleeping(philo, sem))
			break ;
		if (!thinking(philo, sem))
			break ;
	}
	kill(philo->pid, SIGINT);
}

bool	philo_a(t_info info, t_sem_info *sem, t_philo *philo)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < info.nb_philo)
	{
		cpy_info(info, &philo[i], i);
		pid = fork();
		philo[i].pid = pid;
		if (pid == 0)
			routine(sem, &philo[i]);
		else
			continue ;
	}
	//may not need it if they kill themself
	//wait dead to send kill to all
	i = -1;
	while (++i < info.nb_philo)
	{
		if (waitpid(philo[i].pid, NULL, 0) == -1)
		{
			write(2, "Fail on waiting\n", 16);
			return (false);
		}
	}
	close_sem(sem);
	return (true);
	//loop de fork ?
}

bool	close_sem(t_sem_info *sem)
{
	sem_wait(sem->dead);
	sem_wait(sem->write);
	sem_wait(sem->bowl);
	if (sem_close(sem->dead) != 0)
	{
		write(2, "Error closing sem\n", 18);
		return (false);
	}
	if (sem_unlink("dead") != 0)
	{
		write(2, "Error unlinking sem\n", 21);
		return (false);
	}
	if (sem_close(sem->write) != 0)
	{
		write(2, "Error closing sem\n", 18);
		return (false);
	}
	if (sem_unlink("write") != 0)
	{
		write(2, "Error unlinking sem\n", 21);
		return (false);
	}
	if (sem_close(sem->bowl) != 0)
	{
		write(2, "Error closing sem\n", 18);
		return (false);
	}
	if (sem_unlink("bowl") != 0)
	{
		write(2, "Error unlinking sem\n", 21);
		return (false);
	}
	return (true);
}

bool	semaphore(t_sem_info *sem, t_info info)
{
	int	i;

	sem->bowl = sem_open("bowl", O_CREAT, S_IRWXU, 1);
	if (sem->bowl == SEM_FAILED)
	{
		write(2, "Error opening semaphore\n", 24);
		return (false);
	}
	i = -1;
	while (++i < info.nb_philo)
	{
		if (sem_post(sem->bowl) != 0)
		{
			write(2, "Error sem post\n", 15);
			return (false);
		}
	}
	sem->dead = sem_open("dead", O_CREAT, S_IRWXU, 1);
	if (sem->dead == SEM_FAILED)
	{
		write(2, "Error opening semaphore\n", 24);
		return (false);
	}
	if (sem_post(sem->dead) != 0)
	{
		write(2, "Error sem post\n", 15);
		return (false);
	}
	sem->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	if (sem->write == SEM_FAILED)
	{
		write(2, "Error opening semaphore\n", 24);
		return (false);
	}
	if (sem_post(sem->write) != 0)
	{
		write(2, "Error sem post\n", 15);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_sem_info	sem;
	t_philo		*philo;

	if (!parse_input(ac, av, &info))
		return (1);
	philo = malloc(sizeof(t_philo) * info.nb_philo);
	if (!philo)
	{
		write(2, "Malloc failed\n", 14);
		free(philo);
		return (2);
	}
	if (!semaphore(&sem, info))
	{
		free(philo);
		return (3);
	}
	if (!philo_a(info, &sem, philo))
	{
		free(philo);
		return (4);
	}
}

//int	main(int ac, char **av)
//{
//	(void) ac;
//	(void) av;
//	sem_t	*bowl;
//	int		fork_nb;
//	int pid;
//
//	fork_nb = 2;
//	bowl = sem_open("bowl", O_CREAT, S_IRWXU, fork_nb);
//	if (bowl == SEM_FAILED)
//	{
//		write(2, "error\n", 6);
//		return (1);
//	}
//	pid = fork();
//	if (pid == 0)
//	{
//		//if (sem_wait(bowl) != 0)
//	//	{
//	//		write(2, "error\n", 6);
//	//		return (1);
//	//	}
//		if (sem_post(bowl) != 0)
//		{
//			write(2, "error\n", 6);
//			return (1);
//		}
//		if (sem_post(bowl) != 0)
//		{
//			write(2, "error\n", 6);
//			return (1);
//		}
//		printf("bonsoiir\n");
//		//printf("bonsoiir\n");
//		if (sem_post(bowl) != 0)
//		{
//			write(2, "error\n", 6);
//			return (1);
//		}
//		//printf("bonsoiir\n");
//	}
//	else
//	{
//		if (sem_wait(bowl) != 0)
//		{
//			write(2, "error\n", 6);
//			return (1);
//		}
//		if (sem_wait(bowl) != 0)
//		{
//			write(2, "error\n", 6);
//			return (1);
//		}
//		if (sem_wait(bowl) != 0)
//		{
//			write(2, "error\n", 6);
//			return (1);
//		}
//		printf("%s\n",bowl->__);
//	}
//}

//Semaphore pour le nombre de fourchette available
//Call 2 time le semaphore avant de eat et le release 2 times quand il a fini
//Decalage pareil que sur le philo de base
//checker la mort reduire a 0 remettre a 1 (si mort reste blocker a reduire a 0 because not possible to go -1)

//Semaphore pour la mort 

//IDEA : Philo meurt -> sleep de 5000 Us reset a 1 (sem_dead) kill le ps

	// Autre philo : get time before check_dead(semaphore)
	//	block sur le sem_dead si temp ecoule en entre avant et apres > 5000 
	//	Kill le process aussi

//Pas de sleep (il doivent faire la queue)
//2 boolean dans la structure pour les fourchettes des philo

//Modifier directement la value du nombre de fourchettes restantes, -2 +2 ?

//Comment on fait pour la mort ? 

//Si le philo meurt : 


		//On linfo du nombre de fourchettes au depart
		//Pas de droite ou de gauches | ils se servent directement
		//
		//Stocker le pid du philo dans la structure philo
		//Ensuite il va falloir loop sur les process
		//Le probleme c'est la communication entre les process ...
		//Thread autoriser ! Donc a utiliser pour la communication je suppose
		//
