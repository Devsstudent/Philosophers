/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:11:59 by odessein          #+#    #+#             */
/*   Updated: 2022/11/03 14:38:15 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int ac, char **av)
{
	t_mem_shared	mem_shared;
	t_info			info;

	if (!parse_input(ac, av, &info, &mem_shared))
		return (1);
	if (!philo(&mem_shared, &info))
		return (2);
}

//Pas de sleep (il doivent faire la queue)
//2 boolean dans la structure pour les fourchettes des philo

//Modifier directement la value du nombre de fourchettes restantes, -2 +2 ?

//Comment on fait pour la mort ? 

//Si le philo meurt : 
void	beta()
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		//On linfo du nombre de fourchettes au depart
		//Pas de droite ou de gauches | ils se servent directement
		//
		//Stocker le pid du philo dans la structure philo
		//Ensuite il va falloir loop sur les process
		//Le probleme c'est la communication entre les process ...
		//Thread autoriser ! Donc a utiliser pour la communication je suppose
		//
		i++;
	}
}
