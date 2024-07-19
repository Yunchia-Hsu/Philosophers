/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:02:21 by alli              #+#    #+#             */
/*   Updated: 2024/07/19 10:53:04 by alli             ###   ########.fr       */
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
