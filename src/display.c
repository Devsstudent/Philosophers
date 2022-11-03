/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:59:35 by odessein          #+#    #+#             */
/*   Updated: 2022/11/03 12:45:14 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	ft_putchar(char c)
{
	if (write(1, &c, sizeof(c)))
		return ;
}

static void	ft_putnbr(long long n)
{
	long long	temp;

	temp = (long long) n;
	if (n < 0)
	{
		ft_putchar('-');
		temp *= -1;
	}
	if (temp < 10)
	{
		ft_putchar(temp + 48);
		return ;
	}
	ft_putnbr(temp / 10);
	ft_putchar((temp % 10) + 48);
}

static void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void	print_str(t_disp action, long long timestamp, int id)
{
	ft_putnbr(timestamp);
	write(1, " ", 1);
	ft_putnbr((long long) id);
	write(1, " ", 1);
	if (action == _EAT)
		ft_putstr(EAT);
	else if (action == _SLEEP)
		ft_putstr(SLEEP);
	else if (action == _THINK)
		ft_putstr(THINK);
	else if (action == _FORK)
		ft_putstr(FORK);
	else if (action == _DIE)
		ft_putstr(DIE);
}

bool	display(t_philo *philo, t_mem_shared *mem_shared, t_disp state)
{
	long int	timestamp_v;

	pthread_mutex_lock(&mem_shared->mutex_dead);
	if (mem_shared->die)
	{
		pthread_mutex_unlock(&mem_shared->mutex_dead);
		if (state == _EAT)
			unlock_fork(philo, mem_shared);
		else if (state == _FORK)
			unlock_fork(philo, mem_shared);
		return (false);
	}
	pthread_mutex_unlock(&mem_shared->mutex_dead);
	timestamp_v = timestamp(philo->info.t_start);
	if (timestamp_v < 0)
		return (false);
	pthread_mutex_lock(&mem_shared->mutex_write);
	if (state == _FORK)
		print_str(state, timestamp_v, philo->id);
	print_str(state, timestamp_v, philo->id);
	pthread_mutex_unlock(&mem_shared->mutex_write);
	return (true);
}
