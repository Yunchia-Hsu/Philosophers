/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:52:57 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/22 11:53:01 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finished_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eating_lock);
	if (philo->all_meals_eaten == true)
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
		return (1);
	return (0);
}
