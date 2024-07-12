
#include "philo.h"


int check_death_flag(t_program *data, t_philo *philo)
{
    pthread_mutex_lock(&data->death_lock);
    if (data->dead_philo_flag == true)
    {
        pthread_mutex_unlock(&data->death_lock);
        return (1);
    }
    pthread_mutex_unlock(&data->death_lock);    
    return (0);
}

int hungery_to_die(t_program *data, t_philo *philo)
{
    size_t elapse;

    pthread_mutex_lock(&data->eating_lock);
    pthread_mutex_lock(&data->death_lock);
    elapse = get_current_time() - philo->last_meal_time;
    if (elapse >= data->time_to_die)
    {
        print_death(philo);
        pthread_mutex_unlock(&data->eating_lock);
        data->dead_philo_flag = true;
        pthread_mutex_unlock(&data->death_lock);
        return (1);
    }
    pthread_mutex_unlock(&data->eating_lock);
    pthread_mutex_unlock(&data->death_lock);
    return (0);
}

int death_check(t_program *data, t_philo *philo)
{
    int i;

    i = 0;
    while(i < data->philo_n || check_death_flag(data, philo)) // 確認已經死 跟被餓死的
    {
        if (hungery_to_die(data, &philo[i]))
            return (1);
        i++;
    }
    return (0);
}


int meal_check(t_program *data, t_philo *philo)// check if anyone is full
{
    int i;

    i = 0;
    if (!data->meals_to_eat)
        return (0);
    while(i < data->philo_n)
    {
        pthread_mutex_lock(&data->eating_lock);
        if (&philo[i].num_meals_eaten < data->meals_to_eat)// philo not full yet
        {
            pthread_mutex_unlock(&data->eating_lock);
            return (0);
        } 
        philo[i].all_meals_eaten = true;
        pthread_mutex_unlock(&data->eating_lock);
        i++;
    }
    pthread_mutex_lock(&data->eating_lock);
    data->everyone_full_flag = true;
    pthread_mutex_unlock(&data->eating_lock);
    return (1);
}

int monitoring(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (meal_check(philo->data, philo) || death_check(philo->data, philo))
            break;
    }
    return (0);
} 