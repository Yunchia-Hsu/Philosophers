
#include "philo.h"

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

int clean_philo(t_program *data, t_philo *philo)
{
    int i;

    i = 0;
    if (philo == NULL || philo->data == NULL)
    {
        ft_putstr_fd( "Error: philo or philo->data is NULL\n", 2);
        return(1);
    }
    while (i < data->philo_n)
    {
        pthread_mutex_destroy(&philo[i++].meal_lock);//destroy every philo's meal lock
    }
    return (0);
}


int clean_all(t_program *data, t_philo *philo)
{
    clean_program(data);
    clean_philo(data, philo);
        
    free(philo);
    philo = NULL;
    return (0);
}
// free all threads and return(1)