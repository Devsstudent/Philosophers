/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:24:39 by odessein          #+#    #+#             */
/*   Updated: 2022/11/07 17:04:51 by odessein         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */
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

bool	display(t_philo *philo, t_sem_info *sem, t_disp disp)
{
	long int	timestamp_v;

	if (does_im_dead(philo, sem))
		return (false);
	if (sem_wait(sem->write) != 0)
	{
		write(2, "Error wait sem\n", 15);
		return (false);
	}
	timestamp_v = timestamp(philo->info.t_start);
	print_str(disp, timestamp_v, philo->id);
	if (sem_post(sem->write) != 0)
	{
		write(2, "Error post sem\n", 15);
		return (false);
	}
	return (true);
}
