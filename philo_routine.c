/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:12:13 by alli              #+#    #+#             */
/*   Updated: 2024/07/16 12:13:08 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_meals(t_philo *philo)
{
	//printf("entered finished_meals\n");
	//check this not going through all the philosophers
	pthread_mutex_lock(&philo->data->eating_lock);
	if (philo->num_meals_eaten == philo->data->meals_to_eat)
	{
		//printf("philo is full\n");
		
		philo->all_meals_eaten = true;
		pthread_mutex_unlock(&philo->data->eating_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eating_lock);
	//printf("philo %d is hungry\n", philo->philo_index);
	return (0);
}

// int	starvation_check(t_philo *philo)
// {
// 	long long	elapsed_time;

// 	//printf("am I starving?\n");
// 	pthread_mutex_lock(&philo->data->death_lock);
// 	//pthread_mutex_lock(&philo->data->eating_lock);
// 	elapsed_time = get_current_time() - philo->last_meal_time;
// 	if (elapsed_time >= philo->data->time_to_eat)
// 	{
// 		pthread_mutex_unlock(&philo->data->death_lock);
// 		pthread_mutex_unlock(&philo->data->eating_lock);
// 		philo->data->dead_philo_flag = true;
// 		//philo->data->dead_philo_flag = true or a dead philosopher function
// 		return (1);
// 	}
// 	//printf("philo %d not starving\n", philo->philo_index);
// 	pthread_mutex_unlock(&philo->data->eating_lock);
// 	pthread_mutex_unlock(&philo->data->death_lock);
// 	return (0);
// }

int	starvation_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
    if (philo->data->dead_philo_flag == true)
    {
        pthread_mutex_unlock(&philo->data->death_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->death_lock);    
    return (0);
}

int	dead_or_finished(t_philo *philo)
{
	
	//printf("philo %d entered dead or finished\n",philo->philo_index);
	if (starvation_check(philo) || finished_meals(philo))
		return (1);
	// if (meal_check(philo->data, philo) || death_check(philo->data, philo))
	// 	return (1);
	//printf("philo %d finished check\n",philo->philo_index);
	return (0);
}

int	die_alone(t_philo *philo)
{
	
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

static int	eat(t_philo *philo)
{
	//printf("%d, time_to_eat %lld\n", philo->philo_index, philo->data->time_to_eat);
	if (am_i_full(philo))
		return (1);
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken right fork\n");
	
	if (philo->data->philo_n == 1) //check if it's a single philo
		return (die_alone(philo));
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken left fork\n");
	if (dead_or_finished(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}

	pthread_mutex_lock(&philo->meal_lock);

	philo->last_meal_time = get_current_time();

	if (philo->data->meals_to_eat)
		philo->num_meals_eaten++;

	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

	return (0);
}

static int	sleep_philo(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	// if (pthread_mutex_lock(&philo->sleep_lock) == 0)
	{
		print_action(philo, "is sleeping\n");
		ft_usleep(philo->data->time_to_sleep);
		// pthread_mutex_unlock(&philo->sleep_lock);
		return (0);
	}
	// return (1);
}

static int	think(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	print_action(philo, "is thinking\n ");
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	
	if (philo->philo_index % 2 == 0)
		ft_usleep(50);
	while (!dead_or_finished(philo))
	{
		//printf("philo %d is in routine\n", philo->philo_index);
		if (eat(philo) == 1)
			return (NULL);
		if (sleep_philo(philo) == 1)
			return (NULL);
		if (think(philo) == 1)
			return (NULL);
		//printf("routine 3 \n");
	}
	//printf("routine 4 \n");
	return (NULL);
}