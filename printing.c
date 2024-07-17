/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 13:58:03 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_death(t_philo *philo)
{	
	long long	time;
	
	pthread_mutex_lock(&philo->data->print_lock);
	time = get_current_time() - philo->data->start_time;
	// if (philo->data->dead_philo_flag)  // already checked in monitoring
	// {
		printf("%lld %d %s", time, philo->philo_index, "has died\n");
		pthread_mutex_unlock(&philo->data->print_lock);
		//clean_all(philo->data, philo);// will return to mian and clean all
		return ;
}

void print_action(t_philo *philo, char *str)
{
	long long	time;
	//printf(" philo %d in print 1 \n", philo->philo_index);
	pthread_mutex_lock(&philo->data->print_lock);
	time = get_current_time() - philo->data->start_time;
	if ( philo->data->can_write == true || (philo->data) == 0)
		printf("%lld %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}