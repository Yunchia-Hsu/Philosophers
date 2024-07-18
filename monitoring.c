/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:36:34 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/18 16:37:39 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_program *data)
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

int	hungery_to_die(t_program *data, t_philo *philo)
{
	long long	elapse;
	long long	current_time;

	pthread_mutex_lock(&data->eating_lock);
	current_time = get_current_time();
	elapse = current_time - philo->last_meal_time;
	if (elapse >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->eating_lock);
		print_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&data->eating_lock);
	return (0);
}

int	death_check(t_program *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_n || check_death_flag(data))
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

int	meal_check(t_program *data, t_philo *philo)
{
	int	i;

	if (data->meals_to_eat == -1)
		return (0);
	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->eating_lock);
		if (philo[i].num_meals_eaten < data->meals_to_eat)
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

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (meal_check(philo->data, philo) || death_check(philo->data, philo))
			break ;
	}
	pthread_mutex_lock(&philo->data->print_lock);
	philo->data->can_write = false;
	pthread_mutex_unlock(&philo->data->print_lock);
	return (NULL);
}
