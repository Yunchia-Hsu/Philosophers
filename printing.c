/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 11:14:28 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_death(t_philo *philo)
{	
	long long	time;
	
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	time = get_current_time() - philo->data->start_time;
	if (philo->data->dead_philo_flag)
	{
		printf("%lld %d %s", time, philo->philo_index, "has died\n");
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(&philo->data->death_lock);
		clean_all(philo->data, philo);
		return ;
	}
	else
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_lock(&philo->data->death_lock);
	}
}

void print_action(t_philo *philo, char *str)
{
	long long	time;
	
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->dead_philo_flag == true || philo->n_philo_full)
		return ;
	time = get_current_time() - philo->data->start_time;
	printf("%lld %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}