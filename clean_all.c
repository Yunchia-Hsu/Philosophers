/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:06:36 by alli              #+#    #+#             */
/*   Updated: 2024/07/18 09:10:50 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_forks(int i, t_program *data)
{
	while (i > 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	free(data->forks);
	return (0);
}

int	clean_program(t_program *data)
{
	int	i;

	i = 0;
	if (data == NULL)
	{
		ft_putstr_fd("Error: data is NULL\n", 2);
		return (1);
	}
	pthread_mutex_destroy(&data->eating_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	while (i < data->philo_n)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	data->forks = NULL;
	return (0);
}

int	clean_all(t_program *data, t_philo *philo)
{
	clean_program(data);
	if (philo)
		free(philo);
	philo = NULL;
	return (0);
}
