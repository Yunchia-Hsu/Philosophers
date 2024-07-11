/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:03:01 by alli              #+#    #+#             */
/*   Updated: 2024/07/11 15:16:26 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_mutexes(t_program *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_program) * data->philo_n);
	if (!data->forks)
		return (1); //exit?
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(philo->l_fork, NULL))// do I need to initialize these forks?
		return (1);
	if (pthread_mutex_init(philo->r_fork, NULL))
		return (1);
	if (pthread_mutex_init(&philo->sleep_lock, NULL))
		return (1);
	if (pthread_mutex_init(&philo->eating_lock, NULL))
		return (1);
	if (pthread_mutex_init(&philo->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&philo->death_lock, NULL))
		return (1);
}

int	init_program(t_program *data, char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (1);
	data->philo_n = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	if (init_data_mutexes(data))
		return (1);
	return (0);
}

int	init_philo(t_philo	*philo, t_program *data)
{
	int	i;

	i = 1;//index starts from 1
	while (i <= data->philo_n)
	{
		philo[i].philo_index = i;
		philo[i].data = data;
		philo[i].n_philo_full = false;
		philo[i].r_fork = data.forks[i];
		if (i == (data->philo_n - 1))
			philo[i].l_fork = data->fork[1];
		else
			philo[i].l_fork = data->fork[i + 1];
		if (init_philo_mutexes(philo))
			return (1);
	}
}