/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/15 17:13:49 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_death(t_philo *philo)
{	
	size_t	time;

	time = get_current_time() - philo->data->start_time;
	if (philo->data->dead_philo_flag)
	{
		printf("%zu Philosopher %d %s", time, philo->philo_index, "has died\n");
		clean_all(philo->data, philo);
		return ;
	}
	else
		return ;
}

void print_action(t_philo *philo, char *str)
{
	size_t	time;
	
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->dead_philo_flag == true || philo->n_philo_full)
		return ;
	time = get_current_time() - philo->data->start_time;
	printf("%zu Philosopher %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}