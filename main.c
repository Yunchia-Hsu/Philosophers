/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:47:04 by alli              #+#    #+#             */
/*   Updated: 2024/07/10 16:38:52 by alli             ###   ########.fr       */
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
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i <= argc)
		{
			if (!ft_isdigit(argv[i]))
				i++;
			else
				return (1);
		}
	}
	else
	{
		printf("argument count not correct\n");
		return (0);
	}
		
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (1);//error printed
	if (init_)
	
	
}


/*
log:
X is thinking
X is sleeping
X is eating
*/