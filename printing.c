/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/12 15:46:31 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_death(t_philo *philo)
{
	if (philo->data->dead_philo_flag)
	{
		printf("%d Philosopher %d %s", time, philo->philo_index, "has died");
		//clean all
		//return ;
	}
	// else
	// 	return ;
}

void print_action(t_philo *philo, char *str)
{
	size_t	time;
	
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->dead_philo_flag = true || philo->n_philo_full)
		return ;
	time = get_current_time() - philo->data->start_time;
	printf("%d Philosopher %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}