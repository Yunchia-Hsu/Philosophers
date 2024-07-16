/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/16 16:11:35 by alli             ###   ########.fr       */
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
	// }
	// else
	// 	return ;
}

void print_action(t_philo *philo, char *str)
{
	long long	time;
	//printf(" philo %d in print 1 \n", philo->philo_index);
	pthread_mutex_lock(&philo->data->print_lock);
	// if (philo->data->dead_philo_flag == true || philo->n_philo_full)
	// 	return ;  //this will cause suspended
	//printf(" philo %d in print 2 \n", philo->philo_index);
	time = get_current_time() - philo->data->start_time;
	// if (philo->data->can_write == true || check_death_flag(philo->data) == 0)
	// 	printf("%lld %d %s", time, philo->philo_index, str);
	if ( philo->data->can_write == true || (philo->data) == 0)
		printf("%lld %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
	//printf(" philo %d in print end \n", philo->philo_index);
}