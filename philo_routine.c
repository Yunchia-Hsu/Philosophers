/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:12:13 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 14:32:29 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eating_lock);
	if (philo->all_meals_eaten == true)//will be update in monitoring so here only needs to check
	{
		pthread_mutex_unlock(&philo->data->eating_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eating_lock);
	return (0);
}

int	dead_or_finished(t_philo *philo)
{
	if (check_death_flag(philo->data) || finished_meals(philo))
	{
		return (1);
	}
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
	pthread_mutex_lock(&philo->data->eating_lock);
	print_action(philo, "is eating\n");
	philo->last_meal_time = get_current_time();
	if (philo->data->meals_to_eat != -1)
		philo->num_meals_eaten++;
	pthread_mutex_unlock(&philo->data->eating_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
		//printf("think returned 1\n");
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