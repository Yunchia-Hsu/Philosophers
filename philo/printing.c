/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:53:45 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/22 11:53:47 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{	
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_current_time() - philo->data->start_time;
	printf("%lld %d %s", time, philo->philo_index, " died\n");
	pthread_mutex_unlock(&philo->data->print_lock);
	return ;
}

void	print_action(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_current_time() - philo->data->start_time;
	if (philo->data->can_write == true || (philo->data) == 0)
		printf("%lld %d %s", time, philo->philo_index, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}
