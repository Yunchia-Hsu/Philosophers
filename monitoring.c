/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:19:07 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 14:10:46 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	am_i_full(t_philo *philo) //do I need this?
{
	//printf("in am i full 1 \n");
    pthread_mutex_lock(&philo->data->eating_lock);
    //pthread_mutex_lock(&philo->meal_lock);
	if (philo->all_meals_eaten == true)
	{
		pthread_mutex_unlock(&philo->data->eating_lock);
        //pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
    pthread_mutex_unlock(&philo->data->eating_lock);
	//pthread_mutex_unlock(&philo->meal_lock);
    //printf("in eat end \n");
	return (0);
}

int check_death_flag(t_program *data)
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
    long long elapse;
    long long current_time;

    pthread_mutex_lock(&data->eating_lock);
    //pthread_mutex_lock(&philo->meal_lock);
    current_time = get_current_time();
	// printf("%lld hungery_to_die\n", philo->last_meal_time);

    elapse = current_time - philo->last_meal_time;
    if (elapse >= data->time_to_die)
    {
		
        pthread_mutex_unlock(&data->eating_lock);
        //pthread_mutex_unlock(&philo->meal_lock);
        print_death(philo); 
        return (1);
    }
	pthread_mutex_unlock(&data->eating_lock);
    //pthread_mutex_unlock(&philo->meal_lock);
    //printf("hungry6\n");
	return (0);
}

int death_check(t_program *data, t_philo *philo)
{
    int i;

    i = 0;
    while(i < data->philo_n || check_death_flag(data)) // 確認已經死 跟被餓死的
    {
		if (hungery_to_die(data, &philo[i]))
		{
            pthread_mutex_lock(&philo->data->print_lock);
            pthread_mutex_lock(&data->death_lock);
			philo->data->dead_philo_flag = true;
            pthread_mutex_unlock(&philo->data->print_lock);
			pthread_mutex_unlock(&data->death_lock);
			
			return (1);
		}
        i++;
    }
    return (0);
}


int meal_check(t_program *data, t_philo *philo)// check if anyone is full
{
    int i;

    
    if (data->meals_to_eat == -1)
    {
		return (0);
	}
    i = 0;
	while(i < data->philo_n)
    { 
        pthread_mutex_lock(&data->eating_lock);
        //pthread_mutex_lock(&philo[i].meal_lock);
        if (philo[i].num_meals_eaten < data->meals_to_eat)// philo not full yet
        {
            // printf("in mealcheck\n");
			pthread_mutex_unlock(&data->eating_lock);
            //pthread_mutex_unlock(&philo[i].meal_lock);
            return (0);
        } 
        //pthread_mutex_lock(&data->eating_lock);//finished meals function use eating lock
        philo[i].all_meals_eaten = true;
        pthread_mutex_unlock(&data->eating_lock);
        //pthread_mutex_unlock(&philo[i].meal_lock);
    
        i++;
    }
	
	// printf("out of the loop\n");
    pthread_mutex_lock(&data->eating_lock);// like full lock
    //pthread_mutex_lock(&philo->meal_lock);
    data->everyone_full_flag = true;
    pthread_mutex_unlock(&data->eating_lock);
    return (1);
}

void *monitoring(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (meal_check(philo->data, philo) || death_check(philo->data, philo))
            break;
    }
	pthread_mutex_lock(&philo->data->print_lock);
	philo->data->can_write = false;
	pthread_mutex_unlock(&philo->data->print_lock);
    return (NULL);
} 
