/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:18:33 by alli              #+#    #+#             */
/*   Updated: 2024/07/12 09:05:29 by alli             ###   ########.fr       */
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
	size_t	start_time;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	int		meals_to_eat; //# of meals 6th argument
	bool	dead_philo_flag;
	bool	everyone_full_flag;
	pthread_t	*philo_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock; //only 1 philosopher can print at a time
	pthread_mutex_t	death_lock; //only 1 death
	//pthread_t	thread_id; for debugging
} t_program;
//philo:   5人 800死 200吃 200睡覺  

typedef struct s_philo
{
    bool i_died;
    t_program	*data;
	bool n_philo_full;
	int	philo_index;
	long	last_meal_time;
	int		num_meals_eaten;
	bool		all_meals_eaten;
	
    pthread_mutex_t *l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	sleep_lock;
	pthread_mutex_t	eating_lock; //checking to see if the philosopher finished meals
} t_philo;

/*philosopher utilities*/
long	ft_atol(const char *str);
int	ft_isdigit(char *str);
int	ft_putstr_fd(char *s, int fd);
void ft_usleep(long millisecond);
size_t get_current_time(void);

/*initializing*/
int	init_philo(t_philo	*philo, t_program *data);
int	init_program(t_program *data, char **argv);

/*monitoring*/
int monitoring(t_program *data, t_philo *philo);


#endif