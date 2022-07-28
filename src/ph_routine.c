#include "philo.h"

//Mutex l'attribution des fourchettes + checker si c'est 1 ou un nombre inmpaire ou un nombre pair
//Mutex pour l'affichage des messages

//Function check fork to check if the fork ar available or not


//Si le nombre de philo est impaire faire sleep tous les pair + le premier philo / tous les impaire mange 
//Ensuite les paire mange puis l

void	*routine_philo(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *) philo;
	printf("philo nb : %i\n", phil->id);
	phil->creation_time = ph_get_time(&input);
	printf("time %i\n", phil->creation_time);
	//tant que time to eat du philo precedent et suivant n'est pas fini / think ou nothing if not started
	//ensuite access au fork
	return (NULL);
}

//Si les forks sont available ils les prends et eat le time to eat puis les liberes et sleep time to sleep 
//when finished to sleep, they start thinking

//Si ils ont tous manger, the first one can restart again / else he died,

//Boolean qui passe a 1 quand ils ont fini de manger et qui reset a 0 pour tous quand ca restart

//Function qui check si ils sont dead ou pas aussi !
