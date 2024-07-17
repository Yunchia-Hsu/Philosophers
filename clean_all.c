
#include "philo.h"

int	clean_forks(int i, t_program *data)
{
	while (i > 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	free(data->forks);
	return (0);
}

int clean_program(t_program *data)
{
    int i;

    i = 0;
    if (data == NULL)
    {
        ft_putstr_fd( "Error: data is NULL\n", 2);
        return(1);
    }
    pthread_mutex_destroy(&data->eating_lock);
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->death_lock);
    while (i < data->philo_n) // if it only init 3/5 fork, should protect
        pthread_mutex_destroy(&data->forks[i++]);
    free(data->forks);
    data->forks = NULL;
    return (0);
}

int clean_all(t_program *data, t_philo *philo)
{
    clean_program(data);
    // if (clean_philo(data, philo))
    //     return (clean_program(data));
    free(philo);
    philo = NULL;
    return (0);
}
// free all threads and return(1)