/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:19:07 by alli              #+#    #+#             */
/*   Updated: 2024/07/15 17:55:08 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


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
    long elapse;

	//printf("hungry0\n");
    pthread_mutex_lock(&data->eating_lock);
	//printf("hungry1\n");
    //pthread_mutex_lock(&data->death_lock);
    elapse = get_current_time() - philo->last_meal_time;
    if (elapse >= data->time_to_die)
    {
        printf("philo %d \n", philo->philo_index);
		printf("get_current_time() %zu \n", get_current_time());
		printf("philo->last_meal_time %zu \n", philo->last_meal_time);
		
		printf("elapse %zu \n", elapse);
		printf("data->time_to_die %zu \n", data->time_to_die);
		printf("hungry4\n");
		print_death(philo);
        pthread_mutex_unlock(&data->eating_lock);
        data->dead_philo_flag = true;
        //pthread_mutex_unlock(&data->death_lock);
        return (1);
    }
    //printf("hungry5\n");
	pthread_mutex_unlock(&data->eating_lock);
    //pthread_mutex_unlock(&data->death_lock);
    //printf("hungry6\n");
	return (0);
}

int death_check(t_program *data, t_philo *philo)
{
    int i;

    i = 0;
    while(i < data->philo_n || check_death_flag(data)) // 確認已經死 跟被餓死的
    {
        //printf("i in death check %d\n", i);
		if (hungery_to_die(data, &philo[i]))
		{
            pthread_mutex_lock(&data->death_lock);
			philo->data->dead_philo_flag = true;
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		// if (starvation_check(philo))
		// 	return (1);
        i++;
    }
    return (0);
}


int meal_check(t_program *data, t_philo *philo)// check if anyone is full
{
    int i;

    
    if (!data->meals_to_eat)
    {
		return (0);
	}   
    i = 0;
	while(i < data->philo_n)
    { 
        pthread_mutex_lock(&data->eating_lock);
        if (philo[i].num_meals_eaten < data->meals_to_eat)// philo not full yet
        {
            //printf("in mealcheck\n");
			pthread_mutex_unlock(&data->eating_lock);
            return (0);
        } 
        philo[i].all_meals_eaten = true;
        pthread_mutex_unlock(&data->eating_lock);
        i++;
    }
	
	// printf("out of the loop\n");
    pthread_mutex_lock(&data->eating_lock);
    data->everyone_full_flag = true;
    pthread_mutex_unlock(&data->eating_lock);
	printf("in mealcheck 0\n");
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
    return (NULL);
} 
