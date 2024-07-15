/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:12:13 by alli              #+#    #+#             */
/*   Updated: 2024/07/15 12:56:51 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_meals(t_philo *philo)
{
	//check this not going through all the philosophers
	pthread_mutex_lock(&philo->data->eating_lock);
	if (philo->num_meals_eaten == philo->data->meals_to_eat)
	{
		pthread_mutex_unlock(&philo->data->eating_lock);
		philo->all_meals_eaten = true;
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eating_lock);
	return (0);
}

int	starvation_check(t_philo *philo)
{
	size_t	elapsed_time;
	size_t	over_time;

	pthread_mutex_lock(&philo->data->death_lock);
	//pthread_mutex_lock(&philo->data->eating_lock);
	elapsed_time = get_current_time() - philo->last_meal_time;
	if (elapsed_time > philo->data->time_to_eat)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		philo->data->dead_philo_flag = true;
		//philo->data->dead_philo_flag = true or a dead philosopher function
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (0);
}

int	dead_or_finished(t_philo *philo)
{
	if (starvation_check(philo) || finished_meals(philo))
		return (1);
	return (0);
}

int	die_alone(t_philo *philo)
{
	ft_usleep(philo->data->time_to_die);
	return (1);
}

static int	eat(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	if (philo->data->philo_n == 1) //check if it's a single philo
		return (die_alone(philo));
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken right fork");
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken left fork");
	pthread_mutex_lock(&philo->data->eating_lock);
	ft_usleep(philo->data->time_to_eat);
	print_action(philo, "is eating");
	philo->last_meal_time = get_current_time() - philo->last_meal_time;
	if (philo->data->meals_to_eat)
		philo->num_meals_eaten++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->data->eating_lock);
	return (0);
}

static int	sleep(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	if (pthread_mutex_lock(&philo->sleep_lock) == 0)
	{
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		pthread_mutex_unlock(&philo->sleep_lock);
		return (0);
	}
	return (1);
}

static int	think(t_philo *philo)
{
	if (dead_or_finished(philo))
		return (1);
	print_action(philo, "is thinking");
}

void	philo_routine(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	while (!dead_or_finished(philo))
	{
		if (eat(philo) == 1)
			return ;
		if (sleep(philo) == 1)
			return ;
		if (think(philo) == 1)
			return ;
	}
}