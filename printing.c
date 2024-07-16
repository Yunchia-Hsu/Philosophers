/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/16 11:24:21 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_death(t_philo *philo)
{	
	long long	time;

	printf("entered print_death\n");
	time = get_current_time() - philo->data->start_time;
	printf("time %lld\n", time);
	printf("dead_philo_flag %d\n", philo->data->dead_philo_flag);
	if (philo->data->dead_philo_flag)
	{
		printf("%lld Philosopher %d %s", time, philo->philo_index, "has died\n");
		clean_all(philo->data, philo);
		return ;
	}
	else
		return ;
}

void print_action(t_philo *philo, char *str)
{
	long long	time;
	
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->dead_philo_flag == true || philo->n_philo_full)
		return ;
	time = get_current_time() - philo->data->start_time;
	printf("%lld Philosopher %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}