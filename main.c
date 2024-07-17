/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:29:33 by alli              #+#    #+#             */
/*   Updated: 2024/07/17 14:29:37 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int validate_input(int argc, char **argv)
{
    int i;

    if (argc != 5 && argc != 6)
    {
        ft_putstr_fd("invalid number of arguments", 2);
        return (1);
    }
    i = 1;
    while (argv[i])
    {
        if (i == 1 && ft_atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid number of philosophers\n", 2), 1);
        else if (i == 2 && ft_atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to die\n", 2), 1);
        else if (i == 3 && ft_atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to eat\n", 2), 1);
        else if (i == 4 && ft_atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to sleep\n", 2), 1);
        else if (i == 5 && ft_atol(argv[i]) < 0)
            return (ft_putstr_fd("invalid times each philo should eat\n", 2), 1);
        i++;
    }
    return (0);
}

int thread_join(pthread_t monitor, t_philo *philo)
{
    int i;

    i = 0;
    if (pthread_join(monitor, NULL) != 0)
    {
        ft_putstr_fd("Error: monitor_join falied\n", 2);
        return (clean_all(philo->data, philo));
    }
    while(i < philo->data->philo_n)
    {
        // printf("philo %d in join\n", i);
		if (pthread_join(philo[i].philo_thread, NULL) != 0)
        {
            ft_putstr_fd("Error: philo_join falied\n", 2);
            return (clean_all(philo->data, philo));
        }
        i++;
    }
    return (0);
}


int init_threads(t_philo *philo, t_program *data)
{
    pthread_t monitor;
    int i;

    i = 0;
    if (pthread_create(&monitor, NULL, &monitoring, philo))//philo is the argument for thread
    {
        
		ft_putstr_fd("Error: monitoring thread_creat failed\n", 2);
        return (1);
    }
	while (i < data->philo_n)
	{	 
        if (pthread_create(&philo[i].philo_thread, NULL, &philo_routine, &philo[i]))
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


int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_program	data;
	
    if (validate_input(argc, argv))
		return (1);
	if (init_program(&data, argv, argc))
		return (clean_program(&data));
	philo = malloc(data.philo_n * sizeof(t_philo));
	if (!philo)
        return (clean_program(&data));
    if (init_philo(philo, &data)) //this should be what kind of &data each philosopher carries
		return (clean_program(&data));
	if (init_threads(philo, &data))
        return(clean_all(&data, philo));
	if (clean_all(&data, philo))
        return (1);
	return (0);
}


//./philo 5人 800死 200吃 200睡覺 
