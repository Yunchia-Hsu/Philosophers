/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:47:04 by alli              #+#    #+#             */
/*   Updated: 2024/07/11 17:43:50 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int validate_input(int argc, char **argv)
{
    //./philo 5 philo ;800 time to die ;200 time to eat ;200 time to sleep
    int i;

    if (argc != 5 && argc != 6)
    {
        ft_purstr_fd("invalid number of arguments", 2);
        return (1);
    }
    i = 1;
    while (argv[i])
    {
        if (i == 1 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid number of philosophers\n", 2), 1);
        else if (i == 2 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to die\n", 2), 1);
        else if (i == 3 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to eat\n", 2), 1);
        else if (i == 4 && atol(argv[i]) <= 0)
            return (ft_putstr_fd("invalid time to sleep\n", 2), 1);
        else if (i == 5 && atol(argv[i]) < 0)
            return (ft_putstr_fd("invalid times each philo should eat\n", 2), 1);
        i++;
    }
    return (0);
}



// int	init_program(t_program *data, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	if (!argv)
// 		return (1);
// 	data->philo_n = ft_atoi(argv[1]);
// 	data->time_to_die = ft_atoi(argv[2]);
// 	data->time_to_eat = ft_atoi(argv[3]);
// 	data->time_to_sleep = ft_atoi(argv[4]);
// 	if (argv[5])
// 		data->meals_to_eat = ft_atoi(argv[5]);
// 	return (0);
// }

// int	check_args(int argc, char **argv)
// {
// 	int	i;

// 	i = 1;
// 	if (argc == 5 || argc == 6)
// 	{
// 		while (i <= argc)
// 		{
// 			if (0 < ft_atoi((argv[i])))
// 				i++;
// 			if (0 < ft_atoi((argv[argc])))
// 				return (0);
// 			else
// 			{
// 				printf("positive numeric arguments only\n");
// 				return (1);
// 			}
// 		}
// 	}
// 	else
// 		printf("argument count not correct\n");
// 	return (0);
// }



int thread_join(pthread_t *monitor, t_philo *philo)
{
    int i;

    i = 0;
    if (pthread_join(monitor, NULL))
    {
        ft_putstr_fd("Error: monitor_join falied\n", 2);
        return (free_threads());
    }
    while(i < philo->data->philo_n)
    {
        if (pthread_join(philo->data->philo_thread[i], NULL))
        {
            ft_putstr_fd("Error: philo_join falied\n", 2);
            return (free_threads());
        }
        i++;
    }
    return (0);
}


int init_threads(t_philo *philo, t_program *data, char **argv)
{
    pthread_t monitor;
    int i;

    i = 0;
    if (pthread_create(&monitor, NULL, &monitoring, philo))//philo is the argument for thread
    {
        ft_putstr_fd("Error: monitoring thread_creat failed\n", 2);
        return (1);
    }
   while(i < philo->data->philo_n)
   {
       philo->data->philo_thread[i] = malloc(1 * sizeof(pthread_t));
       if (!philo->data->philo_thread[i])
       {
            ft_putstr_fd("Error: malloc\n", 2);
            return (free_threads());
       }
        if (pthread_create(&philo->data->philo_thread[i], NULL, &philo_routine, philo))
        {
            ft_putstr_fd("Error: philo thread_create failed\n", 2);
            return (free_threads());
        }
      i++;  
   }
    if (thread_join(monitor, philo))
        return (1);
    return (0);
}


int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_program	*data;
	
    if (validate_input(argc, argv))
        return (1);
	// if (check_args(argc, argv))
	// 	return (1);//error printed
	if (init_program(data, argv)) //this is a shared resource for all the philosophers should be program
		return (clean_program(data));
	
    philo = malloc(data->philo_n * sizeof(t_philo));
    if (!philo)
        return (clean_program(data));
    if (init_philo(philo, argv)) //this should be what kind of data each philosopher carries
		return (clean_all(data, philo));
    
    if (init_threads(philo, data, argv))
        return (clean_all(data, philo));
    
    if (clean_all(data, argv))
        return (1);
    return (0);
}



     


/*
./philo 5人 800死 200吃 200睡覺 
int main(int argc, char *argv[])
{
    //number_of_philosophers time_to_die time_to_eat time_to_sleep
    t_program data;

    //valid input  The number of philosophers , The time a philosopher will die if he doesn’t eat , The time it takes a philosopher to eat , The time it takes a philosopher to sleep   > 0   philo < 200
    if (validate_input(argc, argv))
        return (1);
    
    if (init_program(&data, argv))
        return (1);
    
     
    threads();
    run threads: 
    1. create philo and check threads and run routine ; every philo is a thread  create threads
    2. monitor- if die thread 
    3. monitor-if full thread
    4.threads join 
    
    monitor die 

     monitor full

    
    return (0);
}
*/

/*
log:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/