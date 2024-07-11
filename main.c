/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:47:04 by alli              #+#    #+#             */
/*   Updated: 2024/07/11 10:35:44 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//valid input  The number of philosophers , The time a philosopher will die if he doesn’t eat , The time it takes a philosopher to eat , The time it takes a philosopher to sleep   > 0   philo < 200
init_program 
init_philo
//every philo is a thread  create threads; monitor is also a thread

// each philo geos into the routine function
// eat , sleep, think
routine()
{
    //loop the routine, and break when dead flag is 1
    // thinking: print message
    //eating : ft_usleep , print message //-alice thinks that ft_usleep should be for sleep
    //sleep :lock right / left forks , printf message , ft_usleep, drop forks (unlock fork) /

    //destroy mutex; free data if allocate any
}

monitor()
{

//infinite loop until philo dies
//check die; time now - last meal < the time philo needs to die

}

int	init_philo(t_pphilo	*philo, )

int	init_program(t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	philo->philo_n = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i <= argc)
		{
			if (0 < ft_atoi(ft_isdigit(argv[i])))
				i++;
			if (0 < ft_atoi(ft_isdigit(argv[argc])))
				return (1);
			else
			{
				printf("positive numeric arguments only\n");
				return (0);
			}
		}
	}
	else
		printf("argument count not correct\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_program	*data;
	
	if (!check_args(argc, argv))
		return (1);//error printed
	if (!init_program(&data, argv)) //this is a shared resource for all the philosophers should be program
		return (1);
	if (!init_philo(&philo, argv)) //this should be what kind of data each philosopher carries
		return (1);
}


/*
log:
X is thinking
X is sleeping
X is eating
*/