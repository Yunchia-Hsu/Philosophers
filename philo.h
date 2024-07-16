/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:18:33 by alli              #+#    #+#             */
/*   Updated: 2024/07/16 16:04:50 by alli             ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct s_program
{
    int 	philo_n;
	long long	start_time;
	long long	time_to_eat;
	long long	time_to_die;
	long long	time_to_sleep;
	int		meals_to_eat; //# of meals 6th argument
	bool	dead_philo_flag;// if one philois dead, it turns true
	bool	everyone_full_flag;
	// bool	can_write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock; //only 1 philosopher can print at a time
	pthread_mutex_t	death_lock; //only 1 death
	pthread_mutex_t	eating_lock;
	//pthread_t	thread_id; for debugging
} t_program;
//philo:   5人 800死 200吃 200睡覺  

typedef struct s_philo
{
    t_program	*data;
	bool 	n_philo_full;//philo[index] is fill
	int		philo_index;//index starts from 1
	long long	last_meal_time;
	int		num_meals_eaten;
	bool		all_meals_eaten;
    pthread_t	philo_thread;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_lock; //might be unnecessary  used in routine and monitoring
} t_philo;

/*philosopher utilities*/
long	ft_atol(const char *str);
int	ft_isdigit(int c);
int	ft_putstr_fd(char *s, int fd);
void ft_usleep(long long millisecond);
long long get_current_time(void);

/*philo routine*/
void	*philo_routine(void *ptr);
int	am_i_full(t_philo *philo);

/*dead or finished check*/
int	dead_or_finished(t_philo *philo);
int	die_alone(t_philo *philo);
int	starvation_check(t_philo *philo);
int	finished_meals(t_philo *philo);

/*initializing*/
int	init_philo(t_philo	*philo, t_program *data);
int	init_program(t_program *data, char **argv, int argc);

/*printing*/
void print_action(t_philo *philo, char *str);
void print_death(t_philo *philo);

/*monitoring*/
//void monitoring(void *data, void *philo);
void *monitoring(void *arg);
int meal_check(t_program *data, t_philo *philo);
int death_check(t_program *data, t_philo *philo);
int check_death_flag(t_program *data);


/*clean all*/
int clean_all(t_program *data, t_philo *philo);
// int clean_philo(t_program *data, t_philo *philo);
int clean_program(t_program *data);
#endif