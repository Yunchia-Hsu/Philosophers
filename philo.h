
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


typedef struct s_philo
{
    int dead;
    t_philo *philo;
    //   3   pthread_mutex_t 
    pthread_mutex_t l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	eating_lock;
} t_philo;

/*philosopher utilities*/
int	ft_atoi(const char *str);
int	ft_isdigit(char *str)

#endif