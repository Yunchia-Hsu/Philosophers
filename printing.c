/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:31:46 by alli              #+#    #+#             */
/*   Updated: 2024/07/12 11:36:30 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_death(t_philo *philo)
{
	if (philo->i_died || philo->data->dead_philo_flag)
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
	
	pthread_mutex_lock(philo->data->print_lock);
	if (philo->i_died = true || philo->n_philo_full)
		return ;
	time = get_current_time() - philo->data->start_time;
	printf("%d Philosopher %d %s", time, philo->philo_index, str);
}