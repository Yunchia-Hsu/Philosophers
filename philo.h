/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <student.hive.fi>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:14:25 by yhsu              #+#    #+#             */
/*   Updated: 2024/07/11 14:34:20 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//write, usleep
# include <unistd.h>
//malloc, free
#include <stdlib.h>
//memset
# include <string.h>
//printf 
# include <stdio.h>
//pthread, mutex
# include <pthread.h>
//gettimeofday
# include <sys/time.h>
# include <stdbool.h>

struct timeval	time;

typedef struct s_program
{
    int philo_n;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	long	last_eat_time;
	int		meals_to_eat;
	bool	dead_philo_flag;
	bool	everyone_full_flag;
	pthread_t	*philo_thread;
	//pthread_t	thread_id; for debugging
} t_program;
//philo:   5人 800死 200吃 200睡覺  

typedef struct s_philo
{
    int dead;
    t_program		*data;
	int				n_philo_full;
	int				philo_index;
    pthread_mutex_t l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	sleep_lock;
	pthread_mutex_t	eating_lock;//only 1 philosopher can eat
	pthread_mutex_t	print_lock; //only 1 philosopher can print at a time
	pthread_mutex_t	death_lock; //only 1 death
} t_philo;

/*philosopher utilities*/
long	ft_atoi(const char *str);
int	ft_isdigit(char *str)

#endif