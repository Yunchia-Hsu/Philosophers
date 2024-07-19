/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:36:47 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/19 10:10:16 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die_alone(t_philo *philo)
{
	if (ft_usleep(philo->data->time_to_die, philo))
		return (1);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork\n");
	if (philo->data->philo_n == 1)
		return (die_alone(philo));
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork\n");
	if (dead_or_finished(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->eating_lock);
	print_action(philo, "is eating\n");
	philo->last_meal_time = get_current_time();
	if (philo->data->meals_to_eat != -1)
		philo->num_meals_eaten++;
	pthread_mutex_unlock(&philo->data->eating_lock);
	if (ft_usleep(philo->data->time_to_eat, philo))
		return (1);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static int	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping\n");
	if (dead_or_finished(philo))
		return (1);
	if (ft_usleep(philo->data->time_to_sleep, philo))
		return (1);
	return (0);
}

static int	think(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	print_action(philo, "is thinking\n");
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_index % 2 == 1)
	{
		think(philo);
		ft_usleep(philo->data->time_to_eat / 2, philo);
	}	
	while (!dead_or_finished(philo))
	{
		if (eat(philo) == 1)
			return (NULL);
		if (sleep_philo(philo) == 1)
			return (NULL);
		if (think(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
