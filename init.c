/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:19:34 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 13:46:38 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_mutexes(t_program *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		return (1); //exit?
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->eating_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (1);
	return (0);
}

// int	init_philo_mutexes(t_philo *philo)
// {
// 	// printf("philo_mutex 1\n");
// 	// if (pthread_mutex_init(philo->l_fork, NULL))// do I need to initialize these forks?
// 	// 	return (1);
// 	// printf("philo_mutex 2\n");
// 	// if (pthread_mutex_init(philo->r_fork, NULL))
// 	// 	return (1);
// 	printf("philo_mutex 3\n");
// 	if (pthread_mutex_init(&philo->sleep_lock, NULL))
// 		return (1);
// 	return (0);
// }

int	init_program(t_program *data, char **argv, int argc)
{
	//int	i;
	//i = 0;
	
	if (!argv)
		return (1);
	//printf("before init\n");
	data->start_time = get_current_time();
	// printf("data->start_time %zu", data->start_time);
	//printf("philo_n %zu \n", ft_atol(argv[1]));
	data->philo_n = ft_atol(argv[1]);
	//printf("data->philo_n %d\n", data->philo_n);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc > 5)
	{
		data->meals_to_eat = ft_atol(argv[5]);
		//printf("init arv[5] \n");
	}
	else
		data->meals_to_eat = -1;
	//printf("init 6\n");
	data->dead_philo_flag = false;
	//printf("init 7\n");
	data->everyone_full_flag = false;
	data->can_write = true;
	// data->can_write = true;
	//rintf("init 8\n");
	if (init_data_mutexes(data))
	{
		//printf("in data mutexes\n");
		return (1);
	}
	//printf("init 9\n");
	// printf("finished init_philo\n");
	return (0);
}

int	init_philo(t_philo	*philo, t_program *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		philo[i].data = data;
		philo[i].philo_index = i;
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
		// if (pthread_mutex_init(&philo[i].meal_lock, NULL))
		// {
		// 	clean_all(data, philo);
		// 	return (1);
		// }
	}
	return (0);
}