
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
    pthread_t t;
    int philo_n;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	meals_to_eat;
	bool	dead_philo;
	bool	has_eaten;
} t_program;



//philo:   5人 800死 200吃 200睡覺  

typedef struct s_philo
{
    pthread_t t;
    int philo_n;//id
    int n_meal_had;
    long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
     last_eat_time;//use long because we use millm isecond
    status;// eating or sleeping
    pthread_t thread_id;

} t_philo;

typedef struct s_program
{
    bool dead;
    int *philo;
    int fork_id; //for debug
    int n_philo_full;
    int n_meals_option;
    //   3   pthread_mutex_t 
    pthread_mutex_t l_fork;
    pthread_mutex_t r_fork;
    pthread_mutex_t eat_lock;
    pthread_mutex_t sleep_lock;
    pthread_mutex_t print_lock;

    pthread_t *philos;
    pthread_t check_die;//check if one philo dies
    pthread_t check_full;//check if all philos r full
    t_philo *philos;
} t_program






    int dead;
    t_philo *philo;
    //   3   pthread_mutex_t 
    pthread_mutex_t l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	eating_lock;//only 1 philosopher can eat
	pthread_mutex_t	print_lock; //only 1 philosopher can print at a time
	pthread_mutex_t	death_lock; //only 1 death
} t_philo;

/*philosopher utilities*/
int	ft_atoi(const char *str);
int	ft_isdigit(char *str)

#endif