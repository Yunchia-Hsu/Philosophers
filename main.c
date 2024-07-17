

#include "philo.h"

int validate_input(int argc, char **argv)
{
    //./philo 5 philo ;800 time to die ;200 time to eat ;200 time to sleep
    int i;

    if (argc != 5 && argc != 6)
    {
        ft_putstr_fd("invalid number of arguments", 2);
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
       
	   //data->philo_thread[i] = (unsigned long)malloc(sizeof(pthread_t));
       

	//if (!philo->data->philo_thread[i])
    //    {
    //        printf("thread.6\n");
	// 	    ft_putstr_fd("Error: malloc\n", 2);
    //         return (clean_all(data, philo));
    //    }
	 
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
    {
		return (1);
	}
	//printf("enters init_program0\n");
	if (init_program(&data, argv, argc))
	{
		printf("something's wrong\n");
		return (clean_program(&data));
	}	
	philo = malloc(data.philo_n * sizeof(t_philo));
	if (!philo)
        return (clean_program(&data));
    if (init_philo(philo, &data, argc)) //this should be what kind of &data each philosopher carries
		return (clean_program(&data));
		//return (clean_all(&data, philo));
    //printf("test0\n");
    
	if (init_threads(philo, &data))
        return(clean_all(&data, philo));
    
	//printf("test1\n");
    
	if (clean_all(&data, philo))
        return (1);
	
	//printf("test2\n");
    
	return (0);
}


//./philo 5人 800死 200吃 200睡覺 
