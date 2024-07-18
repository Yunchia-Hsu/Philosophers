/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:36:20 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/18 16:37:45 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_mutexes(t_program *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		return (1);
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			clean_forks(i, data);
		i++;
	}
	if (pthread_mutex_init(&data->eating_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_program(t_program *data, char **argv, int argc)
{
	if (!argv)
		return (1);
	data->start_time = get_current_time();
	data->philo_n = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc > 5)
		data->meals_to_eat = ft_atol(argv[5]);
	else
		data->meals_to_eat = -1;
	data->dead_philo_flag = false;
	data->everyone_full_flag = false;
	data->can_write = true;
	if (init_data_mutexes(data))
		return (1);
	return (0);
}

int	init_philo(t_philo	*philo, t_program *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		philo[i].data = data;
		philo[i].philo_index = i + 1;
		philo[i].n_philo_full = false;
		philo[i].num_meals_eaten = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].all_meals_eaten = false;
		philo[i].r_fork = &data->forks[i];
		if (i == (data->philo_n - 1))
			philo[i].l_fork = &data->forks[0];
		else
			philo[i].l_fork = &data->forks[i + 1];
		i++;
	}
	return (0);
}

static	int	thread_join(pthread_t monitor, t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_join(monitor, NULL) != 0)
	{
		ft_putstr_fd("Error: monitor_join failed\n", 2);
		return (clean_all(philo->data, philo));
	}
	while (i < philo->data->philo_n)
	{
		if (pthread_join(philo[i].philo_thread, NULL) != 0)
		{
			ft_putstr_fd("Error: philo_join failed\n", 2);
			return (clean_all(philo->data, philo));
		}
		i++;
	}
	return (0);
}

int	init_threads(t_philo *philo, t_program *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL,
			&monitoring, philo))
	{
		ft_putstr_fd("Error: monitoring thread_creat failed\n", 2);
		return (1);
	}
	while (i < data->philo_n)
	{
		if (pthread_create(&philo[i].philo_thread, NULL,
				&philo_routine, &philo[i]))
		{
			ft_putstr_fd("Error: philo thread_create failed\n", 2);
			return (clean_all(data, philo));
		}
		i++;
	}
	if (thread_join(monitor, philo) != 0)
		return (1);
	return (0);
}
