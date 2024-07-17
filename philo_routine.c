/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:12:13 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 11:15:34 by alli             ###   ########.fr       */
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

int	dead_or_finished(t_philo *philo)
{
	am_i_full(philo);
	if (check_death_flag(philo->data) || finished_meals(philo))
	{
		return (1);
	}
	return (0);
}

int	die_alone(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	ft_usleep(philo->data->time_to_die);
	return (1);
}

static int	eat(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork\n");
	if (philo->data->philo_n == 1) //check if it's a single philo
		return (die_alone(philo));
	if (dead_or_finished(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (clean_all(philo->data, philo));
	}
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork\n");
	if (dead_or_finished(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (clean_all(philo->data, philo));
	}
	print_action(philo, "is eating\n");
	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_lock(&philo->data->eating_lock);
	philo->last_meal_time = get_current_time();
	// printf("new last meal time %lld\n", philo->last_meal_time);
	if (philo->data->meals_to_eat)
		philo->num_meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->data->eating_lock);
	return (0);
}

static int	sleep_philo(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	print_action(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

static int	think(t_philo *philo)
{
	if (dead_or_finished(philo))
	{
		printf("think returned 1\n");
		return (1);
	}
	print_action(philo, "is thinking\n");
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	
	if (philo->philo_index % 2 == 0)
		ft_usleep(50);
	// printf("philo_index %d\n", philo->philo_index);
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